#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <grpcpp/grpcpp.h>
#include "commu.grpc.pb.cc"
 

ABSL_FLAG(std::string , target , "localhost:50051" , "Server address");

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using commu::Commu;
//using commu::index;
using commu::reply;

class Sendclient{
  public:
    Sendclient(std::shared_ptr<Channel> channel)
      :stub_(Commu::NewStub(channel)){}

    void send_index_client(std::vector<int>& _dfv_index , std::vector<int>& _value , std::vector<int>& _task_index){

      //commu::index indexs_send;

      commu::threemess indexs_send;

      //for (auto i : indexs) {
      //  indexs_send.add__index(i);
      //}
      
      //repeated int32 dfv_index = 1;
      for(auto i : _dfv_index){
        indexs_send.add_dfv_index(i);
      }
      
      //repeated int32 value = 2;
      for(auto i : _value){
        indexs_send.add_value(i);
      }
      
      //repeated int32 task_index = 3;
      for(auto i : _task_index){
        indexs_send.add_task_index(i);
      }
      
      reply response;
      ClientContext context;

      Status status = stub_->send_index(&context  , indexs_send , &response);

      if (status.ok()) {
        return;
      }else{
        std::cout << status.error_code() << ":" << status.error_message() << std::endl;
      }
    }
  private:
    std::unique_ptr<Commu::Stub> stub_;
};

int main(int argc, char *argv[])
{
  absl::ParseCommandLine(argc , argv);
  std::string target_str =absl::GetFlag(FLAGS_target);

  Sendclient sendclient(grpc::CreateChannel(target_str , grpc::InsecureChannelCredentials()));


  std::vector<int> dfv_index = {3};
  std::vector<int> value = {77};
  std::vector<int> task_index = {3 , 4};
  sendclient.send_index_client(dfv_index , value , task_index);

  std::cout << "send end" << std::endl;


  return 0;

}
