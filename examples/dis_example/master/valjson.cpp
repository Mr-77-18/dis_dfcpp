#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include "schedule_v2.hpp"

struct Mydata{
  int a;
  double b;
};

int main(int argc, char *argv[])
{
  type_name.push_back(typeid(int).name());
  type_name.push_back(typeid(double).name());

  if (argc < 3) {
    std::cout << "argc error , the argc should be like that: [exe] [filename] [nParts] [executor_address]" << std::endl;
  }

  cout << "1" << endl;

  //图
  std::string filename = argv[1];

  //分区数量
  int nParts = std::stoi(argv[2]);
cout << "2" << endl;


  std::vector<std::string> executor_address;

cout << "3" << endl;
  //executor地址
  for (int i = 3; i < argc; i++) {
    executor_address.push_back(std::string(argv[i]));
  }
cout << "4" << endl;

  DFCPP::Schedule<struct Mydata , int , double> sc(filename , executor_address , nParts);

cout << "5" << endl;
  sc.init(&Mydata::a , &Mydata::b);

  sc.run();

  return 0;
}
