//本实验针对main10进行grpc改造
#include <iostream>
#include <string.h>
#include <vector>

#include "dfcpp/dfcpp.hpp"
#include "dfcpp/global_v2.hpp"

#include "dfcpp/DFV.hpp"
#include "dfcpp/Node.hpp"

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"
#include "executor_v2.hpp"


using namespace std;
using namespace DFCPP;

DFGraph graph;
Executor executor;

struct Mydata{
    //vector<int> a[512]
    int a;
    double b;
    //double b;
    //long long blocak[3];
};

//ABSL_FLAG(uint16_t , port , 50058 , "Server port for the service");

template <typename... Args>
SendMessageImpl<Args...> sm;

    
int main(int argc, char *argv[])
{
    type_name.push_back(typeid(vector<int>).name());
    //type_name.push_back(typeid(double).name());
    if (argc < 2) {
        std::cout << "agrc error" << std::endl;
        exit(0);
    }

    uint16_t port  = std::stoi(argv[1]);

    auto A = graph.createDFV<struct Mydata>();
    auto B = graph.createDFV<struct Mydata>();
    auto C = graph.createDFV<struct Mydata>();
    auto D = graph.createDFV<struct Mydata>();
    auto E = graph.createDFV<struct Mydata>();
    auto F = graph.createDFV<struct Mydata>();
    
    //入边：无
    //出边：A
    auto task1 = graph.emplace(
            [](DFV<struct Mydata> A , DFV<struct Mydata> D){
            cout << "task1" << endl;
            struct Mydata data = {22 , 3.2};
            A = data;
            D = data;
            },
            make_tuple(),
            make_tuple(A , D)
            );

    //入边:A 
    //出边:B
    auto task2 = graph.emplace(
            [](struct Mydata a , DFV<struct Mydata> B){
            cout << "task2" << endl;
            struct Mydata data = {22 , 4.3};
            B = data;
            },
            make_tuple(A),
            make_tuple(B)
            );

    //入边:无
    //出边:C
    auto task3 = graph.emplace(
            [](struct Mydata b , DFV<struct Mydata> C){
            cout << "task3" << endl;
            struct Mydata data = {22 , 2.2};
            C = data;
            },
            make_tuple(B),
            make_tuple(C)
            );

    //入边C， D
    auto task4 = graph.emplace(
            [](struct Mydata d , DFV<struct Mydata> E){
            cout << "task4"<< endl;
            struct Mydata data = {22 , 3.3};
            E = data;
            },
            make_tuple(D),
            make_tuple(E)
            );

    //入边：B,D
    auto task5 = graph.emplace(
            [](struct Mydata e , DFV<struct Mydata> F){
            cout << "task5"<< endl;
            struct Mydata data = {22 , 1.1};
            F = data;
            },
            make_tuple(E),
            make_tuple(F)
            );

    auto task6 = graph.emplace(
            [](struct Mydata c , struct Mydata f){
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
    task5.name("task6");

    //服务启动
    absl::ParseCommandLine(argc , argv);
    RunServer<struct Mydata , vector<int>>(port  , &graph , &executor , &Mydata::a , &Mydata::b);

    return 0;

}
