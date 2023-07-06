//
// Created by Gboom on 2022/10/20.
//

#ifndef DFCPP_EXECUTOR_HPP
#define DFCPP_EXECUTOR_HPP

#include "DFGraph.hpp"
#include "DynamicTask.hpp"
#include "Worker.hpp"
#include "Topology.hpp"
#include "EventCount.hpp"
#include "ConcurrentQueue.hpp"

#ifdef DFCPP_NUMA_ALLOC
#include "Hoard.hpp"
#endif

#include <queue>

namespace DFCPP{

    thread_local Worker* _threadWorker = nullptr;       // thread local variable
#ifdef DFCPP_NUMA_ALLOC
    HoardNuma _hoardNuma;           // 全局内存分配对象
#endif
    class Executor;

    /**
     * @brief 非接口类，每个numa节点一个执行器
     */
    class ExecutorNuma{
    public:
        ExecutorNuma(Executor* executor, int numaNode, size_t n):
                _executor(executor),
                _threads(n),
                _workers(n),
                _numThieves{0},
                _numActives{0},
                _eventCount(n),
                _maxSteals((n+1) << 1),
                _maxYields(100),
                _numaNode(numaNode)
        {}

        Node* steal() {
            Node* res = nullptr;
#ifdef DFCPP_STEAL_PRIORITY
            if(_numThieves > 0 ) {
                return res;
            }
#endif
            _sharedQueue.try_dequeue(res);
            if(res) return res;
            if(_numThieves == 0) {
                std::uniform_int_distribution<size_t> uid(0, _workers.size() - 1);
                res = _workers[uid(_threadWorker->_engine)].steal();
            }

            return res;
        }
        void push(Node* node) {
            _sharedQueue.enqueue(node);
            _eventCount.notify(false);
        }

        void push(const std::vector<Node*>& nodes) {
            for(auto node : nodes) {
                _sharedQueue.enqueue(node);
            }
            _eventCount.notify_n(nodes.size());
        }

        // non thread-safe
        void clearDetach();
        // init the workers
        void _spawn();
        void exit() {_done.store(true, std::memory_order_relaxed);}
    private:
        Executor* _executor;
        std::vector<std::thread> _threads;
        std::vector<Worker> _workers;
        moodycamel::ConcurrentQueue<Node*>    _sharedQueue;                   // shared task queue
        std::atomic_int64_t _numThieves;                    // 正在窃取任务线程数
        std::atomic_int64_t _numActives;                    // 正在执行任务线程数
        EventCount  _eventCount;                            // 无锁条件变量
        const size_t _maxSteals;
        const size_t _maxYields;
        const int _numaNode;
        std::atomic_bool _done{false};                      // 是否结束

        // schedule task
        void _invokeTask(Node*);
        // perform static Task
        void _invokeStaticTask(Node*);
        // perform Dynamic Task
        void _invokeDynamicTask(Node*);
        // perform Condition task
        void _invokeConditionTask(Node*);
        void _resetNodeAndScheduleTask(Node*);
        void _tearDownGraph(Graph* graph);           // 检查此图是否已完成

        void _threadLoop();    // worker loop function
        void _loopUntil(const std::function<bool()>&);
        void _scheduleTask(Node*);      // push the ready task into queue
        void _runOutLocalQueue(Node*&);
        Node* _waitForTask(Worker* );
        Node* _stealFromLocal();
        Node* _stealFromRemote();
        Node* _stealRandomly();           // 随机窃取，不区分numa
    };

    /**
     * @brief   接口类，用于执行数据流图。
     */
    class Executor{
        friend class ExecutorNuma;
    public:
        /**
         * @brief       创建一个执行器。
         * @param n     线程数
         * @attention   一个程序应该只创建一个Executor对象。
         */
        // TODO: 实现单例模式
        explicit Executor(size_t n = std::thread::hardware_concurrency()) :
                _activeTopology{nullptr}
        {
            int numNuma = NUMANUM;
            for(int i = 0; i < numNuma; i++) {
                auto executorNuma = new ExecutorNuma(this, i, n);
                _executorNumas.emplace_back(executorNuma);
            }
            for(auto item : _executorNumas) {
                item->_spawn();
            }
        }

        ~Executor() {
            for(auto executor : _executorNumas) {
                executor->exit();
            }
        }

        // non thread-safe, should be called in the main thread and be called only once
        /**
         * @brief           运行一个数据流图graph n次
         * @param graph     要运行的数据流图
         * @param n         运行次数
         * @return          std::future<void>
         * @attention       调用run()并不一定会立即执行graph，需要等待之前run()所提交的graph。
         * @attention       非线程安全，只能在主线程调用。
         */
        std::future<void> run(DFGraph& graph, size_t n = 1);

        /**
         * @brief           运行一个数据流图graph n次,并在每次结束时调用epilogue。
         * @param graph     要运行的数据流图
         * @param n         运行次数
         * @param epilogue  图每次运行结束要执行的函数
         * @return          std::future<void>
         * @attention       调用run()并不一定会立即执行graph，需要等待之前run()所提交的graph。
         * @attention       非线程安全，只能在主线程调用。
         */
        std::future<void> run(DFGraph& graph, size_t n, std::function<void(void)> epilogue);

        /**
         * @brief           运行一个数据流图graph 1次,并在结束时调用epilogue。
         * @param graph     要运行的数据流图
         * @param epilogue  运行结束要执行的函数
         * @return          std::future<void>
         * @attention       调用run()并不一定会立即执行graph，需要等待之前run()所提交的graph。
         * @attention       非线程安全，只能在主线程调用。
         */
        std::future<void> run(DFGraph& graph, std::function<void(void)> epilogue);

    private:
        std::vector<ExecutorNuma*>  _executorNumas;
        std::queue<std::shared_ptr<Topology>> _topologies;
        Topology*  _activeTopology;                         // todo: 需要是原子变量吗
        std::mutex _mutex;                                  // protect _topologies


        void _runTopology(Topology*);       // guard by _mutex
        // non thread-safe
        void _clearDetach();

        Topology* getActiveTopology() {return _activeTopology;}
        void teardownTopology(Topology* topology);     // 检查topology是否完成

        Node* stealFromNuma(int numaNode) {
            return _executorNumas[numaNode]->steal();
        }

        void pushToNuma(Node* node, size_t numaNode) {
            _executorNumas[numaNode]->push(node);
        }

        /**
         * @brief   将一个就绪任务添加到任务队列
         * @param node
         * @attention 只能在worker线程中调用
         */
        void scheduleTask(Node* node);
    };

    void ExecutorNuma::_invokeTask(Node * node) {
        switch (node->_handle.index()) {
            case Node::STATIC:
                _invokeStaticTask(node);
                break;
            case Node::DYNAMIC:
                _invokeDynamicTask(node);
                break;
            case Node::CONDITION:
                _invokeConditionTask(node);
                break;
            default:
                throw std::runtime_error("unknown task type");
        }
        if(node->_graph) _tearDownGraph(node->_graph);
        else _executor->teardownTopology(node->_topology);
    }

    void ExecutorNuma::_spawn() {
        size_t n = _workers.size();
        for(size_t i = 0; i < n; i++) {
            _workers[i]._id = i;
            _workers[i]._numaNode = _numaNode;
            _workers[i]._waiter = &_eventCount._waiters[i];
            _threads[i] = std::thread([this, id = i](){
                _threadWorker = &_workers[id];
#ifdef DFCPP_NUMA
                numa_run_on_node(_numaNode);
#endif
                _threadLoop();
            });
        }
    }

    void ExecutorNuma::_invokeStaticTask(Node *node) {
        std::get_if<Node::STATIC>(&node->_handle)->work();
        _resetNodeAndScheduleTask(node);
    }

    // DynamicTas is default to join;
    void ExecutorNuma::_invokeDynamicTask(Node *node) {
        DynamicTask dynamicTask(node->_graph);
        std::get_if<Node::DYNAMIC>(&node->_handle)->work(dynamicTask);
        std::vector<Node*> tasks;
        dynamicTask.getSourceTask(tasks);
        // join
        if(dynamicTask._joinable) {
            for(auto n : tasks) {
                _scheduleTask(n);
            }                                       // fixme : 动态任务内赋值的DFV此阶段都不应该触发任务
            std::vector<DFVComm*> readyDFV  = _threadWorker->getAndClearReadyDFV();
            auto f = [&dynamicTask](){return dynamicTask._joinCounter == 0;};
            _loopUntil(f);
            _threadWorker->setReadyDFV(readyDFV);
        } else {    // detach
            for(auto n : dynamicTask._nodes) {
                n->_graph = nullptr;
                n->_topology = _executor->getActiveTopology();
            }
            _threadWorker->_detachedTasks.insert(_threadWorker->_detachedTasks.end(), dynamicTask._nodes.begin(), dynamicTask._nodes.end());
            for(auto n : tasks) {
                _scheduleTask(n);       // todo: 优化一下
            }
            dynamicTask._nodes.clear();
        }
        _resetNodeAndScheduleTask(node);
    }

    void ExecutorNuma::_invokeConditionTask(Node * node) {
        auto index = std::get_if<Node::CONDITION>(&node->_handle)->work();
        _resetNodeAndScheduleTask(node);
        // 控制依赖任务
        if(index < node->_successors.size()) {
            auto nChild = node->_successors[index];
            if(nChild->decreaseJoinCounter()) {
                _scheduleTask(nChild);
            }
        }
    }

    Node *ExecutorNuma::_waitForTask(Worker* worker) {
        ++_numThieves;
        Node* res = nullptr;
        while(true) {
#ifdef DFCPP_NUMA_STEAL
            res = _stealFromLocal();
            if(!res) {
                res = _stealFromRemote();
            }
#else
            res = _stealRandomly();
#endif
            if(res) {
                break;
            }

#ifdef DFCPP_WORKER_ADJUSTMENT
            _eventCount.prepare_wait(_threadWorker->_waiter);
            _sharedQueue.try_dequeue(res);
            if(res) {
                _eventCount.cancel_wait(_threadWorker->_waiter);
                break;
            }
            if(_done) {
                _eventCount.cancel_wait(_threadWorker->_waiter);
                break;
            }
            if(_numThieves.fetch_sub(1) == 1) {
                _eventCount.cancel_wait(_threadWorker->_waiter);
                ++_numThieves;
            } else {
                _eventCount.commit_wait(_threadWorker->_waiter);
                ++_numThieves;
            }
#else
            if(_done) {break;}
#endif
        }

#ifdef DFCPP_WORKER_ADJUSTMENT
        if(res) {
            if(_numThieves.fetch_sub(1) == 1) {
                _eventCount.notify(false);
            }
        } else {        // 结束了
            _eventCount.notify(true);
            --_numThieves;
        }
#else
      --_numThieves;
#endif

        return res;
    }

    void ExecutorNuma::_threadLoop() {
//        worker->_queue.initBuffer(512);
        Node* node = nullptr;
        while(!_done) {
            _runOutLocalQueue(node);
            node = _waitForTask(_threadWorker);
        }
    }

    void ExecutorNuma::_loopUntil(const std::function<bool()>& f) {
        Node* node;
        std::uniform_int_distribution<size_t> uid(0, _workers.size() - 1);
        while(!f()) {
            node = _threadWorker->pop();
            if(!node) {
                size_t index = uid(_threadWorker->_engine);
                if(index != _threadWorker->_id) {
                    node = _workers[index].steal();
                } else {
                    _sharedQueue.try_dequeue(node);
                }
            }
            if(node) {
                _invokeTask(node);
            }
        }
    }

    // non thread-safe
    // should be guarded by _mutex
    // 调用此函数时，不应有任务正在执行中
    void ExecutorNuma::clearDetach() {
        for(auto& w : _workers)
            w._clearDetach();
    }

    void ExecutorNuma::_resetNodeAndScheduleTask(Node * node) {
        // 先重置任务再调度后续任务
        node->reset();
        for(auto dfv : _threadWorker->_readyDFVS) {
            for(auto n : dfv->_nodes) {
                // for work pushing
                if(n->decreaseJoinCounter()) {
                    _scheduleTask(n);
                }
            }
        }
#ifdef DFCPP_DFV_COUNT
        // 当任务结束时递减计数。如果计数为零则释放内存。
        // fixme: 此处内存释放和赋值可能会造成数据冒险。
        for(auto dfv : node->_inputDFVs) {
            if(dfv->_counter.fetch_sub(1, std::memory_order_relaxed) == 1) {
                dfv->release();
            }
        }
#endif

        _threadWorker->_readyDFVS.clear();
}

    void ExecutorNuma::_tearDownGraph(Graph *graph) {
        if(graph->_joinCounter.fetch_sub(1) == 1 && graph->_topology) {
            _executor->teardownTopology(graph->_topology);
        }
    }

    void ExecutorNuma::_scheduleTask(Node *node) {
        if(node->_graph)
            node->_graph->_joinCounter.fetch_add(1, std::memory_order_relaxed);
        else
            node->_topology->_join_counter.fetch_add(1, std::memory_order_relaxed);

        // for work pushing
#ifdef DFCPP_WORK_PUSHING
        auto numaNode = node->getMaxNumaNode();
        if(numaNode == _threadWorker->_numaNode)
            _threadWorker->push(node);
        else
            _executor->pushToNuma(node, numaNode);
#else
      _threadWorker->push(node);
#endif
    }

    // 执行所有本地任务
    void ExecutorNuma::_runOutLocalQueue(Node* & node) {
        if(node) {
            if(_numActives.fetch_add(1) == 0 && _numThieves == 0) {
                _eventCount.notify(false);
            }
            while (node) {
                _invokeTask(node);
                node = _threadWorker->pop();
            }
            --_numActives;
        }
    }

    Node *ExecutorNuma::_stealFromLocal() {
        Node* res = nullptr;
        std::uniform_int_distribution<size_t> uid(0, _workers.size() - 1);
        size_t numSteals = 0;
        size_t numYields = 0;
        while(!_done)
        {
            _sharedQueue.try_dequeue(res);
            if(res) break;
            size_t index = uid(_threadWorker->_engine);
            if(index != _threadWorker->_id) {
                res = _workers[index]._queue.steal();
            }
            if(res) break;
            if(numSteals++ > _maxSteals) {
                std::this_thread::yield();
                if(numYields++ > _maxYields) {
                    res = nullptr;
                    break;
                }
            }
        }
        return res;
    }

    Node *ExecutorNuma::_stealFromRemote() {
        Node* res = nullptr;
        std::uniform_int_distribution<size_t> uid(0, _executor->_executorNumas.size() - 1);
        size_t numSteals = 0;
        size_t numYields = 0;
        while(!_done)
        {
            _sharedQueue.try_dequeue(res);
            if(res) break;
            size_t index = uid(_threadWorker->_engine);
            if(index != _numaNode) {
                res = _executor->stealFromNuma(index);
            }

            if(res) break;
            if(numSteals++ > _maxSteals) {
                std::this_thread::yield();
                if(numYields++ > _maxYields) {
                    res = nullptr;
                    break;
                }
            }
        }
        return res;
    }

    Node* ExecutorNuma::_stealRandomly() {
        Node* res = nullptr;
        std::uniform_int_distribution<size_t> uid(0, NUMANUM - 1);
        size_t numSteals = 0;
        size_t numYields = 0;
        while(!_done)
        {

            size_t index = uid(_threadWorker->_engine);
            if(index != _numaNode) {
                res = _executor->stealFromNuma(index);
            } else {
                res = _stealFromLocal();
            }

            if(res) break;
            if(numSteals++ > _maxSteals) {
                std::this_thread::yield();
                if(numYields++ > _maxYields) {
                    res = nullptr;
                    break;
                }
            }
        }

        return res;
    }

    std::future<void> Executor::run(DFGraph &graph, size_t n) {
        auto topology = std::make_shared<Topology>(&graph, n);
        {
            std::lock_guard<std::mutex> lockGuard(_mutex);
            _topologies.push(topology);
            if(_topologies.size() == 1) {
                _runTopology(topology.get());
            }
        }

        return topology->get_future();
    }

    std::future<void> Executor::run(DFGraph &graph, size_t n, std::function<void(void)> epilogue) {
        auto topology = std::make_shared<Topology>(&graph, n);
        topology->_epilogue = std::move(epilogue);
        {
            std::lock_guard<std::mutex> lockGuard(_mutex);
            _topologies.push(topology);
            if(_topologies.size() == 1) {
                _runTopology(topology.get());
            }
        }
        return topology->get_future();
    }

    std::future<void> Executor::run(DFGraph &graph, std::function<void(void)> epilogue) {
        return run(graph, 1, std::move(epilogue));
    }

    void Executor::teardownTopology(Topology *topology) {
        if(topology->_join_counter.fetch_sub(1) == 1) {
            if(topology->_epilogue) {
                topology->_epilogue();
            }
            if(topology->_epochs.fetch_sub(1) == 1) {       // 此地run已经结束
                topology->_promise.set_value();
                {
                    std::lock_guard<std::mutex> lockGuard(_mutex);
                    _topologies.pop();
                    if(!_topologies.empty()) {
                        _runTopology(_topologies.front().get());
                    }
                }
            } else {
                _runTopology(topology);                     // 还需要继续跑
            }

        }
    }

    // non thread-safe
    void Executor::_clearDetach() {
        for(auto item : _executorNumas) {
            item->clearDetach();
        }
    }

    // guard by _mutex
    // 在执行这个函数的时候，调度器应该处于空闲状态，即没有任务正在运行中
    void Executor:: _runTopology(Topology * topology) {
        topology->_graph->_topology = topology;
        _activeTopology = topology;
        std::vector<Node*> tasks;
        topology->_graph->getSourceTask(tasks);//假设没有任务，这里tasks为空的
        topology->_join_counter = 1;
        if(tasks.empty()) {//当没有可以执行的任务，会进入这个分支
            if(topology->_epilogue) {
                topology->_epilogue();
            }
            topology->_promise.set_value();
        } else {
            _clearDetach();
            // todo
            if(_threadWorker) {
                for(auto n : tasks) {                   // 这里不需要再递增graph，getsourceTask已经做了
                    scheduleTask(n);
                }
            } else {                                            // 默认在0节点上运行
                topology->_graph->_joinCounter.store(tasks.size(), std::memory_order_relaxed);
                _executorNumas[0]->push(tasks);
            }
        }
    }

    void Executor::scheduleTask(DFCPP::Node *node) {
        if(node->_graph)
            node->_graph->_joinCounter.fetch_add(1, std::memory_order_relaxed);
        else
            node->_topology->_join_counter.fetch_add(1, std::memory_order_relaxed);

#ifdef DFCPP_WORK_PUSHING
        // for work pushing
        auto numaNode = node->getMaxNumaNode();
        if(numaNode == _threadWorker->_numaNode)
            _threadWorker->push(node);
        else
            pushToNuma(node, numaNode);
#else
            _threadWorker->push(node);
#endif
    }

    //--------------------------DFV--------------------------
    // DFV赋值不再包括触发任务的行为。触发任务的工作将由worker和graph负责
    void DFVComm::commitAssignment() {
        if(_threadWorker) {
            _threadWorker->setReadyDFV(this);
        } else {
            _graph->setReadyDFV(this);
        }
    }

    template<typename T>
    void DFV<T>::DFVImpl::release() {
        if(_data) {
#ifdef DFCPP_NUMA_ALLOC
            _hoardNuma.free(_numaNode, _data, _dataSize);
            _data = nullptr;
#else
            delete (T*)_data;
            _data = nullptr;
#endif
        }
    }

    template<typename T>
    template<typename ...Args>
    DFV<T>::DFVImpl::DFVImpl(DFCPP::Graph *g, Args &&...args):DFVComm(g) {
#ifdef DFCPP_NUMA_ALLOC
        if(_threadWorker) {
            _numaNode = _threadWorker->numaNode();
            _data = _hoardNuma.allocOnNumaNodeWithThreadID(_numaNode, _threadWorker->id(), sizeof(T));
        } else {
            _numaNode = 0;
            _data = _hoardNuma.alloc(_numaNode, sizeof(T));
        }
        new(_data)T(args...);
#else
      _data = new T(args...);
#endif
        _dataSize = sizeof(T);
        commitAssignment();

    }

    template<typename T>
    typename DFV<T>::DFVImpl &DFV<T>::DFVImpl::operator=(const T &data) {
#ifdef DFCPP_NUMA_ALLOC
        if(_data && _threadWorker && _threadWorker->numaNode() != _numaNode) {
            _hoardNuma.free(_numaNode, _data, sizeof(T));
            _data = nullptr;
        }
        if(_data == nullptr) {
            _numaNode = _threadWorker == nullptr ? 0 : _threadWorker->numaNode();       // 如果在主线程赋值，则默认在0节点
            auto id = _threadWorker == nullptr ? 0 : _threadWorker->id();
            _data = (T*)_hoardNuma.allocOnNumaNodeWithThreadID(_numaNode, id, sizeof(T));
        }

        new (_data) T(data);
#else
        _data = new T(data);
#endif
#ifdef  DFCPP_DFV_COUNT
        _counter = _resetCounter;       // 当DFV被赋值时，重置计数
#endif

        commitAssignment();
        return *this;
    }

    template<typename T>
    DFV<T>::DFVImpl::~DFVImpl() {
        if(_data) {
#ifdef DFCPP_NUMA_ALLOC
            _hoardNuma.free(_numaNode, _data, sizeof(T));
#else
            delete (T*)_data;
#endif
            _data = nullptr;
        }
    }
}




#endif //DFCPP_EXECUTOR_HPP
