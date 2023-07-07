#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <grpcpp/grpcpp.h>
#include "any.grpc.pb.h"
 

ABSL_FLAG(std::string , target , "localhost:50051" , "Server address");

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using any::Any;
using any::request;
using any::reply;
using any::person;
//using google::protobuf::Any

class Sendclient{
  public:
    Sendclient(std::shared_ptr<Channel> channel)
      :stub_(Any::NewStub(channel)){}

    //template<class T>
    void send_value_client(){

      //google::protobuf::Any _any;
      auto indexs_send = new request();

      auto _person = new person();

      _person->set_name("liusenhong");

      //创建一个google::protobuf::Any数据类型的指针，用于把别的类型（定义在proto中的）转化成Any，以便传输
      google::protobuf::Any *_any = new google::protobuf::Any;

      //将_persion类型转成Any类,注意这里PackFrom()函数的参数如果是直接用c++里面的数据类型，会报错说have not member: T::Fullname...,即这里的参数要是proto里面定义的参数类型
      _any->PackFrom(*_person);

      //获取request（在proto中定义的）当中的google::protobuf::Any数据类型字段的指针,用于后续的复制。
      google::protobuf::Any *data = indexs_send->mutable_data();

      *data = *_any;

      reply response;
      ClientContext context;

      Status status = stub_->send_any(&context  , *indexs_send , &response);

      if (status.ok()) {
        return;
      }else{
        std::cout << status.error_code() << ":" << status.error_message() << std::endl;
      }
    }
  private:
    std::unique_ptr<Any::Stub> stub_;
};

int main(int argc, char *argv[])
{
  absl::ParseCommandLine(argc , argv);
  std::string target_str =absl::GetFlag(FLAGS_target);

  Sendclient sendclient(grpc::CreateChannel(target_str , grpc::InsecureChannelCredentials()));


  //std::vector<int> index = new
  sendclient.send_value_client();

  std::cout << "send end" << std::endl;


  return 0;

}
