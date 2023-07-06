//
// Created by Gboom on 2022/10/27.
//

#ifndef DFCPP_TASKQUEUE_HPP
#define DFCPP_TASKQUEUE_HPP

#include <atomic>
#include <cassert>

namespace DFCPP{

    template<typename T>
    class TaskQueue{
    private:
        struct Buffer{
            int64_t cap;
            int64_t mask;
            std::atomic<T>* buffer;

            explicit Buffer(int64_t c) :
                    cap{c},
                    mask{cap - 1},
                    buffer{new std::atomic<T>[static_cast<size_t>(cap)]}
            {}

            ~Buffer() {
                delete[] buffer;
            }

            void push(int64_t i, T t) noexcept {
                buffer[i & mask].store(t, std::memory_order_relaxed);
            }

            T pop(int64_t i) noexcept {
                return buffer[i & mask].load(std::memory_order_relaxed);
            }

            Buffer* resize(int64_t b, int64_t t) {
                auto ptr = new Buffer{2 * cap};
                while(t < b) {
                    ptr->push(t, pop(t));
                    t++;
                }
                return ptr;
            }

            int64_t capacity() const noexcept {
                return cap;
            }
        };
    public:
        explicit TaskQueue(int64_t c = 512) :
            _bottom{0},
            _top{0}
        {
            assert(!(c & (c - 1)));     // c must be the exponent of 2
            _garbage.reserve(32);
            _buffer.store(new Buffer(c), std::memory_order_relaxed);
        }

        ~TaskQueue() {
            for(auto buffer: _garbage) {
                delete buffer;
            }
            delete _buffer.load();
        }

        void push(T);
        T pop();
        T steal();
//        void initBuffer(int64_t c = 512) {
//            assert(!(c &(c-1)));
//            _buffer.store(new Buffer(c), std::memory_order_relaxed);
//        }
    private:
        std::atomic<int64_t> _bottom;           // _bottom 和 _top必须是有符号的，因为无符号数会在pop的时候溢出，进而使得本来空的队列表现不为空。
        std::atomic<int64_t> _top;
        std::atomic<Buffer*> _buffer;
        std::vector<Buffer*> _garbage;


    };

    template<typename T>
    void TaskQueue<T>::push(T t) {
        auto bottom = _bottom.load(std::memory_order_relaxed);
        auto top = _top.load(std::memory_order_acquire);
        auto buffer = _buffer.load(std::memory_order_relaxed);

        // queue is full
        if((bottom - top) > buffer->capacity() - 1) {
            auto newBuffer = buffer->resize(bottom, top);
            _garbage.emplace_back(buffer);
            std::swap(newBuffer, buffer);
            _buffer.store(buffer, std::memory_order_relaxed);
        }

        buffer->push(bottom ,t);
        std::atomic_thread_fence(std::memory_order_release);
        _bottom.store(bottom + 1, std::memory_order_relaxed);
    }

    template<typename T>
    T TaskQueue<T>::pop() {
        auto bottom = _bottom.load(std::memory_order_relaxed) - 1;
        auto buffer = _buffer.load(std::memory_order_relaxed);
        _bottom.store(bottom, std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_seq_cst);
        auto top = _top.load(std::memory_order_relaxed);

        T res = nullptr;
        if(bottom >= top) {
            res = buffer->pop(bottom);
            if(bottom == top) {
                if(!_top.compare_exchange_strong(top, top+1,
                                                 std::memory_order_seq_cst,
                                                 std::memory_order_relaxed)) {
                    res = nullptr;
                }
                _bottom.store(bottom + 1, std::memory_order_relaxed);
            }
        } else {
            _bottom.store(bottom + 1, std::memory_order_relaxed);
        }
        return res;
    }

    template<typename T>
    T TaskQueue<T>::steal() {
        auto top = _top.load(std::memory_order_acquire);
        std::atomic_thread_fence(std::memory_order_seq_cst);
        auto bottom = _bottom.load(std::memory_order_acquire);

        T res = nullptr;
        if(bottom > top) {
            auto buffer = _buffer.load(std::memory_order_consume);
            res = buffer->pop(top);
            if(!_top.compare_exchange_strong(top, top + 1,
                                             std::memory_order_seq_cst,
                                             std::memory_order_relaxed)) {
                return nullptr;
            }
        }
        return res;
    }
}


#endif //DFCPP_TASKQUEUE_HPP
