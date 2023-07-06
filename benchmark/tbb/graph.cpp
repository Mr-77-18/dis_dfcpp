#include <tbb/flow_graph.h>
#include <tbb/task_scheduler_init.h>
#include <chrono>
#include <vector>
#include <memory>
#include <random>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <unistd.h>

using namespace tbb::flow;
using namespace std;


constexpr int BLOCKSIZE = 1;
struct Block{
    long long data[BLOCKSIZE];
};


double measure(int level, int length) {

    tbb::task_scheduler_init init(16);
    graph g;
    std::mt19937 grand(0);  
    std::srand(0);
    vector<vector<shared_ptr<sender<Block>>>> senders(level - 1, vector<shared_ptr<sender<Block>>>(length));
    vector<vector<shared_ptr<graph_node>>> nodes(level, vector<shared_ptr<graph_node>>(length));
    vector<shared_ptr<join_node<tuple<Block, Block, Block, Block>>>> joiners;
    vector<shared_ptr<function_node<int, Block>>> sources;


    // 第一层
    for(int i = 0; i < length; i++) {
        auto node = make_shared<function_node<int, Block>>(g, unlimited,
            [](const int &) {
                Block output;
                for(auto& item : output.data) {
                    item = random() % 100;
                }
                return output;
            }
        );
        senders[0][i] = node;
        nodes[0][i] = node;
        sources.emplace_back(node);
    }

    vector<int> edge_index;
    for(int i = 0; i < length; i++)
        edge_index.emplace_back(i);
    int s = 0;
    for(int j = 1; j < level - 1; j++) {
        shuffle(edge_index.begin(), edge_index.end(), grand);
        s = 0;
        for(int i = 0; i < length; i++) {
            if(s + 3 >= length) {
                shuffle(edge_index.begin(), edge_index.end(), grand);
                s = 0;
            }
            vector<int> edges(edge_index.begin() + s, edge_index.end() + s + 4);

            auto node = make_shared<function_node<tuple<Block, Block, Block, Block>, Block>>(g, unlimited,
                [](const tuple<Block, Block, Block, Block>& inputs){
                    auto& [in1, in2, in3, in4] = inputs;
                    Block output;
                    for(int k = 0; k < BLOCKSIZE; k++) {
                        output.data[k] = in1.data[k] + in2.data[k] + in3.data[k] + in4.data[k];
                    }
                    return output;
                }
            );
            senders[j][i] = node;
            nodes[j][i] = node;
            auto joiner = make_shared<join_node<tuple<Block, Block, Block, Block>>>(g);
            joiners.emplace_back(joiner);
            make_edge(*joiner, *node);
            make_edge(*senders[j - 1][edges[0]], input_port<0>(*joiner));
            make_edge(*senders[j - 1][edges[1]], input_port<1>(*joiner));
            make_edge(*senders[j - 1][edges[2]], input_port<2>(*joiner));
            make_edge(*senders[j - 1][edges[3]], input_port<3>(*joiner));
        }
    }

    // 最后一层
    shuffle(edge_index.begin(), edge_index.end(), grand);
    s = 0;
    for(int i = 0; i < length; i++) {
        if(s + 3 >= length) {
            shuffle(edge_index.begin(), edge_index.end(), grand);
            s = 0;
        }  
        vector<int> edges(edge_index.begin() + s, edge_index.end() + s + 4);

        auto node = make_shared<function_node<tuple<Block, Block, Block, Block>>>(g, unlimited,
            [](const tuple<Block, Block, Block, Block>& inputs){
                auto& [in1, in2, in3, in4] = inputs;
                long long sumup = 0;
                for(int k = 0; k < BLOCKSIZE; k++) {
                    sumup += in1.data[k]; 
                    sumup += in2.data[k];
                    sumup += in3.data[k];
                    sumup += in4.data[k];
                }
            }
        );
        nodes[level-1][i] = node;
        auto joiner = make_shared<join_node<tuple<Block, Block, Block, Block>>>(g);
        joiners.emplace_back(joiner);
        make_edge(*joiner, *node);
        make_edge(*senders[level - 2][edges[0]], input_port<0>(*joiner));
        make_edge(*senders[level - 2][edges[1]], input_port<1>(*joiner));
        make_edge(*senders[level - 2][edges[2]], input_port<2>(*joiner));
        make_edge(*senders[level - 2][edges[3]], input_port<3>(*joiner));
           
    }

    auto start = chrono::steady_clock::now();
    for(int i= 0; i < 10; i++) {
        for(auto& item : sources) {
            item->try_put(1);
        }
        g.wait_for_all();
    }


    auto end = chrono::steady_clock::now();

    return chrono::duration_cast<chrono::milliseconds>(end - start).count();


}


int main(int argc, char** argv) {

    if(argc != 3) {
        cout << "tbb_graph level length" << endl;
        return 0;
    }
    int level = atoi(argv[1]);
    int length = atoi(argv[2]);
    double time = 0;
    // for(int i = 0; i < 10; i++) {
        time += measure(level, length);
    // }

    cout << "tbb_graph level : " << level << " length : " << length << " BlockSIZE: " << BLOCKSIZE << " elapsed: " << time / 10 << " ms" << endl;
    cout << "pid " << getpid() << endl;
    string cmd = "cat /proc/";
    cmd += to_string(getpid());
    cmd += "/status | grep VmPeak";
    int _ = system(cmd.c_str());
    return 0;
}