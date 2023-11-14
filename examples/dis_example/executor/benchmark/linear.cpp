//
// Created by lsh in 11-10
//

#include "dfcpp/dfcpp.hpp"
#include "dfcpp/global.h" 

#include "dfcpp/DFV.hpp" 
#include "dfcpp/Node.h" 

#include "absl/flags/flag.h"
#include "absl/flags/parse.h" 
#include "absl/strings/str_format.h" 
#include "executor.hpp" 


#include <iostream>
#include <chrono>
#include <unistd.h>


using namespace DFCPP;
using namespace std;

constexpr int BLOCKSIZE = 512;
struct Block{
    long long data[BLOCKSIZE];
};

DFGraph dfGraph;
Executor executor(16);

double measure(int n) {

    auto dfvs = dfGraph.createDFVs<Block>(n-1);

    //create a file with n-1 line(mean the edge)
    //只需要考虑三个元素：
    //1. node序号
    //2. make_tuple()左/make_tuple()右可以确定这个node填写的位置

    dfGraph.emplace(
        [](DFV<Block> out){
            Block b;
            for(auto&& item : b.data) {
                item = random() % 100;
            }
            out = b;
        },
        make_tuple(), make_tuple(dfvs[0]));
    for(int i = 0; i < n - 2; i++) {
        dfGraph.emplace(
            [](const Block& b, DFV<Block> out){
                Block a;
                for(int j = 0; j < BLOCKSIZE; j++) {
                    a.data[j] = b.data[j] + random() % 100;
                }
                out = b;
            },
            make_tuple(dfvs[i]), make_tuple(dfvs[i+1]));
    }
    dfGraph.emplace(
        [](const Block& input){
            long long total;
            for(int i = 0; i < BLOCKSIZE; i++) {
                total += input.data[i];
            }
        },
        make_tuple(dfvs.back()));

    auto start = chrono::steady_clock::now();
    executor.run(dfGraph).wait();
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

int main(int argc, char* argv[]) {

    // if(argc != 2) {
    //     cout << "[usage]: linear n " << endl;
    //     return 0;
    // }

    // int  n = atoi(argv[1]);
    int n = 1000;
    measure(n);

    absl::ParseCommandLine(argc , argv);
    RunServer(port , &graph , &executor);

    return 0;
}
