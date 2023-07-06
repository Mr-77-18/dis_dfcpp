#include <iostream>
#include <string>
#include "dfcpp/dfcpp.hpp"

using namespace std;
using namespace DFCPP;

int main(int argc, char *argv[])
{
    DFGraph graph;

    auto A = graph.createDFV<int>();
    auto B = graph.createDFV<int>();
    auto C = graph.createDFV<int>();
    auto D = graph.createDFV<int>();
    auto E = graph.createDFV<int>();

    //出边A , B
    auto task1 = graph.emplace(
            [](DFV<int> a , DFV<int> b){
            cout << "task1" << endl;
            a = 1;
            b = 1;
            },
            make_tuple(),
            make_tuple(A , B)
            );
        //入边A , 出边C
        auto task2 = graph.emplace(
                [](int a , DFV<int> c){
                cout << "task2" << endl;
                c = 1;
                },
                make_tuple(A),
                make_tuple(C)
                );
        //入边B , 出边D
        auto task3 = graph.emplace(
                [](int B , DFV<int> D){
                cout << "task3" << endl;
                D = 1;
                },
                make_tuple(B),
                make_tuple(D)
                );
        //入边C， D
        auto task4 = graph.emplace(
                [](int c , int d , DFV<int> E){
                cout << "task4"<< endl;
                E = 77;
                },
                make_tuple(C , D),
                make_tuple(E)
                );

        task1.name("task1");
        task2.name("task2");
        task3.name("task3");
        task3.name("task4");

        Executor executor;
        auto fut = executor.run(graph , 1 , [](){cout << "endl of the work" << endl;});

        fut.wait();

        cout << "endl" << endl;

        cout << "DFV<int> E is :" << E.get() << endl;

        return 0;
}
