//本实验针对main10进行grpc改造
#include <iostream>
#include <string.h>
#include <vector>

#include "dfcpp/dfcpp.hpp"
#include "dfcpp/global.hpp"

#include "dfcpp/DFV.hpp"
#include "dfcpp/Node.hpp"

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"
#include "executor.hpp"


using namespace std;
using namespace DFCPP;

DFGraph graph;
Executor executor;

ABSL_FLAG(uint16_t , port , 50058 , "Server port for the service");
    
int main(int argc, char *argv[])
{
    auto A = graph.createDFV<int>();
    auto B = graph.createDFV<int>();
    auto C = graph.createDFV<int>();
    auto D = graph.createDFV<int>();
    auto E = graph.createDFV<int>();
    auto F = graph.createDFV<int>();
    
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

    //服务启动
    absl::ParseCommandLine(argc , argv);
    RunServer(absl::GetFlag(FLAGS_port)  , &graph , &executor);

    return 0;

}
