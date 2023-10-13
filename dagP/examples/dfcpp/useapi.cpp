#include <stdio.h>
#include <stdlib.h>
#include "dfcpp_dagP_port.h"
int main(int argc, char* argv[]) {
        char graphFileName[] = "data/dfcpp_e6_v6_4.dot";
        const int nParts = 3;
        // 1. call api to get partition result
        std::vector<DfcppPartitionResult*> result  = dfcpp_graph_partition_by_dagP(graphFileName, nParts);
        // your code...
        // ..... 
        // 2. call api to release partition result resource
        free_dfcpp_partition_result(result);
        return 0;
}
