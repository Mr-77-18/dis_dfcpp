#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <grpcpp/grpcpp.h>
#include "commu.grpc.pb.cc"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using commu::Commu;
//using commu::index;
using commu::reply;

//管理dfv的值,用于前向和后向dfv的使用
std::vector<int> dfv_value;

class Sendclient{
  public:
    Sendclient(std::shared_ptr<Channel> channel)
      :stub_(Commu::NewStub(channel)){}

    void send_index_client(std::vector<int>& _dfv_index , std::vector<int>& _value , std::vector<int>& _task_index , std::vector<int> _dfv_index_backward){

      //commu::index indexs_send;

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

      //repeated int32 dfv_index_backward = 4;
      for(auto i : _dfv_index_backward){
        indexs_send.add_dfv_index_backward(i);
      }

      reply response;
      ClientContext context;

      Status status = stub_->send_index(&context  , indexs_send , &response);

      std::vector<int> res_dfv_index = response.dfv_index();
      std::vector<int> res_value = response.value();

      //后去后向dfv信息，更新图,其实就是更新图的value
      for (int i = 0 ; i < response.dfv_index_size() ; i++) {
        dfv_value.at(res_dfv_index.at(i)) = res_value.at(i);
      }

      //这里还要更新调度需要用到的partion拓扑关系

      if (status.ok()) {
        return;
      }else{
        std::cout << status.error_code() << ":" << status.error_message() << std::endl;
      }
    }
  private:
    std::unique_ptr<Commu::Stub> stub_;
};


//使用的最简单的方法：
//获取图信息
//filename 
//
//Executor地址：std::string ABSL_FLAG(std::string , target , "localhost:50057" , "Server address");
//
//Schedule schedule(filename , Sendclient , std::vector<str::string&>& Executor_address)
//
//schedule.run()
//
//while(1){
//直到任务发布完成
//}
//
//发布任务
//
//end
//
//结束
namespace DFCPP{
  class Schedule{
    public:
      Schdule(std::string _filename , std::vector<std::string>& _executor_address)
        :filename(_filename) , executor_address(_executor_address) , done(false){}

      bool get_free_partition(DfcppPartitionResult& _partition);

      int publish_task(DfcppPartitionResult& _partition);

      Sendclient* get_free_client();
      //开始跑咯
      void run();

    private:
      std::string filename;
      std::vector<std::string> executor_address;
      //这个还没有想好是不是用户传过来
      int nParts;
      std::vector<Sendclient> sendclients;
      bool done;//表示任务调度是否完成
  };

  void Schedule::run(){
    //根据executor_address创造服务接口
    for (auto address : executor_addrss) {
      sendclient.push_back(Sendclient(grpc::CreateChannel(address , grpc::InsecureChannelCredentials)))  ;
    }
    //调用图划分算法
    std::vector<DfcppPartitionResult*> result = dfcpp_graph_partition_by_dagP(filename , nParts);


    //循环发布任务
    while(1){
      DfcppPartitionResult partition;
      done = get_free_partition(partition);//这里free表示可以发布给executor执行的任务

      ret = publish_task(partition);
      if (ret < 0) {//表示所有executor都在忙,下次循环再看
        continue; 
      }

      if (done) {
        break;
      }
    }
    //最后要记得释放掉
    free_dfcpp_partition_result(result);
  }

  bool Schedule::get_free_partition(DfcppPartitionResult& _partition){

  }

  int Schedule::publish_task(DfcppPartitionResult& _partition){
    //得到要发布的executor
    Sendclient* sendclient = get_free_client();//这里的free表示可以发布任务给这个executor
    if (sendclient == nullptr) {//表示所有的executor都在忙，不能发送任务，等待下一轮任务发布
      return -1;
    }

    //发布任务
    //获取最新的value值
    std::vector<int> values;
    for (auto i : _partition.inDfvs) {
      values.push_back(dfv_value.at(i));
    }
    sendclient.send_client_index(_partition.inDfvs , dfv_value , _partition.nodes , _partition.outDfvs);

    return 1;
  }

  Sendclient* Schedule::get_free_client(){//涉及到Executor的管理

  }
}

