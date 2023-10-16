#include <cstdio>
#include "dagP.h"
#include "dfcpp_dagP_port.h"
/*
    释放result占用的内存
*/
void free_dfcpp_partition_result(std::vector<DfcppPartitionResult*>& result) {
    for (unsigned long int i=0; i<result.size(); i++) {
        delete result[i];
    }
}
/*
    把dagP算法的输出结果 移植到 DFCPP需要的格式。
*/
static std::vector<DfcppPartitionResult*> dfcpp_port(dgraph* G, idxType* parts, int nParts, int* totEdges) {
    std::vector<DfcppPartitionResult*> result;
    *totEdges = G->nEdge;
    int* topoOrder = new int[nParts];
    int* mapToNewIndex = new int[nParts];
    int isAcyclic = getTopoOrder(G, parts, nParts, topoOrder);
    if (isAcyclic == 0) {
        printf("ERROR : the partition is acyclic.\n");
        exit(1);
    }
    for (int i=0; i<nParts; i++) {
        mapToNewIndex[topoOrder[i]] = i;
        //printf("old : %d, new = %d\n", topoOrder[i], i);
    }
    

    for (int i=0; i<nParts; i++) {
        result.push_back(new DfcppPartitionResult(nParts));
    }
    // arrays from G included parts is indexed from 1
    int nVrtx = G->nVrtx, fromNode;
    idxType* inStart = G->inStart;
    idxType* inEnd = G->inEnd;
    idxType* in = G->in;
    idxType* inEdgeToDfv = G->inEdgeToDfv;
    for (int i=1; i<=nVrtx; i++) {
        int partToNew = mapToNewIndex[parts[i]];
        result[partToNew]->nodes.push_back(i-1); // node index and dfv index in DFCPP is from 0
        for (int j=inStart[i]; j<=inEnd[i]; j++) {
            fromNode = in[j];
            int partFromNew = mapToNewIndex[parts[fromNode]];
            // the nodes between edge are not in the same partition
            if (partFromNew != partToNew) {
                result[partToNew]->inDfvs.push_back(inEdgeToDfv[j]);
                result[partFromNew]->outDfvs.push_back(inEdgeToDfv[j]);
                result[partFromNew]->outEdges[partToNew]++;
                result[partFromNew]->totOutEdges++;
                result[partToNew]->inDegree++;
            }
        }
    }
    #if 1
    printf("----------------Partion Result for DFCPP----------------------\n");
    printf("Graph Info: total edges: %d\n", *totEdges);
    for (int i=0; i<nParts; i++) {
        printf("#Partition %2d: inDegree = %d\n", i, result[i]->inDegree);
        printf("\tNodes: ");
        for (unsigned long int j=0; j<result[i]->nodes.size(); j++) {
            printf("%d, ", result[i]->nodes[j]);
        }
        printf("totally %lu nodes.\n", result[i]->nodes.size());
        printf("\tInput Dfvs: ");
        for (unsigned long int j=0; j<result[i]->inDfvs.size(); j++) {
            printf("%d, ", result[i]->inDfvs[j]);
        }
        printf("totally %lu dfvs.\n", result[i]->inDfvs.size());

        printf("\tOutput Dfvs: ");
        for (unsigned long int j=0; j<result[i]->outDfvs.size(); j++) {
            printf("%d, ", result[i]->outDfvs[j]);
        }
        printf("totally %lu dfvs.\n", result[i]->outDfvs.size());

        printf("\tOut Edges to other partitions:\n");
        for (int j=0; j<nParts; j++) {
            if (j%10 == 0) {
                printf("\t\t");
            }
            printf(" ---> %d edges = %d, ", j, result[i]->outEdges[j]);
            if ((j+1)%10 == 0) {
                printf("\n");
            }
        }
        if (nParts % 10 != 0) {
            printf("\n");
        }
        printf("\tTotal out edges = %d\n", result[i]->totOutEdges);
    }
    printf("--------------------------------------------------------------\n");
    #endif
    

    delete[] topoOrder; 
    delete[] mapToNewIndex; 
    return result;
}
/*
    Use dagP algorithm to partition the input directed graph to n parts for DFCPP
*/
std::vector<DfcppPartitionResult*> dfcpp_graph_partition_by_dagP(char* graphFileName, int nParts, int* totEdges)
{
    if (nParts < 0) {
        printf("Param invalid, nParts should be greater than 0, now we automatically assign nParts as 2.\n");
        nParts = 2;
    }
    MLGP_option opt;
    dgraph G;

    // initialize the ``opt'' variable with number of parts goal = 2
    dagP_init_parameters (&opt, nParts); // initializes default parameters

    dagP_init_filename(&opt, graphFileName); // initialize the input file name and then the  output file name
    // You can reallocate the related variables for a different number of parts later on,
    // instead of providing it on the init_parameters function:
    // reallocate the part upper bound and lower bound arrays for a different number of parts
    // ub and lb arrays by default filled with -1. To set arbitrary values, simply run a for loop
    // dagP_opt_reallocUBLB (&opt, nParts);

    printf ("input: %s, nbPart: %d\n", opt.file_name, opt.nbPart);

    // opt.print = 10; // parameters can then be updated by direct access
    // opt.co_match = 1;
    // opt.conpar = 1;
    // opt.inipart = 6; // opt.inipart = IP_UNDIR;
    opt.conpar = 0;
    opt.inipart = IP_GGG_TWO;
    opt.use_binary_input = 0;
    opt.runs = 5; // number of runs before selecting best edge cut

    // read the graph from file with name from command-line arguments
    dagP_read_graph (graphFileName, &G, &opt);
    // allocate `parts` array with number of nodes limit = G.nVrtx + 1
    idxType *parts = (idxType*) calloc((G.nVrtx+1), sizeof(idxType));
    if (parts == NULL)
        printf("Could not allocate `parts` array.\n");

    // to the partitioning return value is edge cut, part assignments are written over parts array
    ecType x = dagP_partition_from_dgraph(&G, &opt, parts);

    // // node id's are 1-indexed
    // for(idxType i=1; i<= G.nVrtx; ++i){
    //     printf("part[node:%d] = %d\n", i, parts[i]);
    // }

    printf ("edge cut: %d\n", (int) x);

    std::vector<DfcppPartitionResult*> result = dfcpp_port(&G, parts, nParts, totEdges);
    free(parts);
    dagP_free_option(&opt); // frees the arrays in opt
    dagP_free_graph(&G); // frees the arrays in the graph and resets the variables
    return result;
}


/*
Compile and run with:
```
scons
g++ -Wall -o useapi src/useapi.cpp -I src/recBisection/ -I src/common lib/libdagp.a -L/Users/myozka/Documents/metis-5.1.0/build/Darwin-x86_64/libmetis -lmetis -lm
./useapi 2mm_10_20_30_40.dot 2
```
*/
