//
// Created by ljr on 12/11/22.
//

#include "dfcpp/dfcpp.hpp"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <unistd.h>

using namespace DFCPP;
using namespace std;


constexpr int BLOCKSIZE = 16;
int indexs[BLOCKSIZE];

// 矩阵块
struct Block{
    long long data[BLOCKSIZE];
};

void init(DFV<Block> out) {
    Block block;
    for(auto i : indexs) {
        block.data[i] = random()% 100;
    }
    out = block;
}

void mat(const Block& a, const Block& b, DFV<Block> c) {
    Block block;
    for(auto i : indexs) {
        block.data[i] = a.data[i] * b.data[i];
    }
    c = block;

}

double measure(int n) {
    DFGraph dfGraph;
    vector<vector<DFV<Block>>> matrix_a;
    for(int i = 0; i < n; i++) {
        vector<DFV<Block>> temps;
        for(int j = 0; j < n; j++)
            temps.emplace_back(dfGraph.createDFV<Block>());
        matrix_a.emplace_back(move(temps));
    }

    vector<vector<DFV<Block>>> matrix_b;
    for(int i = 0; i < n; i++) {
        vector<DFV<Block>> temps;
        for(int j = 0; j < n; j++) {
            temps.emplace_back(dfGraph.createDFV<Block>());
        }
        matrix_b.emplace_back(move(temps));
    }

    vector<vector<DFV<Block>>> matrix_c;
    for(int i = 0; i < n; i++) {
        vector<DFV<Block>> temps;
        for(int j = 0; j < n; j++) {
            temps.emplace_back(dfGraph.createDFV<Block>());
        }
        matrix_c.emplace_back(move(temps));
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            dfGraph.emplace(init, make_tuple(), make_tuple(matrix_a[i][j]));
            dfGraph.emplace(init, make_tuple(), make_tuple(matrix_b[i][j]));
            dfGraph.emplace(mat, make_tuple(matrix_a[i][j], matrix_b[i][j]), make_tuple(matrix_c[i][j]));
        }
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

    for(int i = 0; i < BLOCKSIZE; i++)
        indexs[i] = i;
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(indexs, indexs + BLOCKSIZE, g);

    double time = 0;
    for(int i = 0; i < 10; i++)
        time+= measure(n);

    cout <<   " matdot " << n << " BLOCKSIZE: " << BLOCKSIZE << " : " <<  time / 10 << "ms" << endl;
    cout << "pid " << getpid() << endl;
    string cmd = "cat /proc/";
    cmd += to_string(getpid());
    cmd += "/status | grep VmPeak";
    int _ = system(cmd.c_str());    
    return 0;
}
