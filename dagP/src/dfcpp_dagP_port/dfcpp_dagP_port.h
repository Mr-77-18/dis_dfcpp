#ifndef DFCPP_PORT_H
#define DFCPP_PORT_H
#include <vector>
class DfcppPartitionResult {
public:
    std::vector<int> nodes; // index from 0
    std::vector<int> inDfvs; // index from 0
    std::vector<int> outDfvs; // index from 0
    std::vector<int> outEdges; // index denotes node, value denotes out edges amount.
    int inDegree;
    int totOutEdges;
    DfcppPartitionResult(int nParts) {
        std::vector<int> tmp(nParts, 0);
        outEdges.insert(outEdges.end(), tmp.begin(), tmp.end());
        inDegree = 0;
        totOutEdges = 0;
    }
};
std::vector<DfcppPartitionResult*> dfcpp_graph_partition_by_dagP(char* graphFileName, int nParts, int* totEdges);
void free_dfcpp_partition_result(std::vector<DfcppPartitionResult*>& result);
#endif
