//
// Created by ljr on 11/19/22.
//

#include "dfcpp/Hoard.hpp"
#include <iostream>

using namespace DFCPP;
using namespace std;

int main() {
    HoardNuma hoardNuma;
    auto hoard = hoardNuma.getHoardByNuma(0);
    int * addr = (int*)hoard->alloc(sizeof(int));
    *addr = 10;
    cout << *addr << endl;
    hoard->free(addr, 4);
    addr = (int*)hoard->alloc(sizeof(int));
    hoard->free(addr, 4);

    return 0;
}