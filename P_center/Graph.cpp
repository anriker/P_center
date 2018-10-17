#include "Graph.h"
#include <istream>
#include <fstream>
#include <sstream>

using namespace std;

int  data_Readtsp(Graph &G) {
    fstream infile;
    char *line = new char[10000];
    char *file = new char[40];
    //infile.getline(cin, file, '\n');
    cout << "please input filename:";
    cin >> file;
    infile.open(file, ios::in | ios::out);
    if (!infile) {
        cout << "error" << endl;
        cout << "please input filename:";
        cin >> file;
        infile.open(file, ios::in | ios::out);
    }
    infile.getline(line, 10000);
    int numNode;
    infile >> numNode;//±ßµÄ¸öÊý
    cout << numNode << endl;
    while (!infile.eof()) {
       // for (int i = 0; i != numNode; i++) {
            infile >> G.tempNode.id >> G.tempNode.x >> G.tempNode.y;
            G.Node.push_back(G.tempNode);
            //cout << G.tempNode.id << G.tempNode.x << G.tempNode.y << endl;
       // }
        
    }
    if (line) {
        delete line;
    }
    if (file) {
        delete file;
    }
    infile.close();
    return numNode;

}

 