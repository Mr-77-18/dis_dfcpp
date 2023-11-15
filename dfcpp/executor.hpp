#include <iostream>
#include <string.h>
#include <vector>

#include "dfcpp/dfcpp.hpp"
#include "dfcpp/global.hpp"

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

class SendserviceImpl final : public Commu::Service{
    public:
    SendserviceImpl(DFGraph* _graph , Executor* _executor):
        graph(_graph) , executor(_executor){}

    Status send_index(ServerContext* context , const commu::threemess* request , reply* reply)override{
        std::cout << "in send_index()" << std::endl;
        if (request->task_index_size() == 0) {
            return Status::OK;
        }

        dfv_index.clear();
        task_index.clear();
        value.clear();

        backward_index.clear();//加入到global.hpp里面
        int partition;
        int executor_number;

        //获取任务
        //repeated int32 dfv_index = 1;
        for (int i = 0; i < request->dfv_index_size(); i++) {
            dfv_index.push_back(request->dfv_index(i));
        }
        //repeated int32 value = 2;
        for (int i = 0; i < request->value_size(); i++) {
            value.push_back(request->value(i));
        }
        
        //repeated int32 task_index = 3;
        for (int i = 0; i < request->task_index_size(); i++) {
            task_index.push_back(request->task_index(i));
        }

        //repeated int32 dfv_index_backward = 4;
        for (int i = 0; i < request->dfv_index_backward_size() ; i++) {
            backward_index.push_back(request->dfv_index_backward(i));
        }

        //int32 partition = 5;
        partition = request->partition();
        
        //int32 executor_number = 6;
        executor_number = request->executor_number();

        gl.set_dfv_write(dfv_index , value);
        graph->cre_new_graph(task_index);


        auto fut = executor->run(*graph , 1 , [](){cout << "end of the work" << endl;});


        fut.wait();

         //填写reply中的字段，返回信息给master;
        //repeated int32 dfv_index = 2;
        for (int i = 0; i < backward_index.size(); i++) {
            reply->add_dfv_index(backward_index.at(i));
        }
        
        //repeated int32 value = 3;
        std::vector<int> backward_dfv_value;
        gl.get_dfv_value(backward_index , backward_dfv_value);
        for (int i = 0 ; i < backward_index.size() ; i++) {
            reply->add_value(backward_dfv_value.at(i));
        }
        
        //int32 partition = 4;
        reply->set_partition(partition);
        
        //int32 executor_number = 5;
        reply->set_executor_number(executor_number);



        //调试：
        //输出partition查看：
        printf("the partition is :%d\n" , request->partition());

        return Status::OK;

    }

    //std::shared_ptr<DFGraph> graph;
    //std::shared_ptr<Executor> executor;
    DFGraph* graph;
    Executor* executor;
};

void RunServer(uint16_t port , DFGraph* _graph , Executor* _executor) {
    std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
    SendserviceImpl service(_graph , _executor);

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


