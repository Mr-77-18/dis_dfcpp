//
// Created by Gboom on 2022/10/18.
//

#ifndef DFCPP_DFV_HPP
#define DFCPP_DFV_HPP

#include <memory>
#include <vector>
#include <mutex>
#include <atomic>
#include <stdexcept>
#include "global.hpp"

namespace DFCPP{
    //extern Global& gl;

    class Node;
    class Graph;
    class Topology;

    // 空基类，主要用于判断任务参数类型
    class DFVAbstract {};

    // DFV基类
    struct DFVComm{
         std::string _name;
         std::vector<Node*> _nodes;
         Graph* _graph;
         int _numaNode = 0;
         size_t _dataSize;
         void* _data ;
#ifdef DFCPP_DFV_COUNT
         int _resetCounter{0};    //  DFV重置计数
         std::atomic_int64_t _counter{0};      // DFV 使用计数，如果为零则释放内存
#endif
         explicit DFVComm(Graph* g) : _graph(g), _data(nullptr){}
         void commitAssignment();       // in Executor.hpp;
         virtual void release() = 0;                // in Executor.hpp;
         void set_data(void* data){//新增_lsh
             _data = data;
         }
    };

    /**
     * @brief       接口类。
     * DFV用于数据流任务之间传递数据，可以作为数据流任务的输入或输出。其在数据流图中的位置为节点间的数据流依赖边。
     * DFV作为一个模板类，模板参数T为要传输的真实数据类型，必须满足复制构造。
     * @details
     * DFV作为一个接口类，实际上只是作为一个句柄，可以理解为底层数据的一个智能指针。
     * @attention
     * DFV的创建只能通过DFCPP::DFGraph和DFCPP::DynamicTask相关的接口。
     * @tparam T    要传输的数据类型
     */
    template<typename T>
    class DFV : public DFVAbstract{
        friend class Graph;
        friend class Node;
    private:
        struct DFVImpl : DFVComm{
            explicit DFVImpl(Graph* g): DFVComm(g){
                _dataSize = sizeof(T);
            }
            ~DFVImpl();     // in Executor.hpp

            template<typename ...Args>
            explicit DFVImpl(Graph* g, Args&&... args);     // in Executor.hpp

            //  DFV赋值不再包括触发任务的行为。触发任务的工作将由worker和graph负责
            DFVImpl& operator = (const T& data);        // in Executor.hpp
            void release() override;


            const T& get() {
                if(_data)
                    return *(T*)_data;
                else
                    throw std::runtime_error(_name + "has no value");//这里面出错了
            }
        };
        explicit DFV(Graph* g): _dataPtr(std::make_shared<DFVImpl>(g)){
            gl.insert_dfv(_dataPtr.get());//新增_lsh;
        }

        template<typename ...Args>
        explicit DFV(Graph* g, Args&&... args): _dataPtr(std::make_shared<DFVImpl>(g, std::forward<Args>(args)...))
        {}

    public:
        /**
         * @brief   创建一个引用相同数据的DFV。
         */
        DFV(const DFV&) = default;
        DFV(DFV&&) noexcept = default;
        DFV& operator = (const DFV&) = default;
        DFV& operator = (DFV&&) noexcept = default;

        void set(T value) {//新增_lsh
         if (_dataPtr->_data != nullptr) {
           delete static_cast<T*>(_dataPtr->_data);  // 释放之前的内存块
           _dataPtr->_data = nullptr;
         }
         _dataPtr->_data = new T(value);  // 动态分配内存并构造对象
        }

        /**
         * @brief           向一个DFV赋值。当一个任务的所有输入DFV全部被赋值时（还需满足控制依赖），该任务可以被调度执行。
         * @param data      要保存的数据
         * @attention
         * DFCPP采用延迟触发任务的方式，DFV的赋值不会立即触发新的任务，而是在任务函数结束后才会同一触发新的任务。
         * 另外，DFV支持重复赋值，用户需要DFV的读写不存在数据冒险，借助数据流图应该很容易做到这一点。
         */
        DFV& operator=(const T& data) {
            *_dataPtr = data;
            return *this;
        }

        std::string name() {
            return _dataPtr->_name;
        }

        void name(std::string name) {
            _dataPtr->_name = std::move(name);
        }

        /**
         * @brief   获取数据
         * @return
         */
        const T& get() {
            return _dataPtr->get();
        }

    private:
        std::shared_ptr<DFVImpl> _dataPtr;

        void emplaceTarget(Node* node);         // in Node.hpp
    };

}


#endif //DFCPP_DFV_HPP
