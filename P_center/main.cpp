#include <iostream>
#include <fstream>
#include "Solver.h"
#include "Graph.h"
#define maxNumNode 2000

using namespace std;

int data_Readtsp(Graph &G);
void compDic1(Graph &G, int numNode);
int main(int argv, int argc[]) {

    Graph G;

    ofstream ofs("log.csv", ios::app);
    ofs.close();

    int numNode = data_Readtsp(G);
    int numP;
    cout << "please input number of center:";
    cin >> numP;
    while (1) {
        Tabu T(G, numNode, numP);
        T.tabusearch(G);
    }
    system("pause");
    return 0;
}

#if 0
void compDic1(Graph &G, int numNode) {//º∆À„æ‡¿Î
    //vector <vector <float>> distance(numNode, vector <float>(numNode, 0));
    G.distance = new float *[numNode+1];
    for (int i = 0; i != numNode+1; i++) {
        G.distance[i] = new float[numNode+1]();
    }
    for (int i = 0; i != numNode; i++) {
        for (int j = i; j != numNode; j++) {
            float x2= (G.Node[i].x - G.Node[j].x)*(G.Node[i].x - G.Node[j].x);
            float y2= (G.Node[i].y - G.Node[j].y)*(G.Node[i].y - G.Node[j].y);
            if (i == j) {
                G.distance[G.Node[i].id][G.Node[j].id] = 0;
            }
            else {
                G.distance[G.Node[i].id][G.Node[j].id] = G.distance[G.Node[j].id][G.Node[i].id]= sqrt(float(x2 + y2));
            }
           
            
        }  
    }

}
#endif 