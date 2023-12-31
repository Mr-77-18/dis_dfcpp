//
// Created by ljr on 12/8/22.
//

#include <iostream>
#include <chrono>
#include <random>
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

Executor executor(16);
DFGraph dfGraph;

double measure(int n) {//n是矩阵边长

    //节点数量有:n * n
    //边的数量有:2 * n * (n - 1)

    //vector<int> dfvs(2 * n * (n - 1));
    auto dfvs = dfGraph.createDFVs<int>(2 * n * (n - 1));

    int name = -1;

    for(int i = 0; i < n; i++) {
        for(int j =0; j < n; j++) {
            if(i == 0 && j == 0) {
                name++;
                auto task = dfGraph.emplace(
                        [n](DFV<int> output1 , DFV<int> output2){
                        int block;
                        block = random() % 100;
                        output1 = block;
                        output2 = block;
                        }, 
                        make_tuple(), make_tuple(dfvs[0] ,dfvs[0 + n - 1])
                        );

                task.name(std::to_string(name));
            }
            else if(i == 0 && j == n - 1){
                auto task =  dfGraph.emplace(
                        [n , j](const int& input, DFV<int> output){ 
                        int block;
                        block = input + random() % 100;
                        output = block;
                        }, 
                        make_tuple(dfvs[n -2]), make_tuple(dfvs[j + n - 1])
                        );
                task.name(std::to_string(name));
            }
            else if(i == n - 1 && j == 0){
                auto task = dfGraph.emplace(
                        [n](const int& input, DFV<int> output){ 
                        int block;
                        block = input + random() % 100;
                        output = block;
                        }, 
                        make_tuple(dfvs[2 * n * (n - 1) - n + 1 - n]), make_tuple(dfvs[2 * n * (n - 1) - n + 1])
                        );
                task.name(std::to_string(name));
            }
            else if(i == n - 1 && j == n -1){
                auto task= dfGraph.emplace(
                        [n](const int& input1, const int& input2){ 
                        int block;
                        block = input1 + random() % 100;
                        }, 
                        make_tuple(dfvs[2 * n * (n - 1) - 1] , dfvs[2 * n * (n - 1) - n ]), make_tuple()
                        );
                task.name(std::to_string(name));
            }
            else if(i == 0) {
                auto task = dfGraph.emplace(
                        [n , j](const int& input, DFV<int> output1 , DFV<int> output2){ 
                        int block;
                        block = input + random() % 100;
                        output1 = block;
                        output2 = block;
                        }, 
                        make_tuple(dfvs[j - 1]), make_tuple(dfvs[j] , dfvs[j + n - 1])
                        );
                task.name(std::to_string(name));
            } 
            else if(j == 0) {
                auto task = dfGraph.emplace(
                        [i , n](const int& input, DFV<int> output1 , DFV<int> output2){ 
                        int block;
                        block = input + random() % 100;
                        output1 = block;
                        output2 = block;
                        }, 
                        make_tuple(dfvs[i * (2 * n - 1) - n]), make_tuple(dfvs[i * (2 * n - 1) + n - 1] , dfvs[i * (2 * n - 1)]));
                task.name(std::to_string(name));
            } 
            else if(i == n -1){

                auto task = dfGraph.emplace(
                        [i , n](const int& input1, const int& input2 , DFV<int> output){ 
                        int block;
                        block = input1 + random() % 100;
                        output = block;
                        }, 
                        make_tuple(dfvs[i * (2 * n - 1)] , dfvs[i * (2 * n - 1) - n + 1]), make_tuple(dfvs[i * (2 * n - 1) + 1 ]));
                task.name(std::to_string(name));
            }
            else if(j == n -1){

                auto task= dfGraph.emplace(
                        [i , n](const int& input1, const int& input2 , DFV<int> output){ 
                        int block;
                        block = input1 + random() % 100;
                        output = block;
                        }, 
                        make_tuple(dfvs[i * (2 * n - 1) - 1] , dfvs[i * (2 * n - 1) - 1 + n - 1]), make_tuple(dfvs[i * (2 * n - 1) - 1 + n - 1 + n]));
                task.name(std::to_string(name));
            }
            else {
                auto task = dfGraph.emplace([i , n , j](const int& a, const int& b, DFV<int> output1 , DFV<int> output2){
                        int block;
                        block = a + b;
                        output1 = block;
                        output2 = block;
                        },
                        make_tuple(dfvs[i * (2 * n - 1) + j - 1], dfvs[i * (2 * n - 1) + j - n]),
                        make_tuple(dfvs[i * (2 * n - 1) + j] , dfvs[i * (2 * n - 1) + j - 1 + n ])
                        );
                task.name(std::to_string(name));
            }
        }
    }
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
    uint16_t port = std::stoi(argv[1]);

    //int n = atoi(argv[1]);
    int n = 3;


    //double time = 0;
    measure(n);

    absl::ParseCommandLine(argc , argv);
    RunServer(port , &dfGraph , &executor);
//
//    cout << "wavefront " << n << " " << BLOCKSIZE << " : " << time / 10 << " ms" << endl;
//    cout << "pid " << getpid() << endl;
//    string cmd = "cat /proc/";
//    cmd += to_string(getpid());
//    cmd += "/status | grep VmPeak";
//    int _ = system(cmd.c_str());
    return 0;
}
