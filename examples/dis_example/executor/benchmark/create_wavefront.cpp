//
//
// Created by lsh in 11-10
//
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <vector>

using namespace std;

static int fd;
static vector<string>* buf;
//std::vector<string> buf(100);

void writeleft(int dfv_number , int node_number);
void writeright(int dfv_number , int node_number);

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "argc error" << endl;
    }

    int n = stoi(argv[2]);

    buf = new vector<string>(2 * n * (n  - 1) + 1);

    FILE* file = fopen(argv[1] , "w+");


    int node = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            node ++;
                if (i == 0 && j == 0) {
                    writeright(-1 , node);
                    writeleft(0 , node);
                    writeleft(n - 1 , node);

                }else if(i == 0 && j == n - 1){
                    writeright(n - 1 - 1 , node);
                    writeleft(j + n - 1, node);

                }else if(i == n - 1 && j == 0){
                    writeright(2 * n * (n - 1) - n - n + 1 , node);
                    writeleft(2 * n * (n - 1) - n+ 1 , node);

                }else if(i == n - 1 && j == n -1){
                    writeright(2 * n * (n - 1) - 1 , node);
                    writeright(2 * n * (n - 1) - n , node);
                }else if(i == 0){
                    writeright(j - 1 , node);
                    writeleft(j , node);
                    writeleft(j + n - 1 , node);

                }else if(j == 0){
                    writeright(i * (2 * n - 1) - n , node);
                    writeleft(i * (2 * n - 1) + n - 1 , node);
                    writeleft(i * (2* n - 1) , node);

                }else if(i == n - 1){
                    writeright(i * (2 * n - 1), node);
                    writeright(i * (2 * n - 1) - n + 1, node);
                    writeleft(i * (2 * n - 1) + 1 , node);

                }else if(j == n - 1){
                    writeright(i * (2 * n - 1) - 1 , node);
                    writeright(i * (2 * n - 1) - 1 + n - 1 , node);
                    writeleft(i * (2 * n - 1) - 1 + n - 1 + n , node);
                }else{
                    writeright(i * (2 * n - 1) + j - 1 , node);
                    writeright(i * (2 * n - 1) + j - n , node);
                    writeleft(i * (2 * n - 1) + j , node);
                    writeleft(i * (2 * n - 1) + j - 1 + n  , node);

                }
        }
    }
    fprintf(file , "%s\n" , "digraph G{");

    string node_st;

    for (int i = 0; i < n*n; i++) {
        node_st += to_string(i) + ";\n";
    }

    fprintf(file , "%s" , node_st.c_str());

    string edge_st;

    for (auto &st : *buf) {
        edge_st += st + "\n";
    }

    fprintf(file , "%s" , edge_st.c_str());

    fprintf(file , "%s\n" , "}");

    return 0;
}
void writeleft(int dfv_number , int node_number){
    if (dfv_number < 0) {
        return;
    }

    string st = buf->at(dfv_number);
    string new_st = to_string(node_number) + "->" + st;
    buf->at(dfv_number) = new_st;
}

void writeright(int dfv_number , int node_number){
    if (dfv_number < 0) {
        return;
    }

    string st = buf->at(dfv_number);
    string new_st = st + to_string(node_number) + ";";
    buf->at(dfv_number) = new_st;
}

