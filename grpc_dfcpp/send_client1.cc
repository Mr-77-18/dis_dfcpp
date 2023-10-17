#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <grpcpp/grpcpp.h>
#include "commu.grpc.pb.cc"


ABSL_FLAG(std::string , target , "localhost:50057" , "Server address");
ABSL_FLAG(std::string , target1 , "localhost:50058" , "Server address");

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

      std::cout << "the reply from the server is " << response.ret() << std::endl;

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


  //std::vector<int> dfv_index = {0};
  //std::vector<int> value = {77};
  //std::vector<int> task_index = {1 ,2};

  std::vector<int> dfv_index;
  std::vector<int> value;
  std::vector<int> task_index;

  int num;
  bool done = false;
  int which;

  while (!done) {
    dfv_index.clear();
    value.clear();
    task_index.clear();

    std::cout << "enter which computer:0 or 1 , -1 mean shut down\n";
    std::cin >> which;

    std::cout << "input dfv_index\n";
    while (std::cin >> num) {
      dfv_index.push_back(num) ;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "input value\n";
    while (std::cin >> num) {
      value.push_back(num) ;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "input task_index\n";
    while (std::cin >> num) {
      task_index.push_back(num) ;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (which) {
      case 0:
        sendclient.send_index_client(dfv_index , value , task_index);
        break;
      case 1:
        sendclient1.send_index_client(dfv_index , value , task_index);
        break;
      case -1:
        done = true;
        break;
      default:
        break;
    }
  }

  return 0;
}
