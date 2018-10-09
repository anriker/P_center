#include "Tabu.h"

using namespace std;
Tabu::Tabu(){}
Tabu::Tabu(vector <Nodes> &Node)
{

	Sc = 0;
	numNode = Node.size();
	Table = 0 ;//禁忌表初始化
	for (int j = 0; j != 2; j++) {
		for (int i = 0; i !=Node.size(); i++) {
			F[j].push_back(0);
			D[j].push_back(0);//P、D表初始化
		}
	}
	
}

void Tabu::init(vector <Nodes> &Node) {
	*p=rand()% numNode-1;
	int longestN;
	for (int i = 0; i != numNode; i++) {
		if(p[1]!=i)
			PtoNode[1].push_back = Node[i].id;//1对应的中心点是p[1]
	}
	longestN = funcation(Node,p);
	for (int i = 0; i !=numP; i++) {
		int tempP=findP(Node,longestN);
		updatePtoNode(Node,tempP);
		longestN = funcation(Node, p);

	}
}

void Tabu::updatePtoNode(vector <Nodes> &Node,int nextP) {
	for(int j=0;j!=sizeof(p);j++)
		for (int i = 0; i != numNode; i++) {
			if (dictance[p[j]][PtoNode[j][i]] > dictance[nextP][PtoNode[j][i]])
				PtoNode[sizeof(p) + 1][i] = Node[i].id;
			else PtoNode[sizeof(p) + 1][i] = -1;
		}
}

int Tabu::findP(vector <Nodes> &Node, int longestN) {
	vector <int> id;
	int tempP;
	for (int i = 0; i != numNode; i++) {
		if (dictance[longestN][Node[i].id] < Sc) {
			id.push_back(Node[i].id);
		}
	}
	srand(time(0));
	int tempi = rand() % id.size() - 1;
	tempP = id[tempi];
	return tempP;
}

int Tabu::funcation(vector <Nodes> &Node,int *p) {
	int tempid1 = 0;//记录寻找过程中目标函数点
	int tempid2 = 0;
	int tempSc = 0;
	for (int i = 0; i != sizeof(p); i++) {
		for (int j = 0; j != numNode; j++) {
			if (p[i] !=Node[j].id && tempSc<dictance[p[i]][Node[j].id]) {
				tempSc = dictance[p[i]][Node[j].id];
				tempid1 = p[i];
				tempid2 = Node[j].id;
			}
		}

	}
	Sc = tempSc;
	return tempid2;
}

void Tabu::initDtable(vector <Nodes> &Node) {
	
}

void Tabu::initPtable(vector <Nodes> &Node) {

}

int Tabu::fine_move(vector <Nodes> &Node) {
	int i;

	return i;
}


void Tabu::add_facility(vector <Nodes> &Node) {

}

void Tabu::delete_facility(vector <Nodes> &Node) {

}
/*Mf为删除节点f后产生的最长服务边距离（不是当前历史最长距离），
对比所有服务边删除后产生的Mf，选择最小的删除其对应的点,
利用F和D表计算
*/

void Tabu::find_pair(vector <Nodes> &Node) {
	add_facility(Node);
	delete_facility(Node);
}
Tabu::~Tabu()
{

}
