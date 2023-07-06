#include <tbb/flow_graph.h>
#include <tbb/task_scheduler_init.h>
#include <chrono>
#include <vector>
#include <memory>
#include <random>
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

    int total = (1 << n) - 1;
    int non_leaves = (1 << (n - 1)) - 1;
    vector<shared_ptr<graph_node>> nodes(total + 1);
    vector<shared_ptr<split_node<tuple<Block, Block>>>> split_nodes(non_leaves + 1);

    graph g;
    auto source = make_shared<function_node<int, tuple<Block, Block>>>(g, unlimited,
        [](const int&)
        {
            Block output;
            for(int i = 0; i < BLOCKSIZE; i++) {
                output.data[i] = random() % 100;
            }
            return tuple{output, output};
        }
    );
    nodes[1] = source;
    split_nodes[1] = make_shared<split_node<tuple<Block, Block>>>(g);
    make_edge(*source, *split_nodes[1]);

    for(int i = 2; i <= non_leaves; i++) {
        auto node = make_shared<function_node<Block, tuple<Block, Block>>>(g, unlimited,
            [](const Block& input){
                Block output;
                for(int j = 0; j < BLOCKSIZE; j++) {
                    output.data[j] = input.data[j] + random() % 100;
                }
                return tuple{output, output};
            }
        );
        split_nodes[i] = make_shared<split_node<tuple<Block, Block>>>(g);
        nodes[i] = node;
        make_edge(*node, *split_nodes[i]);
        if(i % 2 == 0) {
            make_edge(output_port<0>(*split_nodes[i / 2]), *node);
        } else  {
            make_edge(output_port<1>(*split_nodes[i / 2]), *node);
        }
    }

    for(int i = non_leaves + 1; i <= total; i++) {
        auto node = make_shared<function_node<Block>>(g, unlimited,
            [](const Block& input){
                long long sumup;
                for(int j = 0; j < BLOCKSIZE; j++) {
                    sumup += input.data[j];
                }
            }
        );

        nodes[i] = node;
        if(i % 2 == 0) {
            make_edge(output_port<0>(*split_nodes[i / 2]), *node);
        } else  {
            make_edge(output_port<1>(*split_nodes[i / 2]), *node);
        }
    }

    auto start = chrono::steady_clock::now();
    source->try_put(1);
    g.wait_for_all();
    auto end = chrono::steady_clock::now();

    return chrono::duration_cast<chrono::milliseconds>(end - start).count();


}


int main(int argc, char** argv) {

    if(argc != 2) {
        cout << "tbb_linearchain n" << endl;
        return 0;
    }

    int n = atoi(argv[1]);
    double time = 0;
    int r = 10;
    for(int i = 0; i < r; i++) {
        time += measure(n);
    }

    cout << "tbb_binary_tree " << n << " BLOCKSIZE: " << BLOCKSIZE << " elapsed: " << time/ r << " ms" << endl;
    cout << "pid " << getpid() << endl;
    string cmd = "cat /proc/";
    cmd += to_string(getpid());
    cmd += "/status | grep VmPeak";
    int _ = system(cmd.c_str());


    return 0;
}