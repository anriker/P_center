#include <iostream>
#include <math.h>
#include "Tabu.h"


using namespace std;
void compDic(vector <Nodes> &Node,int &numNode);

int main(int argv,int argc[]) {
	vector <Nodes> nodes;
	int numNode = nodes.size();
	compDic(nodes,numNode);
	//node *nodes=new node[10];
	Tabu T(nodes);
}


void compDic(vector <Nodes> &Node,int &numNode) {//º∆À„æ‡¿Î
	dictance[numNode][numNode];
	for (int i = 0; i != Node.size()-1; i++) {
		for (int j = i + 1; j != Node.size(); j++) {
			dictance[Node[i].id][Node[j].id] = sqrt(double(abs(Node[i].x - Node[j].x) + abs(Node[i].y - Node[j].y)));
			dictance[Node[j].id][Node[i].id]= dictance[Node[i].id][Node[j].id];
			if (i == j) {
				dictance[Node[i].id][Node[j].id] = 0;
			}
		}
	}
}