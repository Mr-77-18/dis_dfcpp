//
// Created by ljr on 12/4/22.
//

#include "dfcpp/dfcpp.hpp"
#include <iostream>
#include <chrono>

using namespace DFCPP;
using namespace std;

void fsum(int a, int b, DFV<int> out) {
    out = a + b;
}

void fib(DynamicTask& dt, int n, DFV<int> out) {
    if(n < 2) {
        out = n;
    } else {
        auto [f1, f2] = dt.createDFV<int,int>();
        dt.emplace([n](DynamicTask& dt, DFV<int> out){
            fib(dt, n-1, out);
        }, make_tuple(), make_tuple(f1));
        dt.emplace([n](DynamicTask& dt, DFV<int> out){
            fib(dt, n-2, out);
        }, make_tuple(), make_tuple(f2));
        dt.emplace(fsum, make_tuple(f1, f2), make_tuple(out));
        dt.detach();
    }
}


int main(int argc, char* argv[]) {
    if(argc != 2) {
        cerr << "./main5 n" << endl;
        exit(-1);
    }
    int n = stoi(argv[1]);
    auto now = chrono::steady_clock::now();
    DFGraph graph;
    auto [a, b] = graph.createDFV<int, int>();
    a = n;
    graph.emplace(fib, make_tuple(a), make_tuple(b));

    Executor executor(8);
    executor.run(graph).wait();
    cout << "fib : " << a.get() << " " << b.get() << endl;
    auto end = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - now);
    cout << time.count() << endl;
    return 0;
}