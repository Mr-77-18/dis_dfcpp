//
// Created by Gboom on 2022/10/18.
//

#ifndef DFCPP_GRAPH_HPP
#define DFCPP_GRAPH_HPP

#include "DFV.hpp"

#include "Task.hpp"
#include "types.hpp"

#include "global.hpp"

#include <utility>
#include <future>
#include <iostream>


namespace DFCPP {

    class Node;
    class Topology;

    /**
     * @brief   接口类。用于创建DFV和任务。
     * DFCPP::DFGraph和 DFCPP::DynamicTask都集成了此类。
     */
    class Graph {

        friend class Executor;
        friend class ExecutorNuma;
        friend struct DFVComm;

    public:

        /**
         * @brief       创建一个T类型的DFV
         * @tparam T    DFV的数据类型
         * @return      DFV<T>的句柄
         *
         * @code{.cpp}
         * // 创建一个int类型的DFV
         * DFCPP::DFGraph dfgraph;
         * DFCPP::DFV<int> dfv = dfgraph.createDFVs<int>();
         * @endcode
         */
        template<typename T, std::enable_if_t<!is_any_DFV<T>, void>* = nullptr>
        [[nodiscard]] DFV<T> createDFV() {
            return DFV<T>(this);
        }

        template<typename T, typename ...Args, std::enable_if_t<!is_any_DFV<T>, void>* = nullptr>
        [[nodiscard]] DFV<T> createDFV(Args&&... args) {
            return DFV<T>(this, std::forward<Args>(args)...);
        }

        /**
         * @brief       创建n个同为T类型的DFV
         * @tparam T    DFV的数据类型
         * @param n     DFV的个数
         * @return      包含n个DFV<T>的vector
         *
         * @code{.cpp}
         * // 创建3个int类型的DFV
         * DFCPP::DFGraph dfgraph;
         * std::vector<DFCPP::DFV<int>> dfvs = dfgraph.createDFVs<int>(3);
         * @endcode
         */
        template<typename T, std::enable_if_t<!is_any_DFV<T>, void>* = nullptr>
        [[nodiscard]] std::vector<DFV<T>> createDFVs(size_t n) {
            std::vector<DFV<T>> temp;
            for(size_t i = 0; i < n; i++) {
                auto dfv = DFV<T>(this);
                temp.template emplace_back(std::move(dfv));
            }
            return temp;
        }

        /**
         * @brief   创建多个相同或不同类型的DFV
         * @tparam  Args DFV的数据类型
         * @return  包含多个DFV的tuple
         *
         * @code{.cpp}
         * // 创建3个类型分别为int、float、double的DFV
         * DFCPP::DFGraph dfgraph;
         * auto [a, b, c] = dfgraph.createDFV<int, float, double>();
         * @endcode
         */
        template<typename ...Args, std::enable_if_t<(sizeof...(Args) > 1), void>* =nullptr, std::enable_if_t<!is_any_DFV<Args...>, void>* = nullptr>
        [[nodiscard]] std::tuple<DFV<Args>...> createDFV() {
            return std::make_tuple(DFV<Args>(this)...);
        }


        Graph() = default;
        ~Graph();

        // ------------------------static task---------------------------------

        /**
         * @brief       创建一个既无输入又无输出的静态任务
         * @tparam C    调用形式为void(void)的可调用类型
         * @tparam func
         * @return      DFCPP::task任务句柄
         *
         * @code{.cpp}
         * DFCPP::task = dfgraph.emplace([](){});
         * @endcode
         */
        template<typename C,
                std::enable_if_t< is_special_static<C>, void>* = nullptr
                >
        Task emplace(C func);

        /**
         * @brief           创建一个只有输入无输出的静态任务
         * @tparam  C       形式为void(const ArgIns&...)的可调用类型
         * @tparam  ArgIns  输入数据类型
         * @tparam  ins     任务的输入依赖DFV，是包含一个或多个DFV的tuple
         * @return          DFCPP::task 任务句柄
         *
         * @code{.cpp}
         * auto a = dfgraph.createDFV<int>();
         * dfgraph.emplace([](int aa){ std::cout << aa << std::endl; }, std::make_tuple(a));
         * @endcode
         */
        template<typename C,
                typename ... ArgIns,
                std::enable_if_t<is_sink_static<C, ArgIns...>,void>* = nullptr
                >
        Task emplace(C, std::tuple<DFV<ArgIns>...> ins);

        /**
         * @brief           创建一个既有输入也有输出的静态任务
         * @tparam C        形式为void(const ArgIns&..., DFV<ArgOuts>...)的可调用类型
         * @tparam ArgIns   输入数据类型
         * @tparam ArgOuts  输出数据类型
         * @param ins       任务的输入DFV，是包含一个或多个DFV的tuple
         * @param outs      任务的输出DFV，是包含一个或多个DFV的tuple
         * @return          DFCPP::task任务句柄
         *
         * @code{.cpp}
         * auto [a, b, c] = dfgraph.createDFV<int, int, int>();
         * auto task = dfgraph.emplace(
         *  [](const int& aa, const int bb, DFV<int> cc){ cc = aa + bb; },
         *  std::make_tuple(a,b),
         *  std::make_tuple(c)
         * );
         *
         * @endcode
         *
         * @attention   如果要创建只有输出没有输入的静态任务，可以将输入ins设置为空std::tuple即可。如下所示
         * @code{.cpp}
         * auto a = dfgraph.createDFV<int>();
         * auto task = dfgrapg.emplace([](DFV<int> aa){ aa = 3; }, std::make_tuple(), std::make_tuple(a));
         * @endcode
         */
        template<typename C,
                typename ... ArgIns,
                typename ... ArgOuts,
                std::enable_if_t<is_normal_static<C>(MetaArg<ArgIns...>{}, MetaArg<ArgOuts...>{}), void>* = nullptr
                >
        Task emplace(C, std::tuple<DFV<ArgIns>...> ins, std::tuple<DFV<ArgOuts>...> outs);

        // ------------------------dynamic task---------------------------------

        /**
         * @brief       创建一个既无输入又无输入的动态任务。动态任务用于在运行过程中根据需要创建新的任务。
         * @tparam C    形式为void(DynamicTask&)的可调用类型
         * @return      DFCPP::task任务句柄
         *
         * @code
         * auto task = dfgraph.emplace([](DynamicTask& dt){
         *  dt.emplace([](){});
         * });
         * @endcode
         */
        template<typename C,
                std::enable_if_t<is_special_dynamic<C>, void>* = nullptr
                >
        Task emplace(C);

        /**
         * @brief           创建一个只有输入的动态任务。动态任务用于在运行过程中根据需要创建新的任务。
         * @tparam C        形式为void(DynamicTask&, const ArgIns&...)的可调用类型
         * @tparam ArgIns   输入数据类型
         * @return          DFCPP::task任务句柄
         *
         * @code
         * auto a = dfgraph.createDFV<int>();
         * auto task = dfgraph.emplace([](DynamicTask& dt, int aa){
         *  std::cout << aa << std::endl;
         *  dt.emplace([](){});
         * });
         * @endcode
         */
        template<typename C,
                typename ... ArgIns,
                std::enable_if_t<is_sink_dynamic<C, ArgIns...>, void>* = nullptr
                >
        Task emplace(C, std::tuple<DFV<ArgIns>...>);

        /**
         * @brief           创建一个既有输入也有输出的动态任务。动态任务用于在运行过程中创建新的任务。
         * @tparam C        形式为void(DynamicTask&, const ArgIns&..., DFV<ArgOuts>...)的可调用类型
         * @tparam ArgIns   输入数据类型
         * @tparam ArgOuts  输出数据类型
         * @return          DFCPP::task任务句柄
         *
         * @code
         * auto [a, b] = dfgraph.createDFV<int, int>();
         * auto task = dfgraph.emplace([](DynamicTask& dt, int aa, DFV<int> bb){
         *      dt.emplace([](){});
         * }, std::make_tuple(a), std::make_tuple(b));
         * @endcode
         *
         * @attention       如果要创建只有输出没有输入的静态任务，可以将输入ins设置为空std::tuple即可。如下所示
         * @code
         * auto a = dfgraph.createDFV<int>();
         * auto task = dfgraph.emplace([](DynamicTask& dt, DFV<int> aa){
         *      dt.emplace([](){});
         * }, std::make_tuple(), std::make_tuple(a));
         * @endcode
         *
         * @attention
         * 动态任务本身的输出DFV不应作为子任务的输入。
         */
        template<typename C,
                typename ... ArgIns,
                typename ... ArgOuts,
                std::enable_if_t<is_normal_dynamic<C>(MetaArg<ArgIns...>{}, MetaArg<ArgOuts...>{}), void>* = nullptr
                >
        Task emplace(C, std::tuple<DFV<ArgIns>...>, std::tuple<DFV<ArgOuts>...>);

        /**
         * @brief           创建一个只有输入的动态任务。这个接口主要是方便子任务直接引用动态任务的输入DFV。
         * @tparam C        形式为void(DynamicTask&, std::tuple<DFV<ArgIns>... >)的可调用类型
         * @tparam ArgIns   输入数据类型
         * @return          DFCPP::task任务句柄
         *
         * @code
         * auto a = dfgraph.createDFV<int>();
         * auto task = dfgraph.emplace([](DynamicTask& dt, std::tuple<DFV<int>> ins){
         *      dt.emplace([](int aaa){}, ins);
         * }, std::make_tuple(a));
         * @endcode
         *
         * @attention
         * 动态任务的输入DFV不应在任务本身或子任务中重复赋值。
         */
        template<typename C,
                typename ...ArgIns,
                std::enable_if_t<is_sink_dynamic_with_tuple<C, ArgIns...>, void>* = nullptr
                >
        Task emplace(C, std::tuple<DFV<ArgIns>...>);

        /**
         * @brief           创建一个既有输入又有输出的动态任务。这个接口主要是方便子任务直接引用动态任务的输入DFV。
         * @tparam C        形式为void(DynamicTask&, std::tuple<DFV<ArgIns>... >， DFV<ArgOuts>...)的可调用类型
         * @tparam ArgIns   输入数据类型
         * @tparam ArgOuts  输出数据类型
         * @return          DFCPP::task任务句柄
         *
         * @code
         * auto [a, b] = dfgraph.createDFV<int, int>();
         * auto task = dfgraph.emplace([](DynamicTask& dt, std::tuple<DFV<int>> ins, DFV<int> bb){
         *      dt.emplace([](int aaa, DFV<int> bbb){}, ins, std::make_tuple(bb));
         * }, std::make_tuple(a), std::make_tuple(b));
         * @endcode
         *
         * @attention
         * 动态任务的输入DFV不应在任务本身或子任务中重复赋值，其输出DFV不应作为子任务的输入。
         */
        template<typename C,
                typename ...ArgIns,
                typename ...ArgOuts,
                std::enable_if_t<is_normal_dynamic_with_tuple<C>(MetaArg<ArgIns...>{}, MetaArg<ArgOuts...>{}), void>* = nullptr
                >
        Task emplace(C, std::tuple<DFV<ArgIns>...>, std::tuple<DFV<ArgOuts>...>);

        // ------------------------condition task---------------------------------

        /**
         * @brief       创建一个既无输入有无输出的谓词任务
         * @tparam C    形式为size_t(void)的可调用类型。谓词任务必须返回一个size_t,用于选择分支。
         * @return      DFCPP::task任务句柄
         *
         * @code
         * auto task = dfgraph.emplace([](){ return 0; });
         * @endcode
         */
        template<typename C,
                std::enable_if_t<is_special_condition<C>, void>* = nullptr
                >
        Task emplace(C func);

        /**
         * @brief           创建一个只有输入的谓词任务
         * @tparam C        形式为size_t(const ArgIns&...)的可调用类型。谓词任务必须返回一个size_t,用于选择分支。
         * @tparam ArgIns   输入数据类型
         * @return          DFCPP::task任务句柄
         *
         * @code
         * auto a = dfgraph.createDFV<int>();
         * auto task = dfgraph.emplace([](int a){ return a; }, std::make_tuple(a));
         * @endcode        */
        template<typename C,
                typename ... ArgIns,
                std::enable_if_t<is_sink_condition<C, ArgIns...>, void>* = nullptr
                >
        Task emplace(C, std::tuple<DFV<ArgIns>...>);

        /**
         * @brief           创建一个既有输入也有输出的谓词任务
         * @tparam C        形式为size_t(const ArgIns&...，)的可调用类型。谓词任务必须返回一个size_t,用于选择分支。
         * @tparam ArgIns   输入数据类型
         * @tparam ArgOuts  输出数据类型
         * @return          DFCPP::task任务句柄
         * @code
         * auto [a, b] = dfgraph.createDFV<int， int>();
         * auto task = dfgraph.emplace(
         *      [](int aa, DFV<int> bb){
         *          bb = aa; return aa;
         * }, std::make_tuple(a), std::make_tuple(b));
         */
        template<typename C,
                typename ... ArgIns,
                typename ... ArgOuts,
                std::enable_if_t<is_normal_condition<C>(MetaArg<ArgIns...>{}, MetaArg<ArgOuts...>{}), void>* = nullptr
                >
        Task emplace(C, std::tuple<DFV<ArgIns>...>, std::tuple<DFV<ArgOuts>...>);

        /**
         * @brief       建立谓词任务与分支任务之间的控制依赖关系。
         * @tparam      谓词任务，其返回值就是选择分支任务的下标，如果返回值超出范围，则哪一个分支也不会被选择。
         * @tparam      分支任务vector。
         *
         * @code
         * auto prediction = dfgraph.emplace([](){return 0;});
         * auto task1 = dfgraph.emplace([](){});
         * auto task2 = dfgraph.emplace([](){});
         * dfgraph.condition(prediction, {task1, task2});
         * @endcode
         */
        static void condition(const Task&, std::vector<Task>);

        void cre_new_graph(std::vector<int> _indexs){//新增_lsh
            _nodes.clear();
            for (auto i : _indexs) {
                _nodes.push_back(gl.get_node(i));
            }
        }

    private:
        std::vector<Node*> _nodes;
        std::vector<DFVComm*> _DFVAssigned;         // 已经赋值的DFV
        std::atomic_uint64_t _joinCounter{0};
        Topology* _topology{nullptr};
        std::mutex _mutex;

        // 建立Node与DFV之间的关系
        template<typename ...ArgIns, size_t... InsIndex>
        static void _connectDFVAndNode(Node*, std::tuple<DFV<ArgIns>...> ins, std::index_sequence<InsIndex...>);

        // special task does not need a helper function;

        // create the sink static work
        template<typename C, typename ...ArgIns, size_t... InsIndex>
        static auto _createStaticWork(C c, std::tuple<DFV<ArgIns>...> ins, std::index_sequence<InsIndex...>);

        // create the normal static work
        template<typename C, typename ... ArgIns, typename ... ArgOuts, size_t ... InsIndex, size_t ... OutsIndex>
        static auto _createStaticWork(C c, std::tuple<DFV<ArgIns>...> ins, std::tuple<DFV<ArgOuts>...> outs,
                                      std::index_sequence<InsIndex...>, std::index_sequence<OutsIndex...>);

        // create the sink dynamic work
        template<typename C, typename ...ArgIns, size_t... InsIndex>
        static auto _createDynamicWork(C c, std::tuple<DFV<ArgIns>...> ins,
                                       std::index_sequence<InsIndex...>);

        // create the normal dynamic work
        template<typename C, typename ... ArgIns, typename ... ArgOuts, size_t ... InsIndex, size_t ... OutsIndex>
        static auto _createDynamicWork(C c, std::tuple<DFV<ArgIns>...> ins, std::tuple<DFV<ArgOuts>...> outs,
                                       std::index_sequence<InsIndex...>, std::index_sequence<OutsIndex...>);

        template<typename C, typename ...ArgIns, typename ...ArgOuts, size_t... OutsIndex>
        static auto _createDynamicWithTupleWork(C, std::tuple<DFV<ArgIns>...>, std::tuple<DFV<ArgOuts>...>, std::index_sequence<OutsIndex...>);

        // create the sink condition work
        template<typename C, typename ...ArgIns, size_t... InsIndex>
        static auto _createConditionWork(C c, std::tuple<DFV<ArgIns>...> ins, std::index_sequence<InsIndex...>);

        // create the normal condition work
        template<typename C, typename ... ArgIns, typename ... ArgOuts, size_t ... InsIndex, size_t ... OutsIndex>
        static auto _createConditionWork(C c, std::tuple<DFV<ArgIns>...> ins, std::tuple<DFV<ArgOuts>...> outs,
                                         std::index_sequence<InsIndex...>, std::index_sequence<OutsIndex...>);

    //    ---------------------------------- for DFV----------------------------
        // 当DFV在非工作线程中被赋值时，视为graph的初始输入，将在图开始运行的时候触发任务。
        void setReadyDFV(DFVComm *dfv);

    //    ---------------------------------- for Executor----------------------------
        // 获取所有已就绪任务
        void getSourceTask(std::vector<Node*>&);

    };

    // special static task
    template<typename C,
            std::enable_if_t< is_special_static<C>, void>*>
    Task Graph::emplace(C func) {
        auto node = new Node(0, this, std::in_place_index_t<Node::STATIC>{}, func);
        _nodes.emplace_back(node);
        return Task(node);
    }

    template<typename C,
            typename... ArgIns,
            std::enable_if_t<is_sink_static<C, ArgIns...>,void>*>
    Task Graph::emplace(C c, std::tuple<DFV<ArgIns>...> ins) {
        auto&& func = _createStaticWork(c, ins, std::make_index_sequence<sizeof...(ArgIns)>{});
        auto node = new Node(sizeof...(ArgIns), this, std::in_place_index_t<Node::STATIC>{}, std::move(func));
        _connectDFVAndNode(node, ins, std::make_index_sequence<sizeof...(ArgIns)>{});
        _nodes.emplace_back(node);
        return Task(node);
    }

    template<typename C,
            typename... ArgIns,
            typename... ArgOuts, std::enable_if_t<is_normal_static<C>(MetaArg<ArgIns...>{}, MetaArg<ArgOuts...>{}), void>*>
    Task Graph::emplace(C c, std::tuple<DFV<ArgIns>...> ins, std::tuple<DFV<ArgOuts>...> outs) {
        auto&& func = _createStaticWork(c, ins, outs, std::make_index_sequence<sizeof...(ArgIns)>{}, std::make_index_sequence<sizeof...(ArgOuts)>{});
        auto node = new Node(sizeof...(ArgIns), this, std::in_place_index_t<Node::STATIC>{}, func);
        gl.insert_node(node);//新增_lsh
        _connectDFVAndNode(node, ins, std::make_index_sequence<sizeof...(ArgIns)>{});
        _nodes.emplace_back(node);
        return Task(node);
    }

    template<typename C,
            std::enable_if_t< is_special_dynamic<C>, void>*>
    Task Graph::emplace(C func) {
        auto node = new Node(0, this, std::in_place_index_t<Node::DYNAMIC>{}, func);
        _nodes.emplace_back(node);
        return Task(node);
    }

    template<typename C,
            typename... ArgIns,
            std::enable_if_t<is_sink_dynamic<C, ArgIns...>,void>*>
    Task Graph::emplace(C c, std::tuple<DFV<ArgIns>...> ins) {
        auto&& func = _createDynamicWork(c, ins, std::make_index_sequence<sizeof...(ArgIns)>{});
        auto node = new Node(sizeof...(ArgIns), this, std::in_place_index_t<Node::DYNAMIC>{}, func);
        _connectDFVAndNode(node, ins, std::make_index_sequence<sizeof...(ArgIns)>{});
        _nodes.template emplace_back(node);
        return Task(node);
    }

    template<typename C, typename... ArgIns,
            typename... ArgOuts,
            std::enable_if_t<is_normal_dynamic<C>(MetaArg<ArgIns...>{}, MetaArg<ArgOuts...>{}), void>*>
    Task Graph::emplace(C c, std::tuple<DFV<ArgIns>...> ins, std::tuple<DFV<ArgOuts>...> outs) {
        auto&& func = _createDynamicWork(c, ins, outs, std::make_index_sequence<sizeof...(ArgIns)>{}, std::make_index_sequence<sizeof...(ArgOuts)>{});
        auto node = new Node(sizeof...(ArgIns), this, std::in_place_index_t<Node::DYNAMIC>{}, func);
        _connectDFVAndNode(node, ins, std::make_index_sequence<sizeof...(ArgIns)>{});
        _nodes.template emplace_back(node);
        return Task(node);
    }

    template<typename C,
            typename ...ArgIns,
            std::enable_if_t<is_sink_dynamic_with_tuple<C, ArgIns...>, void>*>
    Task Graph::emplace(C c, std::tuple<DFV<ArgIns>...> ins) {
        auto&& func = [c, ins](DynamicTask& dt){
            c(dt, ins);
        };
        auto node = new Node(sizeof...(ArgIns), this, std::in_place_index_t<Node::DYNAMIC>{}, func);
        _connectDFVAndNode(node, ins, std::make_index_sequence<sizeof...(ArgIns)>{});
        _nodes.template emplace_back(node);
        return Task(node);
    }

    template<typename C,
            typename ...ArgIns,
            typename ...ArgOuts,
            std::enable_if_t<is_normal_dynamic_with_tuple<C>(MetaArg<ArgIns...>{}, MetaArg<ArgOuts...>{}), void>*>
    Task Graph::emplace(C c, std::tuple<DFV<ArgIns>...> ins, std::tuple<DFV<ArgOuts>...> outs) {
        auto&& func = _createDynamicWithTupleWork(c, ins, outs, std::make_index_sequence<sizeof...(ArgOuts)>{});
        auto node = new Node(sizeof...(ArgIns), this, std::in_place_index_t<Node::DYNAMIC>{}, func);
        _connectDFVAndNode(node, ins, std::make_index_sequence<sizeof...(ArgIns)>{});
        _nodes.template emplace_back(node);
        return Task(node);
    }

    template<typename C, std::enable_if_t< is_special_condition<C>, void>*>
    Task Graph::emplace(C func) {
        auto node = new Node(0, this, std::in_place_index_t<Node::CONDITION>{}, func);
        _nodes.template emplace_back(node);
        return Task(node);
    }

    template<typename C,
            typename... ArgIns,
            std::enable_if_t<is_sink_condition<C, ArgIns...>,void>*>
    Task Graph::emplace(C c, std::tuple<DFV<ArgIns>...> ins) {
        auto&& func = _createConditionWork(c, ins, std::make_index_sequence<sizeof...(ArgIns)>{});
        auto node = new Node(sizeof...(ArgIns), this, std::in_place_index_t<Node::CONDITION>{}, func);
        _connectDFVAndNode(node, ins, std::make_index_sequence<sizeof...(ArgIns)>{});
        _nodes.template emplace_back(node);
        return Task(node);
    }

    template<typename C,
            typename... ArgIns,
            typename... ArgOuts,
            std::enable_if_t<is_normal_condition<C>(MetaArg<ArgIns...>{}, MetaArg<ArgOuts...>{}), void>*>
    Task Graph::emplace(C c, std::tuple<DFV<ArgIns>...> ins, std::tuple<DFV<ArgOuts>...> outs) {
        auto&& func = _createConditionWork(c, ins, outs, std::make_index_sequence<sizeof...(ArgIns)>{}, std::make_index_sequence<sizeof...(ArgOuts)>{});
        auto node = new Node(sizeof...(ArgIns), this, std::in_place_index_t<Node::CONDITION>{}, func);
        _connectDFVAndNode(node, ins, std::make_index_sequence<sizeof...(ArgIns)>{});
        _nodes.emplace_back(node);
        return Task(node);
    }

    void Graph::condition(const Task& prediction, std::vector<Task> branches) {
        auto p = prediction._node;
        for(auto& branch : branches) {
            branch._node->increaseControlDep();
            p->emplaceSuccessor(branch._node);
        }
    }


    Graph::~Graph() {
        for(auto n : _nodes) {
            delete n;
        }
    }

    // it's ok without locking
    void Graph::getSourceTask(std::vector<Node*>& tasks) {
        std::vector<DFVComm*> dfvs;
        {
            std::lock_guard<std::mutex> lockGuard(_mutex);
            std::swap(dfvs, _DFVAssigned);      // 获取已赋值的DFV
        }
        for(auto dfv : dfvs) {
            for(auto n : dfv->_nodes) {
                n->_joinCounter--;
            }
        }
        // 用户应该保证：在graph开始执行后，其拓扑结构不再改变
        for(auto node : _nodes) {
            if(node->_joinCounter == 0) {//_joinCounter可以理解为入度
                tasks.emplace_back(node);
            }
        }
    }

    template<typename... ArgIns, size_t... InsIndex>
    void Graph::_connectDFVAndNode(Node * node, std::tuple<DFV<ArgIns>...> ins, std::index_sequence<InsIndex...>) {
        (std::get<InsIndex>(ins).emplaceTarget(node),...);
        (node->emplaceInputDFV(static_cast<DFVComm *>(std::get<InsIndex>(ins)._dataPtr.get()), InsIndex), ...);
    }

    // create the sink static work
    template<typename C, typename ...ArgIns, size_t... InsIndex>
    auto Graph::_createStaticWork(C c, std::tuple<DFV<ArgIns>...> ins, std::index_sequence<InsIndex...>) {
        return [c, ins]() mutable{
            c(std::get<InsIndex>(ins).get()...);
        };
    }

    // create the normal static work
    template<typename C, typename ... ArgIns, typename ... ArgOuts, size_t ... InsIndex, size_t ... OutsIndex>
    auto Graph::_createStaticWork(C c, std::tuple<DFV<ArgIns>...> ins, std::tuple<DFV<ArgOuts>...> outs,
                                  std::index_sequence<InsIndex...>, std::index_sequence<OutsIndex...>) {
        return [c, ins, outs]() mutable {
            c(std::get<InsIndex>(ins).get()..., std::get<OutsIndex>(outs)...);
        };
    }

    // create the sink dynamic work
    template<typename C, typename ...ArgIns, size_t... InsIndex>
    auto Graph::_createDynamicWork(C c, std::tuple<DFV<ArgIns>...> ins,
                                   std::index_sequence<InsIndex...>) {
        return [c, ins](DynamicTask& dt) mutable{
            c(dt, std::get<InsIndex>(ins).get()...);
        };
    }

    // create the normal dynamic work
    template<typename C, typename ... ArgIns, typename ... ArgOuts, size_t ... InsIndex, size_t ... OutsIndex>
    auto Graph::_createDynamicWork(C c, std::tuple<DFV<ArgIns>...> ins, std::tuple<DFV<ArgOuts>...> outs,
                                   std::index_sequence<InsIndex...>, std::index_sequence<OutsIndex...>) {
        return [c, ins, outs](DynamicTask& dt) mutable {
            c(dt, std::get<InsIndex>(ins).get()..., std::get<OutsIndex>(outs)...);
        };
    }

    template<typename C, typename ...ArgIns, typename ...ArgOuts, size_t... OutsIndex>
    auto Graph::_createDynamicWithTupleWork(C c, std::tuple<DFV<ArgIns>...> ins, std::tuple<DFV<ArgOuts>...> outs, std::index_sequence<OutsIndex...>) {
        return [c, ins, outs] (DynamicTask& dt) {
            c(dt, ins, std::get<OutsIndex>(outs)...);
        };
    }

    // create the sink condition work
    template<typename C, typename ...ArgIns, size_t... InsIndex>
    auto Graph::_createConditionWork(C c, std::tuple<DFV<ArgIns>...> ins, std::index_sequence<InsIndex...>) {
        return [c, ins]() mutable -> size_t{
            return c(std::get<InsIndex>(ins).get()...);
        };
    }

    // create the normal condition work
    template<typename C, typename ... ArgIns, typename ... ArgOuts, size_t ... InsIndex, size_t ... OutsIndex>
    auto Graph::_createConditionWork(C c, std::tuple<DFV<ArgIns>...> ins, std::tuple<DFV<ArgOuts>...> outs,
                                     std::index_sequence<InsIndex...>, std::index_sequence<OutsIndex...>) {
        return [c, ins, outs]() mutable -> size_t{
            return c(std::get<InsIndex>(ins).get()..., std::get<OutsIndex>(outs)...);
        };
    }

    // 添加就绪DFV
    void Graph::setReadyDFV(DFVComm *dfv) {
        std::lock_guard<std::mutex> lockGuard(_mutex);      // 主要防止工作线程与非工作线程的竞争。
        _DFVAssigned.emplace_back(dfv);
    }

}


#endif //DFCPP_GRAPH_HPP
