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

  std::vector<int> dfv_indx;
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

      //任务划分,!!!!!重点!!!!!

      

    private:
      Master(Matrix& _matrix , std:vector<int>& _dfv_value , std::vector<int> _node_status)//这两种数据在程序开始的时候就应该知道。
        :matrix(_matrix) , dfv_value(_dfv_value) , _node_status(node_status){}

      //用来存储图，注意:每一个matrix[i][j]都是dfv_map的key，用来索引dfv对应的值
      Matrix matrix;

      //管理DFV的号码和值，未来需要进行泛型化，即int需要泛化
      std::vector<int> dfv_value;

      //用于表示node对应的任务是否完成
      //0：任务未发布
      //1：任务发布
      //2：任务完成
      std::vector<int> node_status;
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
      if (matrix.getElement(i , node_index) <= 0) {
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
