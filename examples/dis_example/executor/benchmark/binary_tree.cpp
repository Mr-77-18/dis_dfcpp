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

#include "executor.hpp"


using namespace DFCPP;
using namespace std;


constexpr int BLOCKSIZE = 512;
// 矩阵块
struct Block{
    long long data[BLOCKSIZE];
};

//n means 层数
//total 总数
//non_leaves 没有子节点？

DFGraph dfGraph;
Executor executor(8);
double measure(int n) {
    int total = (1 << n) - 1;
    int non_leaves = (1 << (n - 1)) - 1;

    auto dfvs = dfGraph.createDFVs<int>(total);

    dfGraph.emplace(
            [](DFV<int> output1 , DFV<int> output2){
            int block;
            block = random() % 100;
            output1 = block;
            output2 = block;
            },
        make_tuple(),
        make_tuple(dfvs[1] , dfvs[2])
    );
    for(int i = 2; i <= non_leaves; i++) {
        dfGraph.emplace(
                [](const int& input, DFV<int> output1 , DFV<int> output2){
                int block;
                block = input + random() % 100;
                output1 = block;
                output2 = block;
                },
            make_tuple(dfvs[i - 1]),
            make_tuple(dfvs[(i * 2) - 1] , dfvs[i * 2])
        );        
    }
    for(int i = non_leaves+1; i <= total; i++) {
        dfGraph.emplace(
                [](const int& input){
                int sumup;
                sumup += input;
                },
                make_tuple(dfvs[i - 1]),
                make_tuple()
                );        
    }

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

    int n = 10;

    uint16_t port = std::stoi(argv[1]);

    measure(n);

    absl::ParseCommandLine(argc , argv);
    RunServer(port , &dfGraph , &executor);
    
//
//    cout << "binarytree " << n  << " BLOCKSIZE: " << BLOCKSIZE << " : " <<  time / r << " ms" << endl;
//
//    cout << "pid " << getpid() << endl;
//    string cmd = "cat /proc/";
//    cmd += to_string(getpid());
//    cmd += "/status | grep VmPeak";
//    int _ = system(cmd.c_str());
    return 0;
}
