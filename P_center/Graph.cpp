#include "Graph.h"
#include <istream>
#include <fstream>
#include <sstream>

using namespace std;

int readTspFile(Graph &G, std::string filename);
int readTxtFile(Graph &G, std::string filename);
int  data_Readtsp(Graph &G) {
    /*string instanceList = INSTANCE_DIR;
    ifstream readFile(instanceList);
    string str;
    int temp;
    while (getline(readFile, str) && str != "EOF") {*/
    int numNode;
        string instanceName;
        cout << "please input filename:";
       // cin >> instanceName;
        instanceName = "pmed1.txt"; //"u1060.tsp"; // "u1817.tsp";//,"kroA200.tsp";
        cout << instanceName << endl;
       // stringstream ss(str);
        stringstream infile;
        infile >> instanceName ;
        if (instanceName.find("pmed") == string::npos) {
            instanceName = instanceName;//+ ".txt";
            numNode = readTspFile(G, instanceName);
        } else {
            instanceName = instanceName;//+ ".tsp";
            numNode = readTxtFile(G, instanceName);
        }
       
    //}
    return numNode;
}

int readTspFile(Graph &G,std::string filename) {
    std::ifstream readFile(filename);
    std::string str;
    float x, y;
    int id;
    int Const=0; 
   
    while (std::getline(readFile, str)) {
        if (Const && str != "EOF") {
            std::stringstream infile(str);
            
            infile >> id >> x >> y;
           G.tempNode = { id-1,x,y };
           G.Node.push_back(G.tempNode);
          // cout << G.tempNode.id << G.tempNode.x << G.tempNode.y << endl;
        }
       Const++;
    }
    int numNode = G.Node.size();
    cout <<"numNode: "<< numNode << endl;

    G.distance = new float *[numNode];
    for (int i = 0; i != numNode ; i++) {
        G.distance[i] = new float[numNode];
    }
    for (int i = 0; i != numNode; i++) {
        for (int j = i; j != numNode; j++) {
            float x2 = pow((G.Node[i].x - G.Node[j].x),2);
            float y2 = pow((G.Node[i].y - G.Node[j].y),2);
            if (i == j) {
                G.distance[G.Node[i].id][G.Node[j].id] = 0;
            } else {
                G.distance[G.Node[i].id][G.Node[j].id] = G.distance[G.Node[j].id][G.Node[i].id] = sqrt(x2 + y2);
            }
        }
    }
    return numNode;

}

int  readTxtFile(Graph &G,std::string filename) {
    int numNode,edgeNode,Pcenter;
    std::ifstream readfile(filename);
    std::string str;
    //int Const = 0;
    float maxnum = std::numeric_limits<float>::max();
    std::getline(readfile, str);
    std::stringstream infile(str);
    infile >> numNode >> edgeNode >> Pcenter;
    cout << "numNode,edgeNode,Pcenter:" << numNode << "," << edgeNode << "," << Pcenter << endl;

    G.distance = new float *[numNode];
    for (int i = 0; i != numNode; i++) {
        G.distance[i] = new float[numNode];
    }

    int  u1, u2, dis;
    for (int i = 0; i < numNode; i++) {
        for (int j = i; j < numNode; j++) {
            G.distance[j][i] = G.distance[i][j] = maxnum;
        }
    }
    while (std::getline(readfile, str)) {
        if ( str != "EOF") {
            std::stringstream infile(str);
            infile >> u1 >> u2 >> dis;
            //cout << u1 << "," << u2 << "," <<dis<< endl;
            G.distance[u1 - 1][u2 - 1] = dis;
            G.distance[u2 - 1][u1 - 1] = dis;
        }
    
    }
    for (int k = 0; k < numNode; k++) {
        for (int i = 0; i < numNode; i++) {
            for (int j = 0; j < numNode; j++) {
                G.distance[i][j] = std::min(G.distance[i][j], G.distance[i][k] + G.distance[k][j]);
            }
        }
    }
    
    return numNode;
}