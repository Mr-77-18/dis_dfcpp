//
// Created by ljr on 12/8/22.
//

#include "dfcpp/dfcpp.hpp"
#include <iostream>
#include <chrono>
#include <random>
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

    vector<vector<DFV<Block>>> dfvvs;
    for(int i = 0; i < n; i++) {
        dfvvs.emplace_back(dfGraph.createDFVs<Block>(n));
    }
    for(int i = 0; i < n; i++) {
        for(int j =0; j < n; j++) {
            if(i == 0 && j == 0) {
                dfGraph.emplace(
                    [](DFV<Block> output){
                        Block block;
                        for(int k = 0; k < BLOCKSIZE; k++) {
                            block.data[k] = random() % 100;
                        }
                        output = block;
                    }, 
                    make_tuple(), make_tuple(dfvvs[i][j])
                );
            } else if(i == 0) {
                dfGraph.emplace(
                    [](const Block& input, DFV<Block> output){ 
                        Block block;
                        for(int k = 0; k < BLOCKSIZE; k++) {
                            block.data[k] = input.data[k] + random() % 100;
                        }
                        output = block;
                    }, 
                    make_tuple(dfvvs[0][j-1]), make_tuple(dfvvs[i][j]));
            } else if(j == 0) {
                dfGraph.emplace(
                    [](const Block& input, DFV<Block> output){ 
                        Block block;
                        for(int k = 0; k < BLOCKSIZE; k++) {
                            block.data[k] = input.data[k] + random() % 100;
                        }
                        output = block;
                    }, 
                    make_tuple(dfvvs[i-1][0]), make_tuple(dfvvs[i][j]));
            } else {
                dfGraph.emplace([](const Block& a, const Block& b, DFV<Block> output){
                        Block block;
                        for(int k = 0; k < BLOCKSIZE; k++) {
                            block.data[k] = a.data[k] + b.data[k];
                        }
                        output = block;
                    },
                    make_tuple(dfvvs[i-1][j], dfvvs[i][j-1]),
                    make_tuple(dfvvs[i][j])
                );
            }
        }
    }
    Executor executor(16);
    auto start = chrono::steady_clock::now();
    executor.run(dfGraph).wait();
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


int main(int argc, char* argv[] ) {
    if(argc != 2) {
        cout << "wavefront n" << endl;
        return 0;
    }

    int n = atoi(argv[1]);

    double time = 0;
    for(int i = 0; i < 10; i++) {
        time += measure(n);
    }
    cout << "wavefront " << n << " " << BLOCKSIZE << " : " << time / 10 << " ms" << endl;
    cout << "pid " << getpid() << endl;
    string cmd = "cat /proc/";
    cmd += to_string(getpid());
    cmd += "/status | grep VmPeak";
    int _ = system(cmd.c_str());
    return 0;
}