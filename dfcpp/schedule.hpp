//schedule.hpp负责对分布式的Executor进行调度
//作者：Senhong Liu
//时间：10/11
//调度模块的作用：
//1. 管理Executor的状态信息
//2. 发布任务

//1. 管理Executor的信息，即管理Sendclient结构体


namespace DFCPP{
  template<class T>
    class Schedule{
      public:
        Schedule()

          //跟Executor相关
          void add_client();
        void del_client();
        T& get_free_client();

        //跟partition相关
        std::vector<partition&> get_partition_run();

        private
          std::vector<T> schudult_client;
        //管理进科的接口中传过来的partition,主要是partition的拓扑相关
        partition 

    }
  //跟Executor相关
  void add_client();
  void del_client();
  T& get_free_client();

  //跟partition相关
  std::vector<partition&> get_partition_run();


}
