#include "Graph.h"
#include <istream>
#include <fstream>
#include <sstream>

using namespace std;

//int  data_Readtsp(Graph &G) {
//    fstream infile;
//    char *line = new char[10000];
//    char *file = new char[40];
//    //infile.getline(cin, file, '\n');
//    cout << "please input filename:";
//    cin >> file;
//    infile.open(file, ios::in | ios::out);
//    if (!infile) {
//        cout << "error" << endl;
//        cout << "please input filename:";
//        cin >> file;
//        infile.open(file, ios::in | ios::out);
//    }
//    infile.getline(line, 10000);
//    int numNode;
//    infile >> numNode;//节点的个数
//    cout << numNode << endl;
//    while (!infile.eof()) {
//       // for (int i = 0; i != numNode; i++) {
//        int tempid;
//        infile >> tempid;
//        G.tempNode.id = tempid - 1;
//        infile >> G.tempNode.x >> G.tempNode.y;
//        G.Node.push_back(G.tempNode);
//        cout << G.tempNode.id << G.tempNode.x << G.tempNode.y << endl;
//   // }
//
//    }
//    if (line) {
//        delete line;
//    }
//    if (file) {
//        delete file;
//    }
//    infile.close();
//    return numNode;
//
//}

int readTspFile(Graph &G,std::string filename);
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
        instanceName = "kroA200.tsp";
        cout << instanceName << endl;
       // stringstream ss(str);
        stringstream infile;
        infile >> instanceName ;
        //if (instanceName.find("pmed") == string::npos) {
        //    instanceName = instanceName;//+ ".txt";
        //    numNode = readTxtFile(G, instanceName);
        //} else {
            instanceName = instanceName;//+ ".tsp";
            numNode = readTspFile(G, instanceName);
       // }
       
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
    cout << numNode << endl;

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
                //G.distance[G.Node[j].id][G.Node[i].id] = G.distance[G.Node[i].id][G.Node[j].id];
            }


        }
    }
    return numNode;

}

//int  readTxtFile(Graph &G,std::string filename) {
//    int numNode=0;
//    std::ifstream readFile(filename);
//    std::string str;
//    float MAXNUM = std::numeric_limits<float>::max();
//    G.distance = new float *[numNode + 1];
//    int Const = 0, u1, u2, dis, len = numNode;
//    for (int i = 0; i < len; i++) {
//        for (int j = 0; j < len; j++) {
//            G.distance[i][j] = MAXNUM;
//        }
//    }
//    while (std::getline(readFile, str)) {
//        if (Const && str != "EOF") {
//            std::stringstream infile(str);
//            infile >> u1 >> u2 >> dis;
//            G.distance[u1 - 1][u2 - 1] = dis;
//            G.distance[u2 - 1][u1 - 1] = dis;
//        }
//        Const++;
//    }
//    for (int k = 0; k < len; k++) {
//        for (int i = 0; i < len; i++) {
//            for (int j = 0; j < len; j++) {
//                G.distance[i][j] = std::min(G.distance[i][j], G.distance[i][k] + G.distance[k][j]);
//            }
//        }
//    }
//    return numNode;
//}