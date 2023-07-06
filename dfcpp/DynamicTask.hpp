//
// Created by Gboom on 2022/10/20.
//

#ifndef DFCPP_DYNAMICTASK_HPP
#define DFCPP_DYNAMICTASK_HPP

#include "Graph.hpp"

namespace DFCPP{

    /**
     * @brief   接口类，用于在图的运行过程中创建新的DFV和任务。
     * 继承自DFCPP::Graph，创建DFV和任务的接口请查看DFCPP::Graph
     */
    class DynamicTask : public Graph {
        friend class Executor;
        friend class ExecutorNuma;
    public:
        DynamicTask(const DynamicTask&) = delete;
        DynamicTask(DynamicTask&&) = delete;
        DynamicTask& operator= (const DynamicTask&) = delete;
        DynamicTask& operator= (DynamicTask&&) = delete;

        /**
         * @brief       DynamicTask本身也作为一个任务，join()表示DynamicTask的结束需要等待所有可执行的子任务结束后。
         * @attention   join()方法并不会堵塞DynamicTask任务本身，只是在任务结束后，需要等待所有子任务结束后，动态任务才会触发新的任务。
         * @attention   这是DynamicTask的默认方式。
         *
         * @code
         * // childTask结束后task2能够被调度运行，虽然其输入依赖a的赋值先于childTask的创建。
         * void f(DynamicTask& dt, DFV<int> a) {
         *      a = 1;
         *      auto childTask = dt.emplace([](){});
         *      dt.join();
         * }
         * auto a = dfgraph.createDFV<int>();
         * auto task1 = dfgraph.emplace(f, std::make_tuple(), std::make_tuple(a));
         * auto task2 = dfgraph.emplace([](int a){}, std::make_tuple(a));
         * @endcode
         */
        void join() {
            _joinable = true;
        }
        /**
         * @brief       DynamicTask本身也作为一个任务，join()表示DynamicTask的结束无需等待所有可执行的子任务结束后。
         * @attention   任务函数执行完毕之后，DynamicTask就被视为结束。
         * @attention   DynamicTask的默认选择join，如要更改，需要手动调用detach()。
         *
         * @code
         * // task2可以与childTask并行执行。
         * void f(DynamicTask& dt, DFV<int> a) {
         *      a = 1;
         *      auto childTask = dt.emplace([](){});
         *      dt.detach();
         * }
         * auto a = dfgraph.createDFV<int>();
         * auto task1 = dfgraph.emplace(f, std::make_tuple(), std::make_tuple(a));
         * auto task2 = dfgraph.emplace([](int a){}, std::make_tuple(a));
         * @endcode
         */
        void detach() {
            _joinable = false;
        }

    private:
        /**
         * @brief   用户不可以自己构造DynamicTask对象，该对象在运行过程中由DFCPP提供。
         * @param parent
         */
        explicit DynamicTask(Graph* parent) :
            Graph(),
            _parent(parent),
            _joinable{true}
        {}

        Graph* _parent;
        bool _joinable;     // _joinable will be accessed only in one thread
    };


}


#endif //DFCPP_DYNAMICTASK_HPP
