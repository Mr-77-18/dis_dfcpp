//在schedule的基础上改进成模板类，支持任意版本数据的传输
#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <grpcpp/grpcpp.h>
#include "commu.grpc.pb.cc"
#include "dfcpp_dagP_port.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using commu::Commu;
using commu::reply;

namespace DFCPP{
  class Sendclient; 
  //管理dfv的值,用于前向和后向dfv的使用
  std::vector<int> dfv_value;

  //保存分区信息
  std::shared_ptr<std::vector<DfcppPartitionResult*>> partition_ptr;
  std::vector<int> partition_status;//用来表示分区状态：0:未完成 ； 1：完成了

  //管理Executor
  std::vector<Sendclient> sendclients;
  std::vector<int> client_status;//用来表示executor的状态：0:空闲 ； 1：为空闲

  //更新global的信息，这里会涉及到commu.proto中的字段内容
  //首先明确更新什么
  //1. 根据完成的partition是哪一个，进行拓扑操作，即将相应的partition入度减去；
  //2. 根据返回信息中表示的是那一台client(Executor),将相应的client_status设置成为0（表示空闲）
  //以此推出commu.proto中reply中的信息应该包含的内容
  static void update_global_data(reply& _response){

    std::vector<int> res_dfv_index;
    for (int i = 0; i < _response.dfv_index_size(); i++) {
      res_dfv_index.push_back(_response.dfv_index(i));
    }

    std::vector<int> res_value;
    for (int i = 0; i < _response.value_size(); i++) {
      res_value.push_back(_response.value(i));
    }

    //获取后向dfv信息，更新图,其实就是更新图的value
    for (int i = 0 ; i < _response.dfv_index_size() ; i++) {
      dfv_value.at(res_dfv_index.at(i)) = res_value.at(i);
    }

    //这里还要更新调度需要用到的partion拓扑关系,那么这个patition要全局的咯？,response当中应该携带分区信息吧,所以再commu.proto中加入一个值是int32 partition
    //更新分区的入度
    for (int i = 0; i < (*partition_ptr).size(); i++) {
      (*partition_ptr).at(i)->inDegree -= (*partition_ptr).at(_response.partition())->outEdges.at(i);
    }


    //更新client(executor)的状态,改为空闲
    client_status.at(_response.executor_number()) = 0;
  }

  template <typename T>
  class Sendclient{
    public:
      Sendclient(std::shared_ptr<Channel> channel)
        :stub_(Commu::NewStub(channel)){}

      void send_index_client_v2(int _executor_number , int _partition_number , std::vector<int>& _dfv_index , std::vector<int>& _value , std::vector<int>& _task_index , std::vector<int> _dfv_index_backward){
      }

      void send_index_client(int _executor_number , int _partition_number , std::vector<int>& _dfv_index , std::vector<int>& _value , std::vector<int>& _task_index , std::vector<int> _dfv_index_backward){

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

        //int32 partition = 5;
        indexs_send.set_partition(_partition_number);
        
        //int32 executor_number = 6;
        indexs_send.set_executor_number(_executor_number);

        reply response;
        ClientContext context;

        Status status = stub_->send_index(&context  , indexs_send , &response);

        if (status.ok()) {
          //根据的response中的信息更新gloabl的状态信息;
          update_global_data(response);

          return;
        }else{//任务没有执行成功
          std::cout << status.error_code() << ":" << status.error_message() << std::endl;
        }
      }
    private:
      std::unique_ptr<Commu::Stub> stub_;
  };

  template <typename T>
    void Sendclient<T>::send_index_client_v2(int _executor_number , int _partition_number , std::vector<int>& _dfv_index , std::vector<T>& _value , std::vector<int>& _task_index , std::vector<int> _dfv_index_backward){

        //commu::index indexs_send;

        commu::threemess indexs_send;

        //repeated int32 dfv_index = 1;
        for(auto i : _dfv_index){
          indexs_send.add_dfv_index(i);
        }
        
        //repeated int32 value = 2;
        for(auto i : _value){
          //这里把_value转换成json再放进indexs_send的string里面
          nlohmann::json json;

          //这个函数要能够data i 的；每一个字段放进这个json里面
          //那么这个sm一定是能够理解这个i的数据类型的，也就是T，能够知道各个成员的数据类型?
          sm.function(json , i);

          indexs_send.add_value_json(json.dump());
        }

        //repeated int32 task_index = 3;
        for(auto i : _task_index){
          indexs_send.add_task_index(i);
        }

        //repeated int32 dfv_index_backward = 4;
        for(auto i : _dfv_index_backward){
          indexs_send.add_dfv_index_backward(i);
        }

        //int32 partition = 5;
        indexs_send.set_partition(_partition_number);
        
        //int32 executor_number = 6;
        indexs_send.set_executor_number(_executor_number);

        reply response;
        ClientContext context;

        Status status = stub_->send_index(&context  , indexs_send , &response);

        if (status.ok()) {
          //根据的response中的信息更新gloabl的状态信息;
          update_global_data(response);

          return;
        }else{//任务没有执行成功
          std::cout << status.error_code() << ":" << status.error_message() << std::endl;
        }
    }

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
  template <typename T>//T表示传输数据的类型
  class Schedule{
    public:
      Schedule(std::string _filename , std::vector<std::string>& _executor_address , int _nParts)
        :filename(_filename) , executor_address(_executor_address) , done(false) , nParts(_nParts){}

      bool get_free_partition(DfcppPartitionResult& _partition , int& _partition_number);

      int publish_task(DfcppPartitionResult& _partition , int _partition_number);

      Sendclient* get_free_client(int& _executor_number);
      //开始跑咯
      void run();

    private:
      std::string filename;
      std::vector<std::string> executor_address;
      //这个还没有想好是不是用户传过来,用于表示划分图的partition个数
      int nParts;
      bool done;//表示任务调度是否完成

      //调度策略相关
      int which = 0;
      std::vector<T> dfv_values_v2;
  };

  template <typename T>
  void Schedule<T>::run(){
    //根据executor_address创造服务接口
    for (auto address : executor_address) {
      sendclients.push_back(Sendclient(grpc::CreateChannel(address , grpc::InsecureChannelCredentials())))  ;

      client_status.push_back(0);
    }
    //调用图划分算法
    int dfv_value_size;
    std::vector<DfcppPartitionResult*> result = dfcpp_graph_partition_by_dagP(const_cast<char*>(filename.data()), nParts , &dfv_value_size);

    //更行全局的dfv_value
    for (int i = 0; i < ; i++) {
      dfv_values_v2.push_back(new T());
    }

    for (int i = 0; i < dfv_value_size; i++) {
      dfv_value.push_back(0); 
    }

    partition_ptr = std::make_shared<std::vector<DfcppPartitionResult*>>(result);
    for (int i = 0; i < result.size(); i++) {
      partition_status.push_back(0);
    }

    //循环发布任务
    while(1){
      DfcppPartitionResult partition(nParts);
      int partition_number = -1;
      done = get_free_partition(partition , partition_number);//这里free表示可以发布给executor执行的任务
      if (partition_number == -1) {
        //sleep(1);
        continue;
      }


      int ret = publish_task(partition , partition_number);
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

  template <typename T>
  bool Schedule<T>::get_free_partition(DfcppPartitionResult& _partition , int& _partition_number){
    int i = 0; 

    //获取入度为0的分区
    for (auto partition : *partition_ptr) {
      if (partition->inDegree == 0 && partition_status.at(i) == 0) {
        _partition = *partition;
        _partition_number = i;
        return false; 
      }
      i++;
    }

    return true;
  }

  template <typename T>
  int Schedule<T>::publish_task(DfcppPartitionResult& _partition , int _partition_number){
    //得到要发布的executor
    int _executor_number;
    Sendclient* sendclient = get_free_client(_executor_number);//这里的free表示可以发布任务给这个executor
    if (sendclient == nullptr) {//表示所有的executor都在忙，不能发送任务，等待下一轮任务发布
      return -1;
    }

    //发布任务
    //获取最新的value值
    std::vector<int> values;
    std::vector<T> values_v2;
    for (auto i : _partition.inDfvs) {
      values_v2.push_back(dfv_values_v2.at(i));
      values.push_back(dfv_value.at(i));
    }

    partition_status.at(_partition_number) = 1;
    sendclient->send_index_client(_executor_number , _partition_number , _partition.inDfvs , values , _partition.nodes , _partition.outDfvs);

    return 1;
  }

  template <typename T>
  Sendclient* Schedule<T>::get_free_client(int& _executor_number){//涉及到Executor的管理

    //    调度策略1：轮询1
    //    //这个其实就是调度策略了,之后可以更改
    //    for (int i = 0; i < client_status.size(); i++) {
    //      if (client_status.at(i) == 0) {//表示client(Executor)空闲（free）
    //        client_status.at(i) = 1;//更新client(Executor)状态为忙碌，表示该Executor正在干活
    //        _executor_number = i;
    //        return &sendclients.at(i);
    //      }
    //    }
    //
    //所有client都忙碌中，等待下一次循环再来找free的client吧

    //调度策略2： 轮询2
    int client_size = client_status.size();

    for (int i = 0; i < client_size ; i++) {
      int j = (i + which) % client_size;

      if (client_status.at(j) == 0) {//表示client(Executor)空闲（free）
        client_status.at(j) = 1;//更新client(Executor)状态为忙碌，表示该Executor正在干活
        _executor_number = j;

        which++;
        return &sendclients.at(j);
      }
    }

    return nullptr;
  }
}

