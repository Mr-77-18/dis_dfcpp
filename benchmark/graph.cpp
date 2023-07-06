

#include "dfcpp/dfcpp.hpp"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <vector>
#include <unistd.h>


using namespace DFCPP;
using namespace std;

constexpr int BLOCKSIZE = 1;
struct Block{
    long long data[BLOCKSIZE];
};


double measure(int level, int length) {

    DFGraph dfGraph;
    std::mt19937 g(0);  
    std::srand(0);
    vector<vector<DFV<Block>>> dfvs(level - 1);
    for(int i = 0; i < level - 1; i++) {
        dfvs[i] = std::move(dfGraph.createDFVs<Block>(length));
    }

    auto a = dfGraph.createDFV<int>();
    auto b = dfGraph.createDFV<int>();


    vector<int> edge_index;
    for(int i = 0; i < length; i++) {
        edge_index.emplace_back(i);
    }
    // 第一层
    for(int i = 0; i < length; i++) {
        dfGraph.emplace(
            [](DFV<Block> out){
                Block output;
                for(auto& item : output.data) {
                    item = rand() % 100;
                }
                out = output;
            }, 
            make_tuple(), 
            make_tuple(dfvs[0][i])
        );
    }
    int s = 0; 
    for(int i = 1; i < level - 1; i++) {
        shuffle(edge_index.begin(), edge_index.end(), g);     
        s = 0; 
        for(int j = 0; j < length; j++) {
            if(s + 3 >= length) {
                shuffle(edge_index.begin(), edge_index.end(), g);
                s = 0;
            }
            dfGraph.emplace(
                [](const Block& in1, const Block& in2, const Block& in3, const Block& in4, DFV<Block> out){
                    Block output;
                    for(int k = 0; k < BLOCKSIZE; k++) {
                        output.data[k] = in1.data[k] + in2.data[k] + in3.data[k] + in4.data[k];
                    }
                    out = output;
                }, 
                make_tuple(dfvs[i-1][edge_index[s]], dfvs[i-1][edge_index[s+1]], dfvs[i-1][edge_index[s+2]], dfvs[i-1][edge_index[s+3]]), 
                make_tuple(dfvs[i][j])
            );            
            s += 4;
        }
    }

    // 最后一层
    shuffle(edge_index.begin(), edge_index.end(), g);
    s = 0;
    auto& last_level = dfvs.back();
    for(int i = 0; i < length; i++) {
        if(s + 3 >= length) {
            shuffle(edge_index.begin(), edge_index.end(), g);
            s = 0;
        }
        dfGraph.emplace(
            [](const Block& in1, const Block& in2, const Block& in3, const Block& in4){
                long long sumup = 0;
                for(int k = 0; k < BLOCKSIZE; k++) {
                    sumup += in1.data[k];
                    sumup += in2.data[k];
                    sumup += in3.data[k];
                    sumup += in4.data[k];
                }
            }, 
            make_tuple(last_level[edge_index[s]], last_level[edge_index[s+1]], last_level[edge_index[s+2]], last_level[edge_index[s+3]])
        );            
        s += 4;
    }

    Executor executor(8);
    auto start = chrono::steady_clock::now();
    executor.run(dfGraph, 10).wait();
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

int main(int argc, char* argv[]) {

    if(argc != 3) {
        cout << "[usage]: graph level length " << endl;
        return 0;
    }
    int level = atoi(argv[1]);
    int length = atoi(argv[2]);
    

    double time = 0;
    int r = 10;
    // for(int i = 0; i < r; i++) {
        time += measure(level, length);
    // }

    cout << "graph levels:  " << level << " length : " << length << " BlockSIZE: " << BLOCKSIZE << " : " << time/10 << " ms" << endl;
    cout << "pid " << getpid() << endl;
    string cmd = "cat /proc/";
    cmd += to_string(getpid());
    cmd += "/status | grep VmPeak";
    int _ = system(cmd.c_str());
    return 0;
}