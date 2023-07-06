//
// Created by ljr on 12/9/22.
//

#include "dfcpp/dfcpp.hpp"

using namespace DFCPP;
using namespace std;


int main() {
    DFGraph dfGraph;
    auto a = dfGraph.createDFV<int>();
    dfGraph.emplace([](DFV<int> aa){
        aa = 5;
    }, make_tuple(), make_tuple(a));
    dfGraph.emplace([](int a, DFV<int> aa) {
        if(a > 0) {
            aa = a - 1;
            cout << "a = " << a << endl;
        }
    }, make_tuple(a), make_tuple(a));
    Executor executor(8);
    executor.run(dfGraph).wait();


    return 0;
}