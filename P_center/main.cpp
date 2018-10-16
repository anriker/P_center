#include <iostream>
#include <fstream>
#include "Solver.h"
#include "Graph.h"
#define maxNumNode 2000

using namespace std;

int data_Readtsp(Graph &G);
void compDic(Graph &G, int numNode);

int main(int argv, int argc[]) {

    ofstream ofs("log.csv", ios::app);
   //
    Graph G;
    ofs.close();
    int numNode = data_Readtsp(G);
    //cout << G.Node[0].id << " " << G.Node[0].x << endl;
    //int numNode = G.Node.size();
    compDic(G, numNode);
    int numP;
    cout << "please input number of center:";
    cin >> numP;
    Tabu T(G,numP);
    T.tabusearch(G);
    return 0;
}


void compDic(Graph &G, int numNode) {//º∆À„æ‡¿Î
    //vector <vector <double>> distance(numNode, vector <double>(numNode, 0));
    G.distance = new double *[numNode+1];
    for (int i = 0; i != numNode+1; i++) {
        G.distance[i] = new double[numNode+1]();
    }
    for (int i = 0; i != numNode; i++) {
        for (int j = i; j != numNode; j++) {
            int x2= (G.Node[i].x - G.Node[j].x)*(G.Node[i].x - G.Node[j].x);
            int y2= (G.Node[i].y - G.Node[j].y)*(G.Node[i].y - G.Node[j].y);
            if (i == j) {
                G.distance[G.Node[i].id][G.Node[j].id] = 0;
            }
            else {
                G.distance[G.Node[i].id][G.Node[j].id] = G.distance[G.Node[j].id][G.Node[i].id]= sqrt(double(x2 + y2));
                //G.distance[G.Node[j].id][G.Node[i].id] = G.distance[G.Node[i].id][G.Node[j].id];
            }
           
            
        }  
    }
   /* for (int i = 0; i != numNode; i++) {
        for (int j = 0; j != numNode; j++) {
            cout << G.distance[G.Node[i].id][G.Node[j].id] << "\t";
        }
        cout << endl;
    }*/
    /*for (int i = 0; i != numNode + 1; i++) {
        delete G.distance[i];
    }
    delete G.distance;*/
}
