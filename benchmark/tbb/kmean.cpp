//
// Created by ljr on 5/5/23.
//

#include <tbb/flow_graph.h>
#include <tbb/task_scheduler_init.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <memory>


using namespace tbb::flow;
using namespace std;

constexpr int NUMCLUSTER = 10;

inline float l2(float a, float b, float c, float d) {
    return (a - c) * (a - c) + (b - d) *(b - d);
}

long measure(int n, int k) {
    auto start = chrono::steady_clock::now();
    vector<float> x(n), y(n);
    for(int i = 0; i < n; i++) {
        x[i] = rand() % 1000 - 500;
        y[i] = rand() % 1000 - 500;
    }
    vector<float> anchorsX(NUMCLUSTER), anchorsY(NUMCLUSTER);
    vector<int> bestK(n);

    for(int i = 0; i < NUMCLUSTER; i++) {
        anchorsX[i] = x[i];
        anchorsY[i] = y[i];
    }

    tbb::task_scheduler_init init_(16);
    graph g;
    auto init = continue_node<continue_msg>(g, [](const continue_msg& msg){ return msg; });
    vector<shared_ptr<continue_node<continue_msg>>> nodes(n+1);

    for(int i = 0; i < n; i++) {
        nodes[i] = make_shared<continue_node<continue_msg>>(g,
            [&, i](const continue_msg& msg) mutable {
                float min_distance = std::numeric_limits<float>::max();
                int index = -1;
                for(int j = 0; j < NUMCLUSTER; j++) {
                    float distance = l2(anchorsX[j], anchorsY[j], x[i], y[i]);
                    if(distance <= min_distance) {
                        index = j;
                        min_distance = distance;
                    }
                }
                bestK[i] = index;
                return msg;
            }
        );
    }
    nodes[n] = make_shared<continue_node<continue_msg>>(g,
        [&](const continue_msg& msg) mutable {
            vector<int> counter(NUMCLUSTER);
            for(int i = 0; i < NUMCLUSTER; i++){
                anchorsX[i] = 0;
                anchorsY[i] = 0;
            }
            for(int i = 0; i < n; i++) {
                anchorsX[bestK[i]] += x[i];
                anchorsY[bestK[i]] += y[i];
                counter[bestK[i]]++;
            }

            for(int i = 0; i < NUMCLUSTER; i++) {
                anchorsX[i] /= counter[i];
                anchorsY[i] /= counter[i];
            }
        }
    );
    for(int i = 0; i < n; i++) {
        make_edge(init, *nodes[i]);
        make_edge(*nodes[i], *nodes[n]);
    }
    for(int i = 0; i < k; i++) {
        init.try_put(continue_msg{});
        g.wait_for_all();
    }

    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();   
}


int main(int argc, char** argv) {
    if(argc != 3) {
        cout << "usage :  kmean n k" << endl;
        return 0;
    }

    int n = atoi(argv[1]);  // 点数
    int k = atoi(argv[2]);  // 迭代次数
    int c = 20;
    double t = 0;
    for(int i = 0; i < c; i++)
    {
        t += measure(n, k);
    }
        
    printf("kmean %d %d :%lf ms\n", n, k, t/c);



};