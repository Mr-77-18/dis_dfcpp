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

//ABSL_FLAG(uint16_t , port , 50058 , "Server port for the service");
    
int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "agrc error" << std::endl;
        exit(0);
    }

    uint16_t port  = std::stoi(argv[1]);

    auto A = graph.createDFV<int>();
    auto B = graph.createDFV<int>();
    auto C = graph.createDFV<int>();
    auto D = graph.createDFV<int>();
    
    //入边：无
    //出边：A
    auto task1 = graph.emplace(
            [](DFV<int> A){
            cout << "task1" << endl;
            A = 1;
            },
            make_tuple(),
            make_tuple(A)
            );

    //入边:A 
    //出边:B
    auto task2 = graph.emplace(
            [](int a , DFV<int> B){
            cout << "task2" << endl;
            B = 99;
            },
            make_tuple(A),
            make_tuple(B)
            );

    //入边:无
    //出边:C
    auto task3 = graph.emplace(
            [](DFV<int> C){
            cout << "task3" << endl;
            C = 1;
            },
            make_tuple(),
            make_tuple(C)
            );

    //入边C， D
    auto task4 = graph.emplace(
            [](int c , DFV<int> D){
            cout << "task4"<< endl;
            D = 77;
            },
            make_tuple(C),
            make_tuple(D)
            );

    //入边：B,D
    auto task5 = graph.emplace(
            [](int b , int d){
            cout << "task5"<< endl;
            },
            make_tuple(B , D),
            make_tuple()
            );

    task1.name("task1");
    task2.name("task2");
    task3.name("task3");
    task4.name("task4");
    task5.name("task5");

    //服务启动
    absl::ParseCommandLine(argc , argv);
    RunServer(port  , &graph , &executor);

    return 0;

}
