//
// Created by Gboom on 2022/10/19.
//


#include "dfcpp/dfcpp.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace DFCPP;


int main() {

    DFGraph graph;

    auto [A, B] = graph.createDFV<int, int>();
    auto task1 = graph.emplace(
            [](DFV<int> A){
                    A = 5;
                    // string s = "task1 : start with a = " + to_string(A.get());
                    // cout << s << endl;
                },
            make_tuple(),
            make_tuple(A));
    auto task2 = graph.emplace(
            [](int a, DFV<int> B){
                // cout << "task2" << endl;
                B = a - 1;
            },
            make_tuple(A),
            make_tuple(B)
            );
    auto task3 = graph.emplace(
            [](const int& b, DFV<int> A)->size_t{
                cout << "task3" << endl;
                if(b > 0) {
                    A = b;
                    return 0;
                }
                else {
                    return 1;
                }
            },
            make_tuple(B),
            make_tuple(A)
            );

    auto task4 = graph.emplace(
            [](){
                cout << "task4 continue\n" ;
            }
            );
    auto task5 = graph.emplace(
            [](){
                cout << "task5 done\n";
            }
            );
    graph.condition(task3, {task4, task5});

    task1.name("task1");
    task2.name("task2");
    task3.name("task3");
    task4.name("task4");
    task5.name("task5");


    Executor executor;
    auto fut = executor.run(graph, 2, [](){cout << "----------done one epoch-------------\n";});
    auto fut2 = executor.run(graph, 1,[](){cout << "!!!!!!!!!!done one epoch!!!!!!!!!!!!!\n";});
    fut.wait();
    fut2.wait();
    cout << "graph done" << endl;

    return 0;
}