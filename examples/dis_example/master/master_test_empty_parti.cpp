#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include "schedule.hpp"


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
int main(int argc, char *argv[])
{
  if (argc < 3) {
    std::cout << "argc error" << std::endl;
  }

  std::string filename = argv[1];

  int nParts = std::stoi(argv[2]);

  std::vector<std::string> executor_address = {
    "localhost:50057",
    "localhost:50058",
  };

  DFCPP::Schedule sc(filename , executor_address , nParts);

  sc.run();

  return 0;
}
