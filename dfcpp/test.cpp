#include"dfcpp/dfcpp.hpp"
#include <iostream>
#include "global.hpp"

using namespace DFCPP;

int main(int argc, char *argv[])
{
  Global& gl = Global::get_global();

  std::cout << "end of the get_global()" << std::endl;
  return 0;
}
