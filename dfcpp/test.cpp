#include <iostream> 

#include "master1.hpp"

using namespace DFCPP;

int main(int argc, char *argv[])
{
  Master master;
  master.pub_tasks();

  std::cout << "node_index is :" << std::endl;
  for(auto node : node_index){
    std::cout << node << " ";
  }

  std::cout << std::endl;

  std::cout << "dfv_idnex is :" << std::endl;
  for (auto dfv : dfv_index) {
    std::cout << dfv << " " ;
  }

  std::cout << std::endl;
  return 0;
}
