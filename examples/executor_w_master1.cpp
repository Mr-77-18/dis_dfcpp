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

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "grpc_dfcpp/commu.grpc.pb.h"

using namespace std;
using namespace DFCPP;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using commu::Commu;
using commu::reply;

DFGraph graph;
Executor executor;

//从客户端获取的任务
//vector<int> dfv_index;
//vector<int> task_index;
//vector<int> value;

ABSL_FLAG(uint16_t , port , 50058 , "Server port for the service");

class SendserviceImpl final : public Commu::Service{
    Status send_index(ServerContext* context , const commu::threemess* request , reply* reply)override{
        std::cout << "in send_index()" << std::endl;

        for (int i = 0; i < request->dfv_index_size(); i++) {
            dfv_index.push_back(request->dfv_index(i));
        }

        for (int i = 0; i < request->value_size(); i++) {
            value.push_back(request->value(i));
        }

        for (int i = 0; i < request->task_index_size(); i++) {
            task_index.push_back(request->task_index(i));
        }

        gl.set_dfv_write(dfv_index , value);
        graph.cre_new_graph(task_index);


        auto fut = executor.run(graph , 1 , [](){cout << "end of the work" << endl;});


        fut.wait();

        //3. 模拟信息的返回
        //cout << "the out is " << F.get() << endl;

        return Status::OK;

    }
};

void RunServer(uint16_t port) {
    std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
    SendserviceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();


}


int main(int argc, char *argv[])
{
    auto A = graph.createDFV<int>();//0
    auto B = graph.createDFV<int>();//1
    auto C = graph.createDFV<int>();//2
    auto D = graph.createDFV<int>();//3
    auto E = graph.createDFV<int>();//4
    auto F = graph.createDFV<int>();//5
    auto G = graph.createDFV<int>();//6
    
    auto task1 = graph.emplace(
            [](int a , DFV<int> B , DFV<int> D){
            cout << "task1" << endl;
            B = 1;
            D = 2;
            },
            make_tuple(A),
            make_tuple(B , D)
            );
    auto task2 = graph.emplace(
            [](int b , DFV<int> C){
            cout << "task2" << endl;
            C = 3;

            },
            make_tuple(B),
            make_tuple(C)
            );
    auto task3 = graph.emplace(
            [](int c , int e){
            cout << "task3" << endl;
            c = 1;
            },
            make_tuple(C , E),
            make_tuple()
            );
    auto task4 = graph.emplace(
            [](int d , int g , DFV<int> E){
            cout << "task4"<< endl;
            E = 77;

            },
            make_tuple(D , G),
            make_tuple(E)
            );

    auto task5 = graph.emplace(
            [](int f , DFV<int> G){
            cout << "task5"<< endl;
            G = 1;

            },
            make_tuple(F),
            make_tuple(G)
            );


    task1.name("task1");
    task2.name("task2");
    task3.name("task3");
    task4.name("task4");
    task5.name("task5");

    //服务启动
    absl::ParseCommandLine(argc , argv);
    RunServer(absl::GetFlag(FLAGS_port));
    return 0;

}
