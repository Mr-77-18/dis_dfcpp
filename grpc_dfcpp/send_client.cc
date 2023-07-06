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

    void send_index_client(std::vector<int>& indexs){

      commu::index indexs_send;

      for (auto i : indexs) {
        indexs_send.add__index(i);
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


  std::vector<int> index = {3};
  sendclient.send_index_client(index);

  std::cout << "send end" << std::endl;


  return 0;

}
