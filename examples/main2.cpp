//
// Created by Gboom on 2022/10/21.
//

//
// Created by Gboom on 2022/10/19.
//


#include "dfcpp/dfcpp.hpp"
#include <tuple>
#include <iostream>

using namespace std;
using namespace DFCPP;

int main() {

    DFGraph graph;
    auto a = graph.createDFV<int>();

    auto task1 = graph.emplace(
            [](DFV<int> a){
                a = 1;
                cout << "task1: start with a = " << a.get() << endl;
            },
            make_tuple(),
            make_tuple(a));
    // 动态任务
    auto task2= graph.emplace(
            [](DynamicTask& dt, const int& aa)->void {
                cout << "child task will sleep for " << aa << " seconds, and his parent will wait" << endl;

                dt.emplace([aa](){
                    cout << "child start" << endl;
                    this_thread::sleep_for(chrono::seconds (aa));
                    cout << "child done" << endl;
                });
            },
            make_tuple(a)
            );



    task1.name("task1");
    task2.name("task2");


    Executor executor;
    auto fut = executor.run(graph);
    fut.wait();
    cout << "done" << endl;

    return 0;
}