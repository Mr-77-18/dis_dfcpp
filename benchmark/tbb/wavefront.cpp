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


constexpr int BLOCKSIZE = 512;
struct Block{
    long long data[BLOCKSIZE];
};


double measure(int n) {

    tbb::task_scheduler_init init(16);
    graph g;
    

    // 用于保存各节点对象，防止提前析构
    vector<vector<shared_ptr<graph_node>>> functional_nodes(n);
    vector<vector<shared_ptr<join_node<tuple<Block, Block>>>>> join_nodes(n);
    vector<vector<shared_ptr<split_node<tuple<Block, Block>>>>> split_nodes(n);
    vector<shared_ptr<sender<Block>>> row_senders(n);
    vector<shared_ptr<sender<Block>>> col_senders(n);
    shared_ptr<function_node<int, tuple<Block, Block>>> init_node;

    for(int i = 0; i < n; i++) {
        functional_nodes[i].resize(n);
        join_nodes[i].resize(n);
        split_nodes[i].resize(n);

        for(int j = 0; j < n; j++) {
            if(i == 0 && j == 0) {
                auto node = make_shared<function_node<int, tuple<Block, Block>>>(g, unlimited,
                    [](const int& ){
                        Block output;
                        for(int k = 0; k < BLOCKSIZE; k++) {
                            output.data[k] = random() % 100;
                        }
                        return tuple{output, output};
                    }
                );
                init_node = node;
                functional_nodes[i][j] = node;
                split_nodes[i][j] = make_shared<split_node<tuple<Block, Block>>>(g);
                make_edge(*node, *split_nodes[i][j]);
            } else if(i == 0 && j != n - 1) {
                auto node = make_shared<function_node<Block, tuple<Block, Block>>>(g, unlimited,
                    [](const Block& input ){
                        Block output;
                        for(int k = 0; k < BLOCKSIZE; k++) {
                            output.data[k] = input.data[k] +  random() % 100;
                        }
                        return tuple{output, output};
                    }
                );
                functional_nodes[i][j] = node;
                split_nodes[i][j] = make_shared<split_node<tuple<Block, Block>>>(g);
                make_edge(*node, *split_nodes[i][j]);
                make_edge(output_port<0>(*split_nodes[i][j-1]), *node);                
            } else if( i == 0 && j == n - 1) {
                auto node = make_shared<function_node<Block, Block>>(g, unlimited,
                    [](const Block& input ){
                        Block output;
                        for(int k = 0; k < BLOCKSIZE; k++) {
                            output.data[k] = input.data[k] +  random() % 100;
                        }
                        return output;
                    }
                );
                functional_nodes[i][j] = node;
                row_senders[i] = node;
                make_edge(output_port<0>(*split_nodes[i][j-1]), *node);                 
            } else if(i != n - 1 && j == 0) {
                auto node = make_shared<function_node<Block, tuple<Block, Block>>>(g, unlimited,
                    [](const Block& input ){
                        Block output;
                        for(int k = 0; k < BLOCKSIZE; k++) {
                            output.data[k] = input.data[k] +  random() % 100;
                        }
                        return tuple{output, output};
                    }
                );
                functional_nodes[i][j] = node;
                split_nodes[i][j] = make_shared<split_node<tuple<Block, Block>>>(g);
                make_edge(*node, *split_nodes[i][j]);
                make_edge(output_port<1>(*split_nodes[i - 1][j]), *node); 
            } else if(i == n - 1 && j == 0) {
                auto node = make_shared<function_node<Block, Block>>(g, unlimited,
                    [](const Block& input ){
                        Block output;
                        for(int k = 0; k < BLOCKSIZE; k++) {
                            output.data[k] = input.data[k] +  random() % 100;
                        }
                        return output;
                    }
                );
                functional_nodes[i][j] = node;
                make_edge(output_port<0>(*split_nodes[i - 1][j]), *node); 
                col_senders[j] = node;
            } else if( i == n -1 && j == n - 1) {
                auto node = make_shared<function_node<tuple<Block, Block>>>(g, unlimited,
                    [](const tuple<Block, Block>& input ){
                        Block output;
                        auto& [a, b] = input;
                        for(int k = 0; k < BLOCKSIZE; k++) {
                            output.data[k] = a.data[k] +  b.data[k];
                        }
                    }
                );
                functional_nodes[i][j] = node;
                join_nodes[i][j] = make_shared<join_node<tuple<Block, Block>>>(g);

                make_edge(*join_nodes[i][j], *node);
                make_edge(*row_senders[i - 1], input_port<1>(*join_nodes[i][j]));
                make_edge(*col_senders[j - 1], input_port<0>(*join_nodes[i][j]));                  

            } else if(i == n - 1 ) {     // 最后一行
                auto node = make_shared<function_node<tuple<Block, Block>, Block>>(g, unlimited,
                    [](const tuple<Block, Block>& input ){
                        Block output;
                        auto& [a, b] = input;
                        for(int k = 0; k < BLOCKSIZE; k++) {
                            output.data[k] = a.data[k] +  b.data[k];
                        }
                        return output;
                    }
                );
                functional_nodes[i][j] = node;
                col_senders[j] = node;
                join_nodes[i][j] = make_shared<join_node<tuple<Block, Block>>>(g);

                make_edge(*join_nodes[i][j], *node);
                make_edge(output_port<1>(*split_nodes[i - 1][j]), input_port<1>(*join_nodes[i][j]));
                make_edge(*col_senders[j - 1], input_port<0>(*join_nodes[i][j]));            

            } else if( j == n - 1 && i != 0) {
                auto node = make_shared<function_node<tuple<Block, Block>, Block>>(g, unlimited,
                    [](const tuple<Block, Block>& input ){
                        Block output;
                        auto& [a, b] = input;
                        for(int k = 0; k < BLOCKSIZE; k++) {
                            output.data[k] = a.data[k] +  b.data[k];
                        }
                        return output;
                    }
                );
                functional_nodes[i][j] = node;
                row_senders[i] = node;
                join_nodes[i][j] = make_shared<join_node<tuple<Block, Block>>>(g);

                make_edge(*join_nodes[i][j], *node);
                make_edge(output_port<0>(*split_nodes[i][j-1]), input_port<0>(*join_nodes[i][j]));
                make_edge(*row_senders[i - 1], input_port<1>(*join_nodes[i][j]));                 
            } else {// 中间
                auto node = make_shared<function_node<tuple<Block, Block>, tuple<Block, Block>>>(g, unlimited,
                    [](const tuple<Block, Block>& input ){
                        Block output;
                        auto& [a, b] = input;
                        for(int k = 0; k < BLOCKSIZE; k++) {
                            output.data[k] = a.data[k] +  b.data[k];
                        }
                        return tuple{output, output};
                    }
                );
                functional_nodes[i][j] = node;   
                join_nodes[i][j] = make_shared<join_node<tuple<Block, Block>>>(g);
                split_nodes[i][j] = make_shared<split_node<tuple<Block, Block>>>(g);
                make_edge(*node, *split_nodes[i][j]);
                make_edge(*join_nodes[i][j], *node);

                make_edge(output_port<0>(*split_nodes[i][j-1]), input_port<0>(*join_nodes[i][j]));
                make_edge(output_port<1>(*split_nodes[i-1][j]), input_port<1>(*join_nodes[i][j]));
            }


            
        }
    }


    auto start = chrono::steady_clock::now();
    init_node->try_put(1);
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
    double time = 0;
    int r = 10;
    for(int i = 0; i < r; i++) {
        time += measure(n);
    }

    cout << "tbb_wavefront " << n << " BlockSIZE: " << BLOCKSIZE << " elapsed: " << time / r << " ms" << endl;
    cout << "pid " << getpid() << endl;
    string cmd = "cat /proc/";
    cmd += to_string(getpid());
    cmd += "/status | grep VmPeak";
    int _ = system(cmd.c_str());


    return 0;
}