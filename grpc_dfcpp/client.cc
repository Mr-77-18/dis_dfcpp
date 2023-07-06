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
using commu::index;

class Sendclient{
  public:
    Sendclient(std::shared_ptr<Channel> channel)
      :stub_(Commu::NewStub(channel)){}

    void send_index(std::vector<int>& indexs){
      index indexs;

      for (auto i : indexs) {
        indexs.add_index(i);
      }

      google::protobuf::Empty response;
      ClientContext context;

      Status status = stub_->send_index(&context , indexs , &response);

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


  std::vector<int> index = {1 , 3 , 2};
  addclient.send_index(index);

  std::cout << "send end" << std::endl;


  return 0;

}
