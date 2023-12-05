//
// Created by lsh in 11-10
//
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



//#include <iostream>
//#include <chrono>
//#include <unistd.h>

#define MAX_BUFFER_SIZE 80960

using namespace std;
using namespace DFCPP;
using json = nlohmann::json;

constexpr int BLOCKSIZE = 256 * 256;
//struct Block{
//    long long data[BLOCKSIZE];
//};

DFGraph dfGraph;
Executor executor(16);

double measure(int n) {

    auto dfvs = dfGraph.createDFVs<int>(n-1);

    //create a file with n-1 line(mean the edge)
    //只需要考虑三个元素：
    //1. node序号
    //2. make_tuple()左/make_tuple()右可以确定这个node填写的位置

    auto task = dfGraph.emplace(
            [](DFV<int> out){
            int b;
            b = random() % 100;
            out = b;
            int val = 0;
            for (int i = 0; i < BLOCKSIZE; i++) {
            val += 1;
            }
            std::cout << "0" << std::endl;
            },
            make_tuple(), make_tuple(dfvs[0]));
    task.name("0");

    for(int i = 0; i < n - 2; i++) {
        auto task1 = dfGraph.emplace(
                [i](const int& b, DFV<int> out){
                int a;
                a = b + random() % 100;
                out = b;
                int val = 0;
                for (int i = 0; i < BLOCKSIZE; i++) {
                val += 1;
                }
                std::cout << i << std::endl;
            },
            make_tuple(dfvs[i]), make_tuple(dfvs[i+1]));
        task1.name(std::to_string(i));
    }
    auto task2 = dfGraph.emplace(
            [](const int& input){
            int total;
            total += input;
            std::cout << "999" << std::endl;
            },
        make_tuple(dfvs.back()) , make_tuple());

    task2.name("9998");

    //auto start = chrono::steady_clock::now();
    //executor.run(dfGraph).wait();
    //auto end = chrono::steady_clock::now();
    //return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

int main(int argc, char* argv[]) {

    int n = 10000;

    measure(n);
    //measure(n);


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
            dfGraph.cre_new_graph(task_index);

            auto fut = executor.run(dfGraph , 1 , [](){cout << "end of the work" << endl;});

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
