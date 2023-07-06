//
// Created by ljr on 5/5/23.
//

#include <dfcpp/dfcpp.hpp>
#include <chrono>
#include <vector>
#include <iostream>


constexpr int NUMCLUSTER = 10;
using namespace DFCPP;
using namespace std;

inline float l2(float a, float b, float c, float d) {
    return (a - c) * (a - c) + (b - d) *(b - d);
}

long measure(int n, int k) {
    vector<float> x(n), y(n);
    for(int i = 0; i < n; i++) {
        x[i] = rand() % 1000 - 500;
        y[i] = rand() % 1000 - 500;
    }
    DFGraph dfGraph1;
    vector<float> anchorsX(NUMCLUSTER), anchorsY(NUMCLUSTER);
    vector<int> bestK(n);
    auto dfvs = dfGraph1.createDFVs<bool>(2);

    for(int i = 0; i < NUMCLUSTER; i++) {
        anchorsX[i] = x[i];
        anchorsY[i] = y[i];
    }


    for(int i = 0; i < n; i++) {
        dfGraph1.emplace([&, i]() mutable {
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
        });
    }

    DFGraph dfGraph2;
    auto task3 = dfGraph2.emplace(
            [&]() mutable {
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
            });

    Executor executor(16);
    auto start = chrono::steady_clock::now();
    for(int i = 0; i < k; i++) {
        executor.run(dfGraph1).wait();
//        executor.run(dfGraph2).wait();
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
        t += measure(n, k);
    printf("kmean %d %d :%lf ms\n", n, k, t/c);



};