#ifndef DFCPP_GLOBAL_HPP
#define DFCPP_GLOBAL_HPP
#include <vector>
#include <memory>
#include <vector>
#include <map>

namespace DFCPP {
  //新增_7-8
  //存储node信息
  std::vector<int> task_index;

  //存储前向dfv信息
  std::vector<int> dfv_index;
  std::vector<int> value;

  //存储后向dfv的索引
  std::vector<int> backward_index;

  class Node;
  class DFVComm;
  template<typename T>
    class DFV;

  class Global {//新增_lsh
    public:
      //使用单例模式创建唯一的Global实例
      static Global& get_global() {
        static Global instance; // 单例实例在首次调用时创建
        return instance;

      }

      void insert_node(Node* n);
      void insert_dfv(DFVComm* dfvc);
      Node* get_node(int _index);
      DFVComm* get_dfv(int _index);

      //_indexs表示需要写的DFV的下标，_value为对应的值
      template <class T>
        void set_dfv_write(std::vector<int> _indexs , std::vector<T> _value){
          int j = 0;
          for (auto i : _indexs) {
            T* data = new T(_value.at(j));
            (_dfvs.at(i))->set_data(data);

            for(auto n : _dfvs.at(i)->_nodes){
              n->setnodeready();
            }
            j++;
          }
        }

      template <class T>
        void get_dfv_value(std::vector<int> _dfv_index , std::vector<T>& _value);

      //以下代码存在问题，推测是向下转型的时候出错了
      //template <class T>
      //void set_dfv_write(std::vector<int> _indexs , std::vector<T> _value){
      //  for (int i = 0 ; i < _indexs.size() ; i++) {

      //   ((DFV<T>*)(_dfvs.at(i)))->set(_value.at(i));

      //    for (auto n : _dfvs.at(i)->_nodes) {
      //      n->setnodeready(); 
      //    }
      //  }
      //}
    private:
      Global() {}

      std::vector<Node*> _nodes;
      std::vector<DFVComm*> _dfvs;

  };

  template <class T>//新增10-16
    void Global::get_dfv_value(std::vector<int> _dfv_index , std::vector<T>& _value){
      for (auto i : _dfv_index) {
        try{
          //_value.push_back(77);
          void* ptr = _dfvs.at(i)->get_data();
          if (ptr == nullptr) {
            std::cout << "is nullptr and th dfv index is" << i << std::endl ;
          }else{
            _value.push_back(*(T*)ptr);
          }
          //_value.push_back(*((T*)(_dfvs.at(i)->get_data())));
        }catch(const std::exception& e){
          std::cerr << "Execrption caught:" << e.what() << std::endl;
        }
      }
    }

  //向全局的_nodes当中注册node节点
  void Global::insert_node(Node* n) {
    _nodes.push_back(n);

  }

  //向全局的_dfvs当中注册DFVComm节点
  void Global::insert_dfv(DFVComm* dfvc) {
    _dfvs.push_back(dfvc);

  }

  //根据下标_index取得对应的的node
  Node* Global::get_node(int _index) {
    if (_index >= 0 && _index < _nodes.size()) {
      return _nodes.at(_index);
    }

    return nullptr;
  }

  //根据下表_index取得对应的DFVComm
  DFVComm* Global::get_dfv(int _index) {
    if (_index >= 0 && _index < _dfvs.size()) {
      return _dfvs.at(_index);

    }
    return nullptr;
  }

  //全局唯一的图状态信息
  Global& gl = Global::get_global();
  std::map<std::string , int> g_intask_node;//新增_7-8
}  // namespace DFCPP


#endif
