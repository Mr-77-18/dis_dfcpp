#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <grpcpp/grpcpp.h>
#include "commu.grpc.pb.cc"


ABSL_FLAG(std::string , target , "localhost:50051" , "Server address");
ABSL_FLAG(std::string , target1 , "localhost:50052" , "Server address");

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

std::vector<int> dfv_index;
std::vector<int> value;
std::vector<int> task_index;
bool done = false;

int main(int argc, char *argv[])
{
  absl::ParseCommandLine(argc , argv);

  std::string target_str =absl::GetFlag(FLAGS_target);

  //第一个服务器
  Sendclient sendclient(grpc::CreateChannel(target_str , grpc::InsecureChannelCredentials()));

  //第二个服务器
  std::string target_str1 = absl::GetFlag(FLAGS_target1);
  Sendclient sendclient1(grpc::CreateChannel(target_str1 , grpc::InsecureChannelCredentials()));



  while (!done) {
    dfv_index.clear();
    value.clear();
    task_index.clear();

    int num;

    int which;
    std::cout << "which computer you want to , 0 or 1 , and -1 mean shut down this server\n";
    std::cin >> which;

    std::cout << "input the dfv_index , end with .\n";
    while (std::cin >> num) {
      dfv_index.push_back(num);
    }

    std::cout << "input the value , end with .\n";
    while (std::cin >> num) {
      value.push_back(num);
    }


    std::cout << "input the task_index , end with .\n";
    while (std::cin >> num) {
      task_index.push_back(num);
    }

    switch (which) {
      case 0:
        sendclient.send_index_client(dfv_index , value , task_index);
        std::cout << "send the task to computer 0\n";
      case 1:
        sendclient1.send_index_client(dfv_index , value , task_index);
        std::cout << "send the task to computer 1\n";
      case -1:
        done = true;
      default:
        break;
    } 
  }



  return 0;

}
