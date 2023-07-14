#ifndef DFCPP_MASTER_HPP
#define DFCPP_MASTER_HPP

namespace DFCPP{//新增_7-9
  //master需要干什么
  //掌握全局图的信息
  //图的划分
  //发布任务给Executor
  //发布给Executor的形式如下：
  //1. vector<int> dfv_index
  //2. vector<int> value
  //3. vector<int> node_index

  std::vector<int> dfv_index;
  std::vector<int> value;
  std::vector<int> node_index;

  class Matrix;

  class Master{
    public:
      static Master& get_master(){
        static Master instance;
        return instance;
      }

      //提供更新图的工具：
      //更新dfv对应的值
      void set_dfv_value(int dfv_index , int value);

      //更新图状态信息，主要就是打标机，即哪些任务已经发布出去，哪些任务已经完成，哪些任务还没有完成
      void set_node_status(int node_index , int status);


      //任务划分需要的工具
      ////计算入度
      int get_in(int node_index);
      ////根据node找前向dfv
      std::vector<int> get_pre_dfv(int node_index);

      ////根据node找后向dfv
      std::vector<int> get_aft_dfv(int node_index);

      ////根据node找下一个Node
      std::vector<int> get_aft_node(int node_index);

      //更新dfv_index,value
      void add_dfv_pre_inedx(int node);

      void add_dfv_aft_index(int node);

      //更新入度
      void new_in_edge(int node);

      //指针往后走
      bool new_points(vector<int>* points , vector<int>* pre_node);

      //更新node_index
      void add_node_index(vector<int>* points);

      //任务划分
      void split_graph(){
        std::vector<int> parrell;
        //划分图从节点开始入手，找node_status为0的点。
        int i = 0;
        for (auto n : node_status) {
          if (n == 0 && in_edge[i] == 0) {//节点没有被分配出去，且没有入边
            parrell.push_back(i); 
            i++;
          }

          //算法核心，分为两块，并行度为1，并行度大于1
          if (parrell.size() == 1) {
            //表示并行度等于1
            int _node = parrell.pop();
            node_index.push_back(_node);//更新状态
            add_dfv_pre_index(_node);
            //入度需要更新-----------------------
            new_in_edge(_node);

            std::vector<int> aft_node;
            while(){
              if ((aft_node = get_aft_node(_node)).size() == 1) {
                _node = aft_node.pop();

                //判断一下入度是不是为1；
                if (in_edge[_node] == 0) {
                  node_index.push_back(_node);
                  //入度更新
                  new_in_edge(_node);
                }
              }else if(aft_node.size() > 1){
                add_dfv_pre_index(_node);
              }else{
                break;
              }
            }
          }

        }else{//并行度大于1
          int size = node_status.size();
          std::vector<int>* points = new std::vector<int>(size , 0);
          std::vector<int>* pre_node = new std::vector<int>(size , 0);

          int _node = parrell.pop();
          node_index.push_back(_node);
          add_pre_dfv_index(_node);//传输任务的前向Dfv


          points[_node] = 1;

          while(1){
            add_node_index(points);

            if (!new_points(points , pre_node)) {//new_points（）的作用是让指针往后走，并且记录上一个node,以便加上后向dfv信息
              break;
            }
          }
          add_aft_dfv_index(points , pre_node);
        }
      }

    private:
      Master(Matrix& _matrix , std:vector<int>& _dfv_value , std::vector<int> _node_status)//这两种数据在程序开始的时候就应该知道。
        :matrix(_matrix) , dfv_value(_dfv_value) , _node_status(node_status){
          //node的入度初始化
          for (int i = 0 ; i < node_status.size() ; i++) {
            in_edge.push_back(get_in(i));
          }
        }

      //用来存储图，注意:每一个matrix[i][j]都是dfv_map的key，用来索引dfv对应的值
      Matrix matrix;

      //管理DFV的号码和值，未来需要进行泛型化，即int需要泛化
      std::vector<int> dfv_value;

      //用于表示node对应的任务是否完成
      //0：任务未发布
      //1：任务发布
      //2：任务完成
      std::vector<int> node_status;

      std::vector<int> in_edge;//每一个顶点的入度
  }

  Master& gm = Master::get_master();

  void Master::set_dfv_value(int dfv_index , int value){
    //先判断参数的合法性
    if (dfv_index >= 0 && dev_index < dfv_value.size()) {
      dfv_value[dev_index] = value;
    }else{
      std::cout << "in set_dev_value(): the dfv_index is invalid." << std::endl;
    }
  }

  void Master::set_node_status(int node_index , int status){
    //先判断参数的合法性
    if (node_index >= 0 && node_index < node_status.size()) {
      node_status[node_index] = status;
      if (status == 2) {
        //2表示任务完成
        for (int i = 0; i < node_status.size() ; i++) {
          matrix.setElement(node_index , i , -(matrix.getElement(node_index , i)));//负数表示边已经去掉，用于计算入度，但是依然可以作为dfv的索引,一举两得,-1和1为dfv中的0索引
        }
      }
    }else{
      std::cout << "in set_node_status():the args is invalid." << std::endl;
    }
  }

  //任务划分需要的工具
  ////计算入度
  int Master::get_in(int node_index){
    int ret = 0;
    for (int i = 0; i < node_status.size(); i++) {
      if (matrix.getElement(i , node_index) > 0) {
        ret++;
      }
    }
    return ret;
  }

  ////根据node找前向dfv
  std::vector<int> Master::get_pre_dfv(int node_index){
    std::vector<int> ret;
    int index = -1;
    for(int i = 0 ; i < node_status.size() ; i++){
      if ((index = matrix.getElement(i , node_index)) != 0) {//不等于0表示有边，不管是大于0还是小于0都表示有边
        ret.push_back(std::abs(index) - 1);
      }
    }
  }

  ////根据node找后向dfv
  std::vector<int> Master::get_aft_dfv(int node_index){
    std::vector<int> ret;
    int index = -1;
    for (int i = 0; i < node_status.size(); i++) {
      if ((index = matrix.getElement(node_index , i)) != 0) {
        ret.push_back(std::abs(index) - 1);
      }  
    }
  }

  //更新dfv_index,value
  void Master::add_dfv_pre_inedx(int node){
    std::vector<int> _dfv_index = get_pre_dfv(node);
    for (auto dfv : _dfv_index) {
      dfv_index.push_back(dfv);
      value.push_back(dfv_value[dfv]);
    }
  }

  void Master::add_dfv_aft_index(int node){
    std::vector<int> _aft_index = get_aft_dfv(node):
      for (auto dfv : _dfv_index) {
        dfv_index.push_back(dfv);
        value.push_back(dfv_valuie[dfv]);
      }
  }

  //更新入度,指更新node所指向的node
  void Master::new_in_edge(int node){
    std::vector _aft_node;
    for (int i = 0; i < node_status.size(); i++) {
      if (matrix.getElement(node , i) != 0) {
        _aft_node.push_back(i);
      }
    }
  
    for (auto _index : _aft_node) {
      in_edge[_index] -= 1;
    }
  }

  //指针往后走
  bool Master::new_points(vector<int>* points , vector<int>* pre_node){
    std::vector<int> _aft_node;
    for (int i = 0; i < points.size(); i++) {
      if (points[i] != 0 && points[i] == in_edge[i]) {
        _aft_node = get_aft_node(i);
        for (auto n : _aft_node) {
          points->at(n) += 1;
          pre_node->at(n) = i;
        }
      }
    }
  }

  //更新node_index
  void Master::add_node_index(vector<int>* points){
    //如果入度和指针个数一样，就加入
    for (int i = 0; i < node_status.size(); i++) {
      if (points[i] == in_edge[i]) {
        node_index.push_back(i);
      }
    }
  }

  std::vector<int> Master::get_aft_node(int node_index){
    std::vector<int> ret;
    for (int i = 0; i < node_status.size(); i++) {
      if (matrix.getElement(node_index , i) != 0) {
        ret.push_back(i);
      }
    }
  }


  //存储图信息
  class Matrix{
    private:
      std::vector<vector<int>> data;
      int _length;
    public:
      Matrix(int length)
        :_length(length) , data(length , std::vector<int>(length , 0)){}

      int getlength(){
        return _length;
      }

      int getElement(int row , int col){
        if(row >= 0 && row < _length && col >= 0 && col < _length){
          return data[row][col];
        }else{
          std::cout << "the row or col is invalid" << std::endl;
          return 0;
        }
      }

      void setElement(int row , int col , int value){
        if(row >= 0 && row < _length && col >= 0 && col < _length){
          data[row][col] = value;
        }else{
          std::cout << "the row or col is invalid" << std::endl;
        }
      }
  }

#endif
