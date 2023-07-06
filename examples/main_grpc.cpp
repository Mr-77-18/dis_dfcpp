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

vector<int> dfv_index;

ABSL_FLAG(uint16_t , port , 50051 , "Server port for the service");

class SendserviceImpl final : public Commu::Service{

    Status send_index(ServerContext* context , const commu::index* request , reply* reply)override{
        commu::index get_index = *request;
        cout << "in the send_index" << endl;

        //vector<int> dfv_index = {3};
        //假设dfv_index从客户端获取

        vector<int> dfv_index;
        int size = get_index._index_size();
        for (int i = 0 ; i < size ; i++) {
           dfv_index.push_back(get_index._index(i)) ;
        }

        vector<int> task_index = {3 , 4};
        vector<int> value = {77};

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
    RunServer(absl::GetFlag(FLAGS_port));
    return 0;

}
