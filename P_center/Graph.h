#ifndef PCENTER_Graph_H
#define PCENTER_Graph_H

#include <iostream>
#include <string>
#include <vector>
//class Graph {

//public:
    struct Nodes {
        int id;
        int	x;
        int y;
    } ;

    std::vector <Nodes> Node;
    std::vector<std::vector <int>> distance;
    std::vector<int> pcenter;
//};
#endif // PCENTER_Graph_H