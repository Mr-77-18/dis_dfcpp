#ifndef DFCPP_PORT_H
#define DFCPP_PORT_H
#include <vector>
class DfcppPartitionResult {
public:
    std::vector<int> nodes;
    std::vector<int> dfvs;
};
std::vector<DfcppPartitionResult*> dfcpp_graph_partition_by_dagP(char* graphFileName, int nParts);
void free_dfcpp_partition_result(std::vector<DfcppPartitionResult*>& result);
#endif
