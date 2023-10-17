//此代码是一个临时的图算法，现在已经丢弃了
#ifndef DFCPP_MASTER_HPP
#define DFCPP_MASTER_HPP

//首先构思以下掌控者要怎么做，前面也提到过掌控者的任务有以下：

//1. 掌握全局图的信息
//      涉及到图如何存储
//2. 图的划分
//      对应任务产生器
//          任务发布的形式：1. vector<int> dfv_index 2. vector<int> value 3. vector<int> node_index
//3. 发布任务给Executor,并接受Executor的反馈
//      对应图更新器
#include <iostream>
#include <vector>
#include <map>
#include <memory>

namespace DFCPP{//新增_7-9
  //任务发布的形式：
  std::vector<int> dfv_index;
  std::vector<int> value;
  //用于表示需要发布的任务
  std::vector<int> node_index;

  struct edge_out{
    std::vector<int> node_index;//m_graph的下标
    std::vector<int> edge_index;//m_edge的下标
  };

  struct m_nodes{
    std::vector<int> edge_in_index;//表示入边，以下标索引edge数组
    struct edge_out edge_out_index;
    //int edge_in;//表示入度
  };

  //掌控者类,它应该包含3部分：
  //1. 管理图的数据结构以及一系列工具
  //2. 任务生产器:pub_tasks();返回Executor的反馈
  //3. 图更新器：update_graph();,接收Executor以及任务生产器的反馈并做出图的调整
  class Master{
    public:
      Master(){
        m_edge = {0 , 1 , 1 , 1 , 1 , 1 , 1};
        points = {1 , -2 , -3 , -4 , -3 , -5 , -4};
        dfv_value = {1 , 3 , 2 , 1 , 3 , 5 , 7};

        struct edge_out edge_out1;
        struct edge_out edge_out2;
        struct edge_out edge_out3;
        struct edge_out edge_out4;
        struct edge_out edge_out5;

//        edge_out1.node_index = {0 , 2};
//        edge_out2.node_index = {1};
//        edge_out3.node_index = {3};
//        edge_out4.node_index = {};

        edge_out1.edge_index = {1 , 3};
        edge_out2.edge_index = {2};
        edge_out3.edge_index = {};
        edge_out4.edge_index = {4};
        edge_out5.edge_index = {6};

        struct m_nodes m_nodes1;
        struct m_nodes m_nodes2;
        struct m_nodes m_nodes3;
        struct m_nodes m_nodes4;
        struct m_nodes m_nodes5;

        m_nodes1.edge_in_index ={0};
        m_nodes2.edge_in_index ={1};
        m_nodes3.edge_in_index ={2 , 4};
        m_nodes4.edge_in_index ={3 , 6};
        m_nodes5.edge_in_index ={5};

        m_nodes1.edge_out_index = edge_out1;
        m_nodes2.edge_out_index = edge_out2;
        m_nodes3.edge_out_index = edge_out3;
        m_nodes4.edge_out_index = edge_out4;
        m_nodes5.edge_out_index = edge_out5;

        m_graph = {
         m_nodes1,
         m_nodes2,
         m_nodes3,
         m_nodes4,
         m_nodes5,
        };
      }
      //      //图更新器，只是涉及到了数据更改，所以一般情况下都会成功
      //      void update_graph();
      //
      //      //任务生产器,它的输入就是图数据结构，它会根据图数据结构而自动产生任务，任务装在dfv_index;value;node_index当中
      void  pub_tasks();
      //
      //      //master启动器,启动器里面就是做一个循环吧，即更新图信息<->发布图信息
      //      run()
      //

      //管理图数据结构的工具
      void forward_go(int p , int edge_index);//让小矮人往前一步走，这个p是m_graph的下标
      void update_points(int p , int edge_index);
      void update_edge(int p);//更新m_edge数组
      bool p_can_go(int p);//判断小矮人可不可以往前走

    private:
      //管理图信息的数据结构
      std::vector<m_nodes> m_graph;
      std::vector<int> m_edge;//表示边,0表示小矮人踩着边，1表示边还在，-1表示边没了

      std::vector<int> points;//表示小矮人，大小为边的总数,里面装的是指m_graph的下标
      std::vector<int> dfv_value;//记录dfv对应的值
  };

  //产生任务，即将信息写入dfv_index , value , node_index当中
  void Master::pub_tasks(){
    //注意：如果循环了一轮都没有人走，说明图划分结束了
    int edge_index = 0;

    bool done = false;//表示任务是否已经划分完成
    int node_size = 0;

    int time = 0;//记录是第几次进入循环，要找个标志的原因是第一次进入Points循环可以记录下dfv_idnex以及dfv_value;

    while(!done)
    {
      time++;

      //记录dfv_index和dfv_value;
      if (time == 1) {//第一次进入
          for (int i = 0; i < m_edge.size(); i++) {
            if (m_edge.at(i) == 0) {//表示有小矮人在
              dfv_index.push_back(i);
              //相应的也可以把dfv_value记录下来
              value.push_back(dfv_value.at(i));
            }
          } 
      }
      //记录下这次遍历points的node_size大小，一边后面判断任务划分是否完成;
      node_size = node_index.size();
      for(auto point : points){
        if (point > 0) {
          forward_go(point - 1 , edge_index);
        }
        edge_index++;
      }

      //判断任务是否划分完成的标志就是看node_index有没有变化
      if (node_index.size() == node_size) {
       done = true; 
      }
    } 

  }

  void Master::forward_go(int p , int edge_index){
    //判断小矮人要不要往前走
    if (p_can_go(p)) {//如果可以往前走，就是表明当前小矮人指向的node可以作为task发布出去
      //把小矮人指向的node发布出去，这里的下标p其实就是标志了哪一个node，因为存储node是有顺序的.
      node_index.push_back(p);

      //更新小矮人数组，需要注意更新的时候要把兄弟也去掉,即有其它小矮人站在同一个节点的另外一个入边上等待的时候，这个时候你可以走了，也要把那个等待的小矮人去掉
      update_points(p , edge_index);

      //更新m_edge边数组,因为小矮人要往下踩了
      update_edge(p);
    }else{//不能往前走就等待

    }

  }

  void Master::update_points(int p , int edge_index){
    //分情况讨论：能执行这个说明小矮人能够往前走，那么只有下面几种情况：
    //1. 没有兄弟
    //2. 有兄弟且都有小矮人,这种情况的更新要出去兄弟小矮人在points
    //if (m_graph.at(p).edge_in_index.size() - 1== 0) {//没兄弟
      //nothing to do
      //points.at(edge_index) = -(points.at(edge_index));
    //}else{//有兄弟
      for (auto in_edge : m_graph.at(p).edge_in_index) {
        points.at(in_edge) = -(points.at(in_edge)) ;
      }
    //}

    //往下走,拿到出边，更新小矮人数组
    for (auto out_edge : m_graph.at(p).edge_out_index.edge_index) {
      points.at(out_edge) = -(points.at(out_edge));
    }

    update_edge(p);
  }

  //p为m_graph的下标，这个函数表示使得所有这个node的入边都为-1，所有的出边都为0（有小矮人）
  void Master::update_edge(int p){
    for (auto edge_index : m_graph.at(p).edge_in_index) {//所有的入边都为-1
      m_edge.at(edge_index) = -1;
    }

    for (auto edge_index : m_graph.at(p).edge_out_index.edge_index) {
      m_edge.at(edge_index) = 0;
    }
  }

  //判断小矮人可不可以往前走
  bool Master::p_can_go(int p){
    //判断依据就是所有的入边都ok
    for(auto edge_index : m_graph.at(p).edge_in_index){
      if (m_edge.at(edge_index) > 0) {
        return false;
      }
    }
    return true;
  }
}

#endif
