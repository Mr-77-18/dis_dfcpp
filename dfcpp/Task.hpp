//
// Created by Gboom on 2022/10/18.
//

#ifndef DFCPP_TASK_HPP
#define DFCPP_TASK_HPP

#include "Node.hpp"


namespace DFCPP{
    /**
     * @brief   接口类，操作任务的句柄
     */
    class Task{
        friend class Graph;
    public:
        // 设置任务的名字
        void name(std::string n) {_node->name(std::move(n));}
        // 获取任务的名字
        std::string name() {return _node->name();}
        // 获取任务的总依赖数
        size_t numDependence() { return _node->numDependence();}
        // 获取任务的数据依赖数量，即输入DFV的数量（不包括其它图创建的DFV）
        size_t numDataDependence() {return _node->numDataDependence();}
        // 获取控制依赖数
        size_t numControlDependence() {return _node->numControlDependence();}

    private:
        explicit Task(Node* n) : _node(n) {}
        Node* const _node;
    };

}

#endif //DFCPP_TASK_HPP
