
#include "dfcpp/dfrt.h"


using namespace std;
using namespace DFCPP;


void MainGraph() {
  DFGraph __graph_1;
  DFV<int> len = __graph_1.createDFV<int>(10);
  DFV<vector<DFV<int>> *> __DFCInternalName_0 = __graph_1.createDFV<vector<DFV<int>> *>();
  __graph_1.emplace([__DFCInternalName_0](DynamicTask &__dt, int __len_v) mutable {
    __DFCInternalName_0 = emptyDFV1d<int>(__dt, __len_v);
  }, make_tuple(len)).name("task1");

  DFV<vector<DFV<int>> *> a = __graph_1.createDFV<vector<DFV<int>> *>();
  __graph_1.emplace([a](DynamicTask &__dt, vector<DFV<int>> *____DFCInternalName_0_v) mutable {
    a = ____DFCInternalName_0_v;
  }, make_tuple(__DFCInternalName_0)).name("task2");

  __graph_1.emplace([a](DynamicTask &__dt, int __len_v) mutable {
    for_p(__dt, __len_v, [a](DynamicTask &__dt, int i) {
            DFV<DFV<int>> __DFCInternalName_1 = __dt.createDFV<DFV<int>>();
            __dt.emplace([i](DynamicTask &__dt, vector<DFV<int>> *__a_v) mutable {
              setDF<int>(getE<DFV<int>>(__a_v, i), i);
            }, make_tuple(a));
          }
    );
  }, make_tuple(len)).name("task3");

  __graph_1.emplace([a](DynamicTask &__dt, int __len_v) mutable {
    for_p(__dt, __len_v, [a](DynamicTask &__dt, int j) {
            DFV<int> pp = __dt.createDFV<int>();

            cout << j << endl;

            __dt.emplace([pp, j](DynamicTask &__dt, vector<DFV<int>> *__a_v) mutable {
              cout << j << endl;

              pp = getE<DFV<int>>(__a_v, j);
              cout <<"<<<<<\n";
            }, make_tuple(a));

            __dt.emplace([](DynamicTask &__dt, int __pp_v) mutable {

              print<int>(__pp_v);
              cout << "?????";
            }, make_tuple(pp));
          }
    );
  }, make_tuple(len)).name("task4");

  Executor executor;
  executor.run(__graph_1).wait();
}


int main() {
  MainGraph();
  return 0;
}