//
// Created by Gboom on 2022/10/19.
//

#ifndef DFCPP_NODE_HPP
#define DFCPP_NODE_HPP

#include "NumaNum.hpp"
#include <string>
#include <functional>
#include <variant>
#include <string.h>
#include <vector>

namespace DFCPP{

    struct DFVComm;
    template<typename T>
        class DFV;
    class DynamicTask;
    class Graph;
    class Topology;

    // Node is internal class
    class Node{
        friend class Graph;
        friend class Executor;
        friend class ExecutorNuma;

        template<typename T>
        friend class DFV;
    public:
        struct StaticWork{
            template<typename C>
            explicit StaticWork(C&& c) : work{std::forward<C>(c)} {}
            std::function<void()> work;
        };
        struct DynamicWork{
            template<typename C>
            explicit DynamicWork(C&& c) : work{std::forward<C>(c)} {}
            std::function<void(DynamicTask&)> work;
        };
        struct ConditionWork{
            template<typename C>
            explicit ConditionWork(C&& c) : work{std::forward<C>(c)} {}
            std::function<size_t()> work;
        };

        template<typename ...Args>
        Node(size_t n, Graph* g, Args&&... args):
                _handle(std::forward<Args>(args)...),
                _dataDependence(n),//表示多少个入度？
                _controlDependence(0),
                _joinCounter(n),//表示有几个入度?
                _graph(g),
                _topology(nullptr),
                _inputDFVs(n)//表示多少个入度?
                {}


        void name(std::string n) { _name = std::move(n);}
        std::string name() {return _name;}
        size_t numDependence() {return _dataDependence + _controlDependence;}
        size_t numDataDependence() {return _dataDependence;}
        size_t numControlDependence() {return _controlDependence;}
        size_t getMaxNumaNode() {
            size_t index = 0;
            size_t dataCount[NUMANUM];
            memset(dataCount, 0, sizeof(dataCount));
            for(auto dfv : _inputDFVs) {
                dataCount[dfv->_numaNode] += dfv->_dataSize;
            }

            for(auto i = 1; i < NUMANUM; i++) {
                if(dataCount[i] > dataCount[index])
                    index = i;
            }
            return index;
        }

        // task type / variant index
        static constexpr auto STATIC = 1;
        static constexpr auto DYNAMIC = 2;
        static constexpr auto CONDITION = 3;

        bool setnodeready(){//新增
        return _joinCounter.fetch_sub(1) == 1; 
        }


    private:

        std::variant<std::monostate, StaticWork, DynamicWork, ConditionWork> _handle;
        std::string _name;
        size_t _dataDependence;         // won't change during executing
        size_t _controlDependence;     // won't change during executing
        std::atomic_uint64_t _joinCounter{0};
        Graph* _graph;
        Topology* _topology;
        std::vector<Node*>  _successors;    // won't change during executing
        std::vector<DFVComm*> _inputDFVs;           // 输入DFV

        void setDataDependence(size_t n) {_dataDependence = n; _joinCounter += n;}
        void increaseControlDep() {_controlDependence++; _joinCounter++;}
        bool decreaseJoinCounter() {
            return _joinCounter.fetch_sub(1) == 1;
        }
        void reset() {
            _joinCounter = _dataDependence + _controlDependence;
        }
        void emplaceSuccessor(Node* s){
            _successors.emplace_back(s);
        }

        void emplaceInputDFV(DFVComm* dfvComm, size_t i) {
            _inputDFVs[i] = dfvComm;
        }

    };

//    ---------------------------DFV-------------
    template<typename T>
    void DFV<T>::emplaceTarget(Node *node) {
        // fixme: 类之间耦合太多了
        if(node->_graph == this->_dataPtr->_graph) {        // 动态任务的输出不能作为子任务的输入
            _dataPtr->_nodes.emplace_back(node);
#ifdef DFCPP_DFV_COUNT
            this->_dataPtr->_resetCounter++;
#endif
        } else {                                            // 不是来自同一层的DFV，则说明该DFV已经就绪
            --node->_joinCounter;
            --node->_dataDependence;
#ifdef DFCPP_DFV_COUNT
            this->_dataPtr->_counter++;                     // 动态任务创建的子任务直接添加引用计数，不递增_resetCounter
#endif
        }
    }


}

#endif //DFCPP_NODE_HPP
