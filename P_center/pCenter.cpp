#include <iostream>
#include <math.h>
#include "Graph.h"

using namespace std;

//void compDic(Graph &G) {//º∆À„æ‡¿Î
//    //vector <vector <double>> distance(numNode, vector <double>(numNode, 0));
//   // distance[numNode][numNode];
//    for (int i = 0; i != G.Node.size() - 1; i++) {
//        for (int j = i + 1; j != G.Node.size(); j++) {
//            G.distance[G.Node[i].id][G.Node[j].id] = sqrt(double(abs(G.Node[i].x - G.Node[j].x) + abs(G.Node[i].y - G.Node[j].y)));
//            G.distance[G.Node[j].id][G.Node[i].id] = G.distance[G.Node[i].id][G.Node[j].id];
//            if (i == j) {
//                G.distance[G.Node[i].id][G.Node[j].id] = 0;
//            }
//        }
//    }
//}