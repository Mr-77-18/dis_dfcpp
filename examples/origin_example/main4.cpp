#include "dfcpp/dfcpp.hpp"
#include <iostream>

using namespace DFCPP;
using namespace std;


int main() {
    DFGraph dfGraph;
    auto [a, b, c] = dfGraph.createDFV<int, int, int>();
    auto task1 = dfGraph.emplace([](DFV<int> A){
        cout << "task1\n";
        A = 1;
        }, make_tuple(), make_tuple(a));
    auto task2 = dfGraph.emplace([](DFV<int> B){
        cout << "task2\n";
        B = 2;
    }, make_tuple(), make_tuple(b));
    auto task3 = dfGraph.emplace([](DynamicTask& dt, tuple<DFV<int>, DFV<int>> ins){
        // cout << "task3" << endl;
        dt.emplace([](int aa, int bb){
            // cout << "child task1 aa + bb = " << aa + bb << endl;
        }, ins);

    }, make_tuple(a,b));
    auto task4 = dfGraph.emplace([](DynamicTask& dt, tuple<DFV<int>, DFV<int>> ins, DFV<int> C){
        cout << "task4" << endl;
        dt.emplace([](int aa, int bb, DFV<int> CC){
            cout << "child task 2\n";
            CC = aa + bb;
        }, ins, make_tuple(C)).name("child task2");
        // dt.emplace([](int cc){
        //     cout << "child task3 c = " << cc << endl;
        // }, make_tuple(C)).name("child task3");
    }, make_tuple(a,b), make_tuple(c));
    auto task5 = dfGraph.emplace([](int cc) {
        cout << "task5\n";
    }, make_tuple(c));


    task1.name("task1");
    task2.name("task2");
    task3.name("task3");
    task4.name("task4");
    task5.name("task5");

    Executor executor;
    executor.run(dfGraph).wait();
    cout << "done" << endl;

    return 0;
}