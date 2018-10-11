#include <iostream>
#include <fstream>
#include "Tabu.h"
#include "Graph.h"


using namespace std;
void compDic(vector <Nodes> &Node,int &numNode);

int main(int argv,int argc[]) {
   
    ofstream ofs("log.csv", ios::app);
   //

    ofs.close();
	int numNode = Node.size();
	compDic(Node,numNode);

	Tabu T(Node);
}

