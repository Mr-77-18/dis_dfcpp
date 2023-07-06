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

    tbb::task_scheduler_init init(8);

    graph g;
    function_node<int , Block> source(g, unlimited,
        [](const int&)
        {
            Block output;

            for(int i = 0; i < BLOCKSIZE; i++) {
                output.data[i] = random() % 100;
            }

            return output;

        });

    vector<shared_ptr<function_node<Block, Block>>> internal_nodes(n - 2);
    for(int i = 0; i < n - 2; i++) {
        internal_nodes[i] = make_shared<function_node<Block, Block>>(g,
            unlimited,  
            [](const Block& input)->Block{
                Block output;
                for(int i = 0; i < BLOCKSIZE; i++) {
                    output.data[i] = input.data[i] + random() % 100;
                }
                return output;
            }
        );
    }
    function_node<Block> terminus(g, 
        unlimited,
        [](const Block& input){
            long long total;
            for(int i = 0; i < BLOCKSIZE; i++) {
                total += input.data[i];
            }
    });

    make_edge(source, *internal_nodes[0]);
    for(int i = 0; i < n - 3; i++) {
        make_edge(*internal_nodes[i], *internal_nodes[i+1]);
    }
    make_edge(*internal_nodes.back(), terminus);

    auto start = chrono::steady_clock::now();
    source.try_put(1);
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
    for(int i = 0; i < 10; i++) {
        time += measure(n);
    }

    cout << "tbb_linear " << n << " BlockSIZE: " << BLOCKSIZE << " elapsed: " << time/ 10 << " ms" << endl;
    cout << "pid " << getpid() << endl;
    string cmd = "cat /proc/";
    cmd += to_string(getpid());
    cmd += "/status | grep VmPeak";
    int _ = system(cmd.c_str());


    return 0;
}