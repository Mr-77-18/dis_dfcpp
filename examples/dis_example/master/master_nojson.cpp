#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include <chrono>

#include "schedule_v3.hpp"


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
using namespace std;
int main(int argc, char *argv[])
{

  std::cout << "1" << std::endl;
  if (argc < 3) {
    std::cout << "argc error , the argc should be like that: [exe] [filename] [nParts] [executor_address]" << std::endl;
  }

  //图
  std::string filename = argv[1];

  //分区数量
  int nParts = std::stoi(argv[2]);

  std::vector<std::string> executor_address;

  //executor地址
  for (int i = 3; i < argc; i++) {
    executor_address.push_back(std::string(argv[i]));
  }

  auto start = chrono::steady_clock::now();
  DFCPP::Schedule sc(filename , executor_address , nParts);  

  sc.run();

  auto end = chrono::steady_clock::now();

  std::cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << std::endl;


  return 0;
}
