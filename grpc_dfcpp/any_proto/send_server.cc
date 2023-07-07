#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "any.grpc.pb.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
//using commu::Commu;
//using commu::index;
//using commu::reply;
using any::Any;
using any::request;
using any::reply;

ABSL_FLAG(uint16_t , port , 50051 , "Server port for the service");

class SendserviceImpl final : public Any::Service{
  //接受来自客户端的请求，传过来的数据类型是google::protobuf::Any*
  Status send_any(::grpc::ServerContext* context, const request* req, reply* response)override{
    //commu::index get_index = *request;
    //std::cout << "in the send_index" << std::endl;
    //std::cout << "get value :" << get_index._index(1) << std::endl;
    
    const google::protobuf::Any rec = req->data();

    std::cout << "size of the rec is:" << sizeof(rec) << std::endl;

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
  absl::ParseCommandLine(argc , argv);
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
