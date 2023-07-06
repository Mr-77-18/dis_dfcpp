#include <tbb/flow_graph.h>
#include <tbb/task_scheduler_init.h>
#include <chrono>
#include <vector>
#include <memory>
#include <random>
#include <tuple>
#include <iostream>
#include <unistd.h>

using namespace tbb::flow;
using namespace std;


constexpr int BLOCKSIZE = 1;
struct Block{
    long long data[BLOCKSIZE];
};


double measure(int n) {

    tbb::task_scheduler_init init(17);
    graph g;
    vector<vector<shared_ptr<function_node<int, Block>>>> matrix_a(n);
    vector<vector<shared_ptr<function_node<int, Block>>>> matrix_b(n);
    vector<vector<shared_ptr<function_node<tuple<Block, Block>>>>> matrix_c(n);
    vector<vector<shared_ptr<join_node<tuple<Block, Block>>>>> join_nodes(n);

    for(int i = 0; i < n; i++) {
        matrix_a[i].resize(n);
        matrix_b[i].resize(n);
        matrix_c[i].resize(n);
        join_nodes[i].resize(n);
        for(int j = 0; j < n; j++) {
            matrix_a[i][j] = make_shared<function_node<int, Block>>(g, unlimited,
                [](const int&){
                    Block output;
                    for(int k = 0; k < BLOCKSIZE; k++) {
                        output.data[k] = random() % 100;
                    }
                    return output;
                }
            );
            matrix_b[i][j] = make_shared<function_node<int, Block>>(g, unlimited,
                [](const int&){
                    Block output;
                    for(int k = 0; k < BLOCKSIZE; k++) {
                        output.data[k] = random() % 100;
                    }
                    return output;
                }
            );
            matrix_c[i][j] = make_shared<function_node<tuple<Block, Block>>>(g, unlimited,
                [](const tuple<Block, Block>& input){
                    Block output;
                    auto& [a, b] = input;
                    for(int k = 0; k < BLOCKSIZE; k++) {
                        output.data[k] = a.data[k] +  b.data[k];
                    }
                }
            );
            join_nodes[i][j] = make_shared<join_node<tuple<Block, Block>>>(g);
            make_edge(*matrix_a[i][j], input_port<0>(*join_nodes[i][j]));
            make_edge(*matrix_b[i][j], input_port<1>(*join_nodes[i][j]));
            make_edge(*join_nodes[i][j], *matrix_c[i][j]);
        }
    }



    auto start = chrono::steady_clock::now();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            matrix_a[i][j]->try_put(1);
            matrix_b[i][j]->try_put(1);
        }
    }
    g.wait_for_all();
    auto end = chrono::steady_clock::now();

    return chrono::duration_cast<chrono::milliseconds>(end - start).count();


}


int main(int argc, char** argv) {

    if(argc != 2) {
        cout << "tbb_wavefront n" << endl;
        return 0;
    }
    int n = atoi(argv[1]);
    // int n = 3;
    double time = 0;
    for(int i = 0; i < 10; i++) {
        time += measure(n);
    }

    cout << "tbb_matdot " << n << " BlockSIZE: " << BLOCKSIZE << " elapsed: " << time/ 10 << " ms" << endl;
    cout << "pid " << getpid() << endl;
    string cmd = "cat /proc/";
    cmd += to_string(getpid());
    cmd += "/status | grep VmPeak";
    int _ = system(cmd.c_str());


    return 0;
}