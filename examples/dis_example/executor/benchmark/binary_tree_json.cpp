//
// Created by ljr on 12/11/22.
//

#include <iostream>
#include <chrono>
#include <unistd.h>

#include "dfcpp/dfcpp.hpp"
#include "dfcpp/global.hpp"

#include "dfcpp/DFV.hpp"
#include "dfcpp/Node.hpp"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include "executor_v2.hpp"


using namespace DFCPP;
using namespace std;


constexpr int BLOCKSIZE = 256 * 256;
// 矩阵块
struct Block{
    vector<int> data;

    Block() : data(BLOCKSIZE){}
};

//n means 层数
//total 总数
//non_leaves 没有子节点？

DFGraph dfGraph;
Executor executor(8);
double measure(int n) {
    int total = (1 << n) - 1;
    int non_leaves = (1 << (n - 1)) - 1;


    auto dfvs = dfGraph.createDFVs<struct Block>(total);

    dfGraph.emplace(
            [](DFV<struct Block> output1 , DFV<struct Block> output2){
            struct Block block;
            for (int i = 0; i < BLOCKSIZE; i++) {
                block.data[i] = 44;
            }
                cout << "task is:" <<  1 << endl;
            output1 = block;
            output2 = block;
            },
        make_tuple(),
        make_tuple(dfvs[1] , dfvs[2])
    );
    for(int i = 2; i <= non_leaves; i++) {
        dfGraph.emplace(
                [i](const struct Block& input, DFV<struct Block> output1 , DFV<struct Block> output2){
                struct Block block;
                for (int j = 0; j < BLOCKSIZE ; j++) {
                    block.data[j] = 44;
                }
                cout << "task is:" << i - 1 << endl;
                output1 = block;
                output2 = block;
                },
            make_tuple(dfvs[i - 1]),
            make_tuple(dfvs[(i * 2) - 1] , dfvs[i * 2])
        );        
    }
    for(int i = non_leaves+1; i <= total; i++) {
        dfGraph.emplace(
                [i](const struct Block& input){
                for (int j = 0; j < BLOCKSIZE; j++) {
                    int sumup;
                    sumup += input.data[j];
                }
                cout << "task is:" << i - 1 << endl;
                },
                make_tuple(dfvs[i - 1]),
                make_tuple()
                );        
    }

    cout << "node total:" << total << endl;

}


int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "matdot n  " << endl;
        return 0;
    }

    int n = 10;

    uint16_t port = std::stoi(argv[1]);

    type_name.push_back(typeid(vector<int>).name());

    measure(n);


    absl::ParseCommandLine(argc , argv);
    RunServer<struct Block , vector<int>>(port , &dfGraph , &executor , &Block::data);
 
    auto start = chrono::steady_clock::now();
    executor.run(dfGraph).wait();
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();   
    return 0;
}
