#ifndef PCENTER_Graph_H
#define PCENTER_Graph_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Graph {

public:
   
    struct Nodes {
        int id;
        int	x;
        int y;
    };
    Nodes tempNode;
    vector <Nodes> Node;
    //vector <vector <double>> distance;
    double **distance;
    vector<int> pcenter;
    /*Graph() :distance(maxNumNode, vector<double >(maxNumNode, 0)) {}
    ~Graph() {}*/
};
#endif // PCENTER_Graph_H