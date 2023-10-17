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
    

    A.set(1);

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
            c = 99;

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
    task4.name("task4");

    vector<int> index = {1};//哪些node需要执行
    vector<int> index1 = {0}; //哪些边准备好了
    vector<int> value = {77}; //边的值是什么，index1与value一一对应

    //A.set(77);
     
    gl.set_dfv_write(index1 , value);

    graph.cre_new_graph(index);


    Executor executor;
    auto fut = executor.run(graph , 1 , [](){cout << "end of the work" << endl;});


    fut.wait();

    //3. 模拟信息的返回
   cout << "the out is " << C.get() << endl;

    return 0;
}
