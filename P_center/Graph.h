#ifndef PCENTER_Graph_H
#define PCENTER_Graph_H

#include <iostream>
#include <string>
#include <vector>
//class Graph {

//public:
using namespace std;
struct Nodes {
    int id;
    int	x;
    int y;
};

vector <Nodes> Node;
vector <vector <double>> distance;
vector<int> pcenter;
//};
#endif // PCENTER_Graph_H