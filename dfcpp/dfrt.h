//
// Created by aana on 22-11-15.
//

#ifndef DFCPP_DFRT_H
#define DFCPP_DFRT_H

#include <iostream>
#include <vector>

#include "dfcpp.hpp"

template<typename T>
void print(T i) {
  std::cout << i << std::endl;
}

template<typename T>
void setDF(DFCPP::DFV<T> d, T v) {
  d = v;
}

template<typename T>
T getE(std::vector<T> *a, int idx) {
  return (*a).at(idx);
}


void for_p(DFCPP::DynamicTask &__dt, int i, std::function<void(DFCPP::DynamicTask &, int)> func) {
  for (int j = 0; j < i; ++j) {
    __dt.emplace([func, j](DFCPP::DynamicTask &__dt) {
      func(__dt, j);
    });
  }
}

template<typename T>
std::vector<DFCPP::DFV<T>> *emptyDFV1d(DFCPP::DynamicTask &__dt, int len) {
  auto s = new std::vector<DFCPP::DFV<T>>;
  for (int i = 0; i < len; ++i) {
    s->push_back(__dt.createDFV<T>());
  }
  return s;
}

#endif //DFCPP_DFRT_H
