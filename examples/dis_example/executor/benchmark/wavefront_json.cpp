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
#include "executor_v2.hpp"


using namespace DFCPP;
using namespace std;

constexpr int BLOCKSIZE = 512;
// 矩阵块
struct Block{
    vector<int> data;
    Block() : data(BLOCKSIZE){}
};

Executor executor(16);
DFGraph dfGraph;

double measure(int n) {//n是矩阵边长

    //节点数量有:n * n
    //边的数量有:2 * n * (n - 1)

    //vector<int> dfvs(2 * n * (n - 1));
    auto dfvs = dfGraph.createDFVs<struct Block>(2 * n * (n - 1));

    int name = -1;

    for(int i = 0; i < n; i++) {
        for(int j =0; j < n; j++) {
            if(i == 0 && j == 0) {
                name++;
                auto task = dfGraph.emplace(
                        [n](DFV<struct Block> output1 , DFV<struct Block> output2){
                        struct Block block;
                        for (int z = 0; z < BLOCKSIZE; z++) {
                            block.data[z] = 22;
                        }
                        output1 = block;
                        output2 = block;
                        }, 
                        make_tuple(), make_tuple(dfvs[0] ,dfvs[0 + n - 1])
                        );

                task.name(std::to_string(name));
            }
            else if(i == 0 && j == n - 1){
                auto task =  dfGraph.emplace(
                        [n , j](const struct Block& input, DFV<struct Block> output){ 
                        struct Block block;
                        for (int z = 0; z < BLOCKSIZE; z++) {
                            block.data[z] = 33;
                        }
                        output = block;
                        }, 
                        make_tuple(dfvs[n -2]), make_tuple(dfvs[j + n - 1])
                        );
                task.name(std::to_string(name));
            }
            else if(i == n - 1 && j == 0){
                auto task = dfGraph.emplace(
                        [n](const struct Block& input, DFV<struct Block> output){ 
                        struct Block block;
                        for (int z = 0; z < BLOCKSIZE; z++) {
                            block.data[z] = 989;
                        }
                        output = block;
                        }, 
                        make_tuple(dfvs[2 * n * (n - 1) - n + 1 - n]), make_tuple(dfvs[2 * n * (n - 1) - n + 1])
                        );
                task.name(std::to_string(name));
            }
            else if(i == n - 1 && j == n -1){
                auto task= dfGraph.emplace(
                        [n](const struct Block& input1, const struct Block& input2){ 
                        struct Block block;
                        for (int z = 0; z < BLOCKSIZE; z++) {
                            block.data[z] = 11;
                        }
                        }, 
                        make_tuple(dfvs[2 * n * (n - 1) - 1] , dfvs[2 * n * (n - 1) - n ]), make_tuple()
                        );
                task.name(std::to_string(name));
            }
            else if(i == 0) {
                auto task = dfGraph.emplace(
                        [n , j](const struct Block& input, DFV<struct Block> output1 , DFV<struct Block> output2){ 
                        struct Block block;
                        for (int z = 0; z < BLOCKSIZE; z++) {
                            block.data[z] = 55;
                        }
                        output1 = block;
                        output2 = block;
                        }, 
                        make_tuple(dfvs[j - 1]), make_tuple(dfvs[j] , dfvs[j + n - 1])
                        );
                task.name(std::to_string(name));
            } 
            else if(j == 0) {
                auto task = dfGraph.emplace(
                        [i , n](const struct Block& input, DFV<struct Block> output1 , DFV<struct Block> output2){ 
                        struct Block block;
                        for (int z = 0; z < BLOCKSIZE; z++) {
                            block.data[z] = 11;
                        }
                        output1 = block;
                        output2 = block;
                        }, 
                        make_tuple(dfvs[i * (2 * n - 1) - n]), make_tuple(dfvs[i * (2 * n - 1) + n - 1] , dfvs[i * (2 * n - 1)]));
                task.name(std::to_string(name));
            } 
            else if(i == n -1){

                auto task = dfGraph.emplace(
                        [i , n](const struct Block& input1, const struct Block& input2 , DFV<struct Block> output){ 
                        struct Block block;
                        for (int z = 0; z < BLOCKSIZE; z++) {
                            block.data[z] = 77;
                        }
                        output = block;
                        }, 
                        make_tuple(dfvs[i * (2 * n - 1)] , dfvs[i * (2 * n - 1) - n + 1]), make_tuple(dfvs[i * (2 * n - 1) + 1 ]));
                task.name(std::to_string(name));
            }
            else if(j == n -1){

                auto task= dfGraph.emplace(
                        [i , n](const struct Block& input1, const struct Block& input2 , DFV<struct Block> output){ 
                        struct Block block;
                        for (int z = 0; z < BLOCKSIZE; z++) {
                            block.data[z] = 32;
                        }
                        output = block;
                        }, 
                        make_tuple(dfvs[i * (2 * n - 1) - 1] , dfvs[i * (2 * n - 1) - 1 + n - 1]), make_tuple(dfvs[i * (2 * n - 1) - 1 + n - 1 + n]));
                task.name(std::to_string(name));
            }
            else {
                auto task = dfGraph.emplace([i , n , j](const struct Block& a, const struct Block& b, DFV<struct Block> output1 , DFV<struct Block> output2){
                        struct Block block;
                        for (int z = 0; z < BLOCKSIZE; z++) {
                            block.data[z] = 99;
                        }
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

    type_name.push_back(typeid(vector<int>).name());

    //double time = 0;
    measure(n);

    absl::ParseCommandLine(argc , argv);
    RunServer<struct Block , vector<int>>(port , &dfGraph , &executor , &Block::data);

//    cout << "wavefront " << n << " " << BLOCKSIZE << " : " << time / 10 << " ms" << endl;
//    cout << "pid " << getpid() << endl;
//    string cmd = "cat /proc/";
//    cmd += to_string(getpid());
//    cmd += "/status | grep VmPeak";
//    int _ = system(cmd.c_str());
    return 0;
}
