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

    buf = new vector<string>(n);

    FILE* file = fopen(argv[1] , "w+");


    int node = 0;

    writeright(-1 , node);//-1代表不用写
    writeleft(0, node);


    for (int i = 0; i < n - 2; i++) {
        node++;
        writeright(i , node);
        writeleft(i+1 , node);
    }

    node++;
    writeright(n - 2 , node);//-1代表不用写
    writeleft(-1 , node);

    fprintf(file , "%s\n" , "digraph G{");

    string node_st;

    for (int i = 0; i < n; i++) {
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

