//
// Created by ljr on 12/11/22.
//

#include "dfcpp/dfcpp.hpp"
#include <iostream>
#include <chrono>
#include <unistd.h>


using namespace DFCPP;
using namespace std;


constexpr int BLOCKSIZE = 512;
// 矩阵块
struct Block{
    long long data[BLOCKSIZE];
};

double measure(int n) {
    DFGraph dfGraph;
    int total = (1 << n) - 1;
    int non_leaves = (1 << (n - 1)) - 1;
    auto dfvs = dfGraph.createDFVs<Block>(non_leaves+1);
    dfGraph.emplace(
        [](DFV<Block> output){
            Block block;
            for(int i = 0; i < BLOCKSIZE; i++) {
                block.data[i] = random() % 100;
            }
            output = block;
        },
        make_tuple(),
        make_tuple(dfvs[1])
    );
    for(int i = 2; i <= non_leaves; i++) {
        dfGraph.emplace(
            [](const Block& input, DFV<Block> output){
                Block block;
                for(int i = 0; i < BLOCKSIZE; i++) {
                    block.data[i] = input.data[i] + random() % 100;
                }
                output = block;
            },
            make_tuple(dfvs[i/2]),
            make_tuple(dfvs[i])
        );        
    }
    for(int i = non_leaves+1; i <= total; i++) {
        dfGraph.emplace(
            [](const Block& input){
                long long sumup;
                for(int i = 0; i < BLOCKSIZE; i++) {
                    sumup += input.data[i];
                }
            },
            make_tuple(dfvs[i/2])
        );        
    }

    Executor executor(8);
    auto start = chrono::steady_clock::now();
    executor.run(dfGraph).wait();
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "matdot n  " << endl;
        return 0;
    }
    int n = atoi(argv[1]);
    int r = 10;
    double time = 0;
    for(int i = 0; i < r; i++) {
        time += measure(n);
    }

    cout << "binarytree " << n  << " BLOCKSIZE: " << BLOCKSIZE << " : " <<  time / r << " ms" << endl;

    cout << "pid " << getpid() << endl;
    string cmd = "cat /proc/";
    cmd += to_string(getpid());
    cmd += "/status | grep VmPeak";
    int _ = system(cmd.c_str());
    return 0;
}
