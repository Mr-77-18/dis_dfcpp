//
// Created by lsh in 11-10
//
#include <iostream>
#include <string.h>
#include <vector>

#include "dfcpp/dfcpp.hpp"
#include "dfcpp/global.hpp" 

#include "dfcpp/DFV.hpp" 
#include "dfcpp/Node.hpp" 

#include "absl/flags/flag.h"
#include "absl/flags/parse.h" 
#include "absl/strings/str_format.h" 
#include "executor_v2.hpp" 


using namespace std;
using namespace DFCPP;

constexpr int BLOCKSIZE = 256*256;

DFGraph dfGraph;
Executor executor(16);

struct Block{
    vector<int> data;

    Block() : data(BLOCKSIZE) {}
};

double measure(int n) {

    auto dfvs = dfGraph.createDFVs<struct Block>(n-1);

    //create a file with n-1 line(mean the edge)
    //只需要考虑三个元素：
    //1. node序号
    //2. make_tuple()左/make_tuple()右可以确定这个node填写的位置

    auto task = dfGraph.emplace(
            [](DFV<struct Block> out){
            struct Block b;
            for (int i = 0 ; i < BLOCKSIZE ; i++) {
            b.data[i] = 3;
            }
            //b = random() % 100;
            out = b;
            std::cout << "0" << std::endl;
            },
            make_tuple(), make_tuple(dfvs[0]));
    task.name("0");

    for(int i = 0; i < n - 2; i++) {
        auto task1 = dfGraph.emplace(
                [i](const struct Block& b, DFV<struct Block> out){
                struct Block a;
                for (int j = 0; j < BLOCKSIZE; j++) {
                    a.data[j] = b.data[j] + 7;
                }
                //a = b + random() % 100;
                out = b;
                std::cout << i << std::endl;
            },
            make_tuple(dfvs[i]), make_tuple(dfvs[i+1]));
        task1.name(std::to_string(i));
    }
    auto task2 = dfGraph.emplace(
            [](const struct Block& input){
            struct Block total;
            for (int i = 0; i < BLOCKSIZE; i++) {
            total.data[i] += input.data[i];
            }
            //total += input;
            //std::cout << "999" << std::endl;
            },
        make_tuple(dfvs.back()) , make_tuple());

    task2.name("998");

    auto start = chrono::steady_clock::now();
    executor.run(dfGraph).wait();
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "agrc error" << std::endl;
        exit(0);
    }

    uint16_t port = std::stoi(argv[1]);

    int n = 10000;

    type_name.push_back(typeid(vector<int>).name());

    measure(n);

    absl::ParseCommandLine(argc , argv);
    RunServer<struct Block , vector<int>>(port , &dfGraph, &executor , &Block::data);

    return 0;
}
