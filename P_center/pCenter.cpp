#include <iostream>
#include <math.h>
#include "Tabu.h"
#include "Graph.h"

using namespace std;

void compDic(vector <Nodes> &Node, int &numNode) {//º∆À„æ‡¿Î
    vector <vector <double>> distance(numNode, vector <double>(numNode, 0));
   // distance[numNode][numNode];
    for (int i = 0; i != Node.size() - 1; i++) {
        for (int j = i + 1; j != Node.size(); j++) {
            distance[Node[i].id][Node[j].id] = sqrt(double(abs(Node[i].x - Node[j].x) + abs(Node[i].y - Node[j].y)));
            distance[Node[j].id][Node[i].id] = distance[Node[i].id][Node[j].id];
            if (i == j) {
                distance[Node[i].id][Node[j].id] = 0;
            }
        }
    }
}