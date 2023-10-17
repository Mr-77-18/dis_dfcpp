//
// Created by Gboom on 2022/11/7.
//

#include "dfcpp/dfcpp.hpp"
#include <chrono>
#include <iostream>


using namespace DFCPP;
using namespace std;

int main(){
    DFGraph graph1;
    DFGraph graph2;
    graph1.emplace([](){
        cout << "graph1 child task sleep for 500ms" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    });

    graph2.emplace([](){cout << "graph2 task" << endl;});
    Executor executor(4);
    auto fut1 = executor.run(graph1, 2, [](){cout << "graph1 done" << endl;});
    auto fut2 = executor.run(graph2);
    fut1.wait();
    fut2.wait();

    return 0;

}