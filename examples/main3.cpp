//
// Created by Gboom on 2022/10/23.
//
#include "dfcpp/dfcpp.hpp"
#include <iostream>

using namespace std;
using namespace DFCPP;


//   task1 --> task2
//     |         |
//     v         v
//   task3 --> task4

int main() {
    DFGraph graph;
    auto [A,B,C] = graph.createDFV<int, int, int>();
    auto task1 = graph.emplace([](DFV<int> A){
            A = 1;
            cout << "task1\n";
        }, make_tuple(), make_tuple(A));
    auto task2 = graph.emplace([](int a, DFV<int> B) {
            B = a + 1;
            cout << "task2" << endl;
        }, make_tuple(A), make_tuple(B));
    auto task3 = graph.emplace([](int a, DFV<int> C){
            C = a + 2;
            cout << "task3\n";
        }, make_tuple(A), make_tuple(C));
    auto task4 = graph.emplace([](int b, int c){
            cout << b + c <<  endl;
            cout << "task4\n" << endl;
        }, make_tuple(B,C));

    task1.name("task1");
    task2.name("task2");
    task3.name("task3");
    task4.name("task4");

    Executor executor;
    executor.run(graph, 3).wait();

    return 0;
}
