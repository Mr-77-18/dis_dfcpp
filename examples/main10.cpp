//收到的信息包括：
//1. 需要执行的node的信息
//2. ins的DFV ， outs的DFV
//
//处理的逻辑
//1. 先把所有的ins的状态同步
//2. 找出所有node，放进graph里面，然后去执行
//3. 把所有outs的DFV的状态返回去(这里指任务发布的一方)

//本code测试执行一方，先不管任务发布一方
#include <iostream>
#include <string.h>

#include "dfcpp/dfcpp.hpp"
#include "dfcpp/global.hpp"

#include "dfcpp/DFV.hpp"
#include "dfcpp/Node.hpp"

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
    auto F= graph.createDFV<int>();
    
    auto task1 = graph.emplace(
            [](DFV<int> a , DFV<int> d){
            cout << "task1" << endl;
            a = 1;
            d = 1;

            },
            make_tuple(),
            make_tuple(A , D)
            );
    //入边A , 出边C
    auto task2 = graph.emplace(
            [](int a , DFV<int> b){
            cout << "task2" << endl;
            b = 99;

            },
            make_tuple(A),
            make_tuple(B)
            );
    //入边B , 出边D
    auto task3 = graph.emplace(
            [](int b , DFV<int> c){
            cout << "task3" << endl;
            c = 1;
            },
            make_tuple(B),
            make_tuple(C)
            );
    //入边C， D
    auto task4 = graph.emplace(
            [](int d , DFV<int> E){
            cout << "task4"<< endl;
            E = 77;

            },
            make_tuple(D),
            make_tuple(E)
            );

    auto task5 = graph.emplace(
            [](int d , DFV<int> F){
            cout << "task5"<< endl;
            F = 111;

            },
            make_tuple(E),
            make_tuple(F)
            );

    auto task6 = graph.emplace(
            [](int d , int E){
            cout << "task6"<< endl;
            },
            make_tuple(C , F),
            make_tuple()
            );



    task1.name("task1");
    task2.name("task2");
    task3.name("task3");
    task4.name("task4");
    task5.name("task5");
    task6.name("task6");

    vector<int> dfv_index = {3};
    vector<int> task_index = {3 , 4};
    vector<int> value = {77};

    gl.set_dfv_write(dfv_index , value);
    graph.cre_new_graph(task_index);


    Executor executor;
    auto fut = executor.run(graph , 1 , [](){cout << "end of the work" << endl;});


    fut.wait();

    //3. 模拟信息的返回
    cout << "the out is " << F.get() << endl;

    return 0;
}
