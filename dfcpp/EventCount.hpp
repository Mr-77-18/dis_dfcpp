//
// Created by ljr on 12/4/22.
// from taskflow
//

#ifndef DFCPP_EVENTCOUNT_HPP
#define DFCPP_EVENTCOUNT_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <atomic>
#include <memory>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <algorithm>
#include <numeric>
#include <cassert>


namespace DFCPP {

    class EventCount {
        friend class Worker;
        friend class ExecutorNuma;
    public:

        struct Waiter {
            std::atomic<Waiter*> next;
            std::mutex mu;
            std::condition_variable cv;
            uint64_t epoch;
            unsigned state;
            enum {
                kNotSignaled,
                kWaiting,
                kSignaled,
            };
        };

        explicit EventCount(size_t N) : _waiters{N} {
            assert(_waiters.size() < (1 << kWaiterBits) - 1);
            // Initialize epoch to something close to overflow to tesft overflow.
            _state = kStackMask | (kEpochMask - kEpochInc * _waiters.size() * 2);
        }

        ~EventCount() {
            // Ensure there are no waiters.
            assert((_state.load() & (kStackMask | kWaiterMask)) == kStackMask);
        }

        // prepare_wait prepares for waiting.
        // After calling this function the thread must re-check the wait predicate
        // and call either cancel_wait or commit_wait passing the same Waiter object.
        void prepare_wait(Waiter* w) {
            w->epoch = _state.fetch_add(kWaiterInc, std::memory_order_relaxed);
            std::atomic_thread_fence(std::memory_order_seq_cst);
        }

        // commit_wait commits waiting.
        void commit_wait(Waiter* w) {
            w->state = Waiter::kNotSignaled;
            // Modification epoch of this waiter.
            uint64_t epoch =
                    (w->epoch & kEpochMask) +
                    (((w->epoch & kWaiterMask) >> kWaiterShift) << kEpochShift);
            uint64_t state = _state.load(std::memory_order_seq_cst);
            for (;;) {
                if (int64_t((state & kEpochMask) - epoch) < 0) {
                    // The preceeding waiter has not decided on its fate. Wait until it
                    // calls either cancel_wait or commit_wait, or is notified.
                    std::this_thread::yield();
                    state = _state.load(std::memory_order_seq_cst);
                    continue;
                }
                // We've already been notified.
                if (int64_t((state & kEpochMask) - epoch) > 0) return;
                // Remove this thread from prewait counter and add it to the waiter list.
                assert((state & kWaiterMask) != 0);
                uint64_t newstate = state - kWaiterInc + kEpochInc;
                //newstate = (newstate & ~kStackMask) | (w - &_waiters[0]);
                newstate = static_cast<uint64_t>((newstate & ~kStackMask) | static_cast<uint64_t>(w - &_waiters[0]));
                if ((state & kStackMask) == kStackMask)
                    w->next.store(nullptr, std::memory_order_relaxed);
                else
                    w->next.store(&_waiters[state & kStackMask], std::memory_order_relaxed);
                if (_state.compare_exchange_weak(state, newstate,
                                                 std::memory_order_release))
                    break;
            }
            _park(w);
        }

        // cancel_wait cancels effects of the previous prepare_wait call.
        void cancel_wait(Waiter* w) {
            uint64_t epoch =
                    (w->epoch & kEpochMask) +
                    (((w->epoch & kWaiterMask) >> kWaiterShift) << kEpochShift);
            uint64_t state = _state.load(std::memory_order_relaxed);
            for (;;) {
                if (int64_t((state & kEpochMask) - epoch) < 0) {
                    // The preceeding waiter has not decided on its fate. Wait until it
                    // calls either cancel_wait or commit_wait, or is notified.
                    std::this_thread::yield();
                    state = _state.load(std::memory_order_relaxed);
                    continue;
                }
                // We've already been notified.
                if (int64_t((state & kEpochMask) - epoch) > 0) return;
                // Remove this thread from prewait counter.
                assert((state & kWaiterMask) != 0);
                if (_state.compare_exchange_weak(state, state - kWaiterInc + kEpochInc,
                                                 std::memory_order_relaxed))
                    return;
            }
        }

        // notify wakes one or all waiting threads.
        // Must be called after changing the associated wait predicate.
        void notify(bool all) {
            std::atomic_thread_fence(std::memory_order_seq_cst);
            uint64_t state = _state.load(std::memory_order_acquire);
            for (;;) {
                // Easy case: no waiters.
                if ((state & kStackMask) == kStackMask && (state & kWaiterMask) == 0)
                    return;
                uint64_t waiters = (state & kWaiterMask) >> kWaiterShift;
                uint64_t newstate;
                if (all) {
                    // Reset prewait counter and empty wait list.
                    newstate = (state & kEpochMask) + (kEpochInc * waiters) + kStackMask;
                } else if (waiters) {
                    // There is a thread in pre-wait state, unblock it.
                    newstate = state + kEpochInc - kWaiterInc;
                } else {
                    // Pop a waiter from list and unpark it.
                    Waiter* w = &_waiters[state & kStackMask];
                    Waiter* wnext = w->next.load(std::memory_order_relaxed);
                    uint64_t next = kStackMask;
                    //if (wnext != nullptr) next = wnext - &_waiters[0];
                    if (wnext != nullptr) next = static_cast<uint64_t>(wnext - &_waiters[0]);
                    // Note: we don't add kEpochInc here. ABA problem on the lock-free stack
                    // can't happen because a waiter is re-pushed onto the stack only after
                    // it was in the pre-wait state which inevitably leads to epoch
                    // increment.
                    newstate = (state & kEpochMask) + next;
                }
                if (_state.compare_exchange_weak(state, newstate,
                                                 std::memory_order_acquire)) {
                    if (!all && waiters) return;  // unblocked pre-wait thread
                    if ((state & kStackMask) == kStackMask) return;
                    Waiter* w = &_waiters[state & kStackMask];
                    if (!all) w->next.store(nullptr, std::memory_order_relaxed);
                    _unpark(w);
                    return;
                }
            }
        }

        // notify n workers
        void notify_n(size_t n) {
            if(n >= _waiters.size()) {
                notify(true);
            }
            else {
                for(size_t k=0; k<n; ++k) {
                    notify(false);
                }
            }
        }

        size_t size() const {
            return _waiters.size();
        }

    private:

        // State_ layout:
        // - low kStackBits is a stack of waiters committed wait.
        // - next kWaiterBits is count of waiters in prewait state.
        // - next kEpochBits is modification counter.
        static const uint64_t kStackBits = 16;
        static const uint64_t kStackMask = (1ull << kStackBits) - 1;
        static const uint64_t kWaiterBits = 16;
        static const uint64_t kWaiterShift = 16;
        static const uint64_t kWaiterMask = ((1ull << kWaiterBits) - 1)
                << kWaiterShift;
        static const uint64_t kWaiterInc = 1ull << kWaiterBits;
        static const uint64_t kEpochBits = 32;
        static const uint64_t kEpochShift = 32;
        static const uint64_t kEpochMask = ((1ull << kEpochBits) - 1) << kEpochShift;
        static const uint64_t kEpochInc = 1ull << kEpochShift;
        std::atomic<uint64_t> _state;
        std::vector<Waiter> _waiters;

        void _park(Waiter* w) {
            std::unique_lock<std::mutex> lock(w->mu);
            while (w->state != Waiter::kSignaled) {
                w->state = Waiter::kWaiting;
                w->cv.wait(lock);
            }
        }

        void _unpark(Waiter* waiters) {
            Waiter* next = nullptr;
            for (Waiter* w = waiters; w; w = next) {
                next = w->next.load(std::memory_order_relaxed);
                unsigned state;
                {
                    std::unique_lock<std::mutex> lock(w->mu);
                    state = w->state;
                    w->state = Waiter::kSignaled;
                }
                // Avoid notifying if it wasn't waiting.
                if (state == Waiter::kWaiting) w->cv.notify_one();
            }
        }

    };



}  // namespace DFCPP ------------------------------------------------------------




#endif //DFCPP_EVENTCOUNT_HPP
