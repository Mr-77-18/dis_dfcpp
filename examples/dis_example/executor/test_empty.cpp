//本实验针对main10进行grpc改造
#include <iostream>
#include <string.h>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <nlohmann/json.hpp>

#include "dfcpp/dfcpp.hpp"
#include "dfcpp/global.hpp"

#include "dfcpp/DFV.hpp"
#include "dfcpp/Node.hpp"


#define MAX_BUFFER_SIZE 80960

using namespace std;
using namespace DFCPP;
using json = nlohmann::json;

DFGraph graph;
Executor executor;

//ABSL_FLAG(uint16_t , port , 50058 , "Server port for the service");

int main(int argc, char *argv[])
{

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

    int serverSocket = socket(AF_INET , SOCK_STREAM , 0);
    if (serverSocket == -1) {
        std::cerr << "error in socket" << std::endl;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;


    
    if(bind(serverSocket , reinterpret_cast<struct sockaddr*>(&serverAddr) , sizeof(serverAddr)) == -1){
        std::cerr << "err in bind" << std::endl;
    }

    if(listen(serverSocket , 5) == -1){
        std::cerr << "error in listen" << std::endl;
    }

    sockaddr_in clientAddr{};
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket , reinterpret_cast<struct sockaddr*>(&clientAddr) , &clientAddrSize);
    if (clientSocket == -1) {
        std::cerr << "error in accept" << std::endl;
    }

    char buffer[MAX_BUFFER_SIZE];
    while(1){
        ssize_t bytesRead = recv(clientSocket , buffer , sizeof(buffer) , 0);
        if (bytesRead == -1) {
            std::cerr << "error in recv" << std::endl;
        }else{
            dfv_index.clear();
            task_index.clear();
            value.clear();
            backward_index.clear();
            int _partition;
            int _executor_number;
            std::vector<int> _dfv_index;
            std::vector<int> _value;
            std::vector<int> _task_index;
            std::vector<int> _backward_index;

            try{
                json jsonfromexe = json::parse(buffer);
                for (int i = 0; i < 6; i++) {
                    if (i == 0) {
                        _dfv_index = jsonfromexe.at(i).get<std::vector<int>>();
                    }else if(i == 1){
                        _value = jsonfromexe.at(i).get<std::vector<int>>();
                    }else if(i == 2){
                        _task_index = jsonfromexe.at(i).get<std::vector<int>>();
                    }else if(i == 3){
                        _backward_index = jsonfromexe.at(i).get<std::vector<int>>();
                    }else if(i == 4){
                        _partition = jsonfromexe.at(i).get<int>();
                    }else{
                        _executor_number = jsonfromexe.at(i).get<int>();
                    }
                }
            }catch(const std::exception& e){
                std::cerr << "error in json：" << e.what() << std::endl;
            }

            //std::cout << _dfv_index << " "  << _value << " " << _task_index << " " << _backward_index << " " << _partition << _executor_number << std::endl;

            dfv_index = _dfv_index;
            value = _value;
            task_index = _task_index;
            backward_index = _backward_index;
            //真正干活
            gl.set_dfv_write(dfv_index , value);
            graph.cre_new_graph(task_index);

            auto fut = executor.run(graph , 1 , [](){cout << "end of the work" << endl;});

            fut.wait();

            json jsonArray;
            jsonArray.push_back(backward_index);
            std::vector<int> backward_dfv_value;
            gl.get_dfv_value(backward_index , backward_dfv_value);
            jsonArray.push_back(backward_dfv_value);
            jsonArray.push_back(json(_partition));
            jsonArray.push_back(json(_executor_number));
            std::string jsonString = jsonArray.dump();


            send(clientSocket , jsonString.c_str() , jsonString.size() , 0);

        }

    }
    return 0;

}
