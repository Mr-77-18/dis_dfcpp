//
// Created by ljr on 5/7/23.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <thread>


using namespace std;

inline float l2(float a, float b, float c, float d) {
    return (a - c) * (a - c) + (b - d) *(b - d);
}

long measure(int n, int k, int iterations) {
    auto  start = chrono::steady_clock::now();
    vector<float> x(n), y(n);
    for(int i = 0; i < n; i++) {
        x[i] = rand() % 1000 - 500;
        y[i] = rand() % 1000 - 500;
    }
    vector<float> anchorsX(k), anchorsY(k);
    vector<int> bestK(n);

    for(int i = 0; i < k; i++) {
        anchorsX[i] = x[i];
        anchorsY[i] = y[i];
    }
    int nthread = 16;
    int blocksize = n / nthread;

    for(int _ = 0; _ < iterations; _++) {
        vector<thread> threads(nthread);
        int index = 0;
        for(int i = 0; i < nthread - 1; i++, index+= blocksize) {
            threads[i] = thread([&, left = index, right = index + blocksize](){
                for(int idx = left; idx < right; idx++) {
                    float min_distance = std::numeric_limits<float>::max();
                    int index = -1;
                    for(int j = 0; j < k; j++) {
                        float distance = l2(anchorsX[j], anchorsY[j], x[idx], y[idx]);
                        if(distance <= min_distance) {
                            index = j;
                            min_distance = distance;
                        }
                    }
                    bestK[idx] = index;
                }
            });
        }
        threads[nthread-1] = thread([&, left = index, right = n](){
            for(int idx = left; idx < right; idx++) {
                float min_distance = std::numeric_limits<float>::max();
                int index = -1;
                for(int j = 0; j < k; j++) {
                    float distance = l2(anchorsX[j], anchorsY[j], x[idx], y[idx]);
                    if(distance <= min_distance) {
                        index = j;
                        min_distance = distance;
                    }
                }
                bestK[idx] = index;
            }
        });
        for(auto& item : threads) {
            item.join();
        }

        vector<int> counter(k);
        for(int i = 0; i < k; i++){
            anchorsX[i] = 0;
            anchorsY[i] = 0;
        }
        for(int i = 0; i < n; i++) {
            anchorsX[bestK[i]] += x[i];
            anchorsY[bestK[i]] += y[i];
            counter[bestK[i]]++;
        }

        for(int i = 0; i < k; i++) {
            anchorsX[i] /= counter[i];
            anchorsY[i] /= counter[i];
        }
    }

    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

int main(int argc, char** argv) {

    if(argc != 4) {
        cout << "usage :  omp_kmean n k iterations" << endl;
        return 0;
    }

    int n = atoi(argv[1]);  // 点数
    int k = atoi(argv[2]);  // 迭代次数
    int iterations = atoi(argv[3]);
    double t = 0;
    int c = 20;
    for(int i = 0; i < c; i++)
        t += measure(n, k, iterations);
    printf("kmean %d %d :%lf ms\n", n, k, t/c);

    return 0;
}