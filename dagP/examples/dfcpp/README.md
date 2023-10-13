## 使用说明
0. 本目录文件描述
    - useapi.cpp：调用图分割接口的样例
    - data/dfcpp_e6_v6.dot ：图文件，测试样例useapi.cpp会读取，解析
    - Makefile：描述了此图分割接口依赖的 **头文件路径**， **相关的库**
1. 使用
    - make useapi #编译useapi.cpp，生成useapi可执行文件
        - useapi.cpp默认读取data/dfcpp_e6_v6.dot，可以打开源文件对这个路径进行修改
    - ./useapi #执行useapi，程序会输出分割结果
2. 说明：图分割的2个接口
    ```c++
    // 功能：图分割
    // 参数 graphFileName：图文件的路径
    // 参数 nParts：要分割成几部分
    std::vector<DfcppPartitionResult*> dfcpp_graph_partition_by_dagP(char* graphFileName, int nParts);
    
    // 功能：释放占用的资源
    // 参数 result: `dfcpp_graph_partition_by_dagP`函数返回的结果
    void free_dfcpp_partition_result(std::vector<DfcppPartitionResult*>& result);
    
    // 功能：此类封装分割图之后的一个分块，nodes是分块包含的节点编号，inDfvs是该分块的输入数据dfv编号，outDfvs是该分块的输出数据dfv编号, 编号均从0开始。
    class DfcppPartitionResult {
        public:
            std::vector<int> nodes; // index from 0
            std::vector<int> inDfvs; // index from 0
            std::vector<int> outDfvs; // index from 0
        };
    }
    
    ```