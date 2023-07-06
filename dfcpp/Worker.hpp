//
// Created by Gboom on 2022/10/28.
//

#ifndef DFCPP_WORKER_HPP
#define DFCPP_WORKER_HPP

#include "TaskQueue.hpp"
#include "EventCount.hpp"
#include <thread>
#include <functional>
#include <vector>
#include <random>


namespace DFCPP{

    class Executor;
    class DFVComm;

    class Worker{
        friend class Executor;
        friend class ExecutorNuma;
    public:
        Worker() = default;

        size_t id() const {return _id;}

        inline void push(Node* node) {
            _queue.push(node);
        }
        inline Node* pop() {
            return _queue.pop();
        }
        inline Node* steal() {
            return _queue.steal();
        }

        // non-thread-safe
        void _clearDetach();

        void setReadyDFV(DFVComm* dfv) {
            _readyDFVS.emplace_back(dfv);
        }
        [[nodiscard]] std::vector<DFVComm*>&& getAndClearReadyDFV()  { return std::move(_readyDFVS);}
        void setReadyDFV(const std::vector<DFVComm*>& dfvs) { _readyDFVS = dfvs; }

//        void* alloc(size_t n) {
//            return _hoard->alloc(n);
//        }

        int numaNode() const {return _numaNode;}

    private:
        size_t _id;      // worker id also as the index of Executor's workers;
        TaskQueue<Node*> _queue;
        std::default_random_engine _engine;
        std::vector<Node*> _detachedTasks;
        std::vector<DFVComm*> _readyDFVS;
        EventCount::Waiter* _waiter;
        int _numaNode = -1;
    };

    // non-thread-safe
    void Worker::_clearDetach() {
        for(auto n : _detachedTasks) {
            delete n;
        }
        _detachedTasks.clear();
    }

}



#endif //DFCPP_WORKER_HPP
