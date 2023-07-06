//
// Created by Gboom on 2022/10/18.
//

#ifndef DFCPP_DFGRAPH_HPP
#define DFCPP_DFGRAPH_HPP

#include "Graph.hpp"


namespace DFCPP{

    /**
     * @brief   接口类，用于创建DFV和新的任务，构建数据流图。
     * 继承自DFCPP::Graph。
     */
    class DFGraph : public Graph{
        friend class Executor;
        friend class ExecutorNuma;
    public:

        DFGraph() = default;
        DFGraph(const DFGraph&) = delete;
        DFGraph(DFGraph&&) =  delete;
        DFGraph& operator = (const DFGraph&) = delete;
        DFGraph& operator = (DFGraph&&) = delete;
        
    private:

    };

}



#endif //DFCPP_DFGRAPH_HPP
