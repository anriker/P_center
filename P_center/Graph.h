#ifndef PCENTER_Graph_H
#define PCENTER_Graph_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#define INSTANCE_DIR  "..\\Deploy\\Instance\\"
//#define INSTANCE_LIST "instance.txt"
using namespace std;
class Graph {

public:
   
    struct Nodes {
        int id;
        float x;
        float y;
    };
    Nodes tempNode;
    vector <Nodes> Node;
    //vector <vector <float>> distance;
    float **distance;
    vector<int> pcenter;
    /*Graph() :distance(maxNumNode, vector<float >(maxNumNode, 0)) {}
    ~Graph() {}*/
};
#endif // PCENTER_Graph_H