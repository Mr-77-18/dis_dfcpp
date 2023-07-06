//
// Created by ljr on 12/18/22.
//

#include "dfcpp/dfcpp.hpp"
#include <iostream>
#include <chrono>
#include <unistd.h>

using namespace DFCPP;
using namespace std;

constexpr int BLOCKSIZE = 512;
struct Block{
    long long data[BLOCKSIZE];
};


double measure(int n) {

    DFGraph dfGraph;
    auto dfvs = dfGraph.createDFVs<Block>(n-1);
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

    Executor executor(16);
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
    int round = 10;
    int n = 1000;
    double time = 0;
    for(int i = 0; i < round; i++) {
        time += measure(n);
    }

    cout << "linear " << n << " BlockSIZE: " << BLOCKSIZE << " : " << time/round << " ms" << endl;
    cout << "pid " << getpid() << endl;
    string cmd = "cat /proc/";
    cmd += to_string(getpid());
    cmd += "/status | grep VmPeak";
    int _ = system(cmd.c_str());
    return 0;
}