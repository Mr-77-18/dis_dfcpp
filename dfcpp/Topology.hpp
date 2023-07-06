//
// Created by Gboom on 2022/10/31.
//

#ifndef DFCPP_TOPOLOGY_HPP
#define DFCPP_TOPOLOGY_HPP

#include <vector>
#include <future>
#include <atomic>
#include <functional>


namespace DFCPP {
    class Node;
    class Graph;
    class Topology {
        friend class Executor;
        friend class ExecutorNuma;
    public:
        explicit Topology(Graph* g, size_t n): _graph(g), _join_counter(0), _epochs(n){}
        std::future<void> get_future() { return _promise.get_future();}
    private:
        Graph* _graph;                      // 图
        std::promise<void> _promise;
        std::atomic_uint64_t _join_counter;
        std::atomic_uint64_t _epochs;       // 要运行的次数
        std::function<void()>    _epilogue;
    };
}



#endif //DFCPP_TOPOLOGY_HPP
