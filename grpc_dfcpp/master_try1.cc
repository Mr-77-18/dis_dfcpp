#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <grpcpp/grpcpp.h>
#include "master.hpp"
#include "commu.grpc.pb.cc"


ABSL_FLAG(std::string , target , "localhost:50057" , "Server address");
ABSL_FLAG(std::string , target1 , "localhost:50058" , "Server address");

using namespace DFCPP;

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


      commu::threemess indexs_send;


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
  std::string target_str1 =absl::GetFlag(FLAGS_target1);

  Sendclient sendclient(grpc::CreateChannel(target_str , grpc::InsecureChannelCredentials()));
  Sendclient sendclient1(grpc::CreateChannel(target_str1 , grpc::InsecureChannelCredentials()));

  int executor_num = 2;
  int executor = 0 ;// 认为规定现在只有两个，之后再更新

    //加入master之后的新版本任务发布，不再是和send_client1.cc一样只是手动发送任务了
    //开始之前要清空任务列表
    while (1) {
      node_index.clear();
      value.clear();
      dfv_index.clear();

      //创建Master实例
      Master master;

      //调用下方函数的时候就已经产生任务了
      master.pub_tasks();

      //任务发布，以轮询的方式发布：

      switch (executor) {
        case 0:
          sendclient.send_index_client(dfv_index , value , node_index);
          break;
        case 1:
          sendclient1.send_index_client(dfv_index , value , node_index);
          break;
        default:
          break;
      }

      executor = (executor + 1) % executor_num;
    }
  return 0;
}
