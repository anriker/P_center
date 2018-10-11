#include "Tabu.h"

using namespace std;
Tabu::Tabu(){}
Tabu::Tabu(vector <Nodes> &Node)
{

	Sc = 0;
	numNode = Node.size();
	Table = 0 ;//禁忌表初始化
    adjDic = distance;
	for (int j = 0; j != 2; j++) {
		for (int i = 0; i !=Node.size(); i++) {
			F[j].push_back(0);
			D[j].push_back(0);//P、D表初始化
		}
	}
	
}

void Tabu::init(vector <Nodes> &Node) {
	pcenter[0]=rand()% numNode-1;
	int longestN;
	for (int i = 0; i != numNode; i++) {
		if(pcenter[1]!=i)
			PtoNode[1].push_back = Node[i].id;//1对应的中心点是p[1]
	}
	longestN = initfuncation(Node,pcenter);
	for (int i = 0; i !=numPcenter; i++) {
		int tempP=findP(Node,longestN);
		updatePtoNode(Node,tempP);
		longestN = initfuncation(Node, pcenter);

	}
}

void Tabu::updatePtoNode(vector <Nodes> &Node,int nextP) {
	for(int j=0;j!=sizeof(pcenter);j++)
		for (int i = 0; i != numNode; i++) {
			if (adjDic[pcenter[j]][PtoNode[j][i]] > adjDic[nextP][PtoNode[j][i]])
				PtoNode[sizeof(pcenter) + 1][i] = Node[i].id;
			else PtoNode[sizeof(pcenter) + 1][i] = -1;
		}
}

int Tabu::findP(vector <Nodes> &Node, int longestN) {
	vector <int> id;
	int tempP;
	for (int i = 0; i != numNode; i++) {
		if (adjDic[longestN][Node[i].id] < Sc) {
			id.push_back(Node[i].id);
		}
	}
	srand(time(0));
	int tempi = rand() % id.size() - 1;
	tempP = id[tempi];
	return tempP;
}

int Tabu::initfuncation(vector <Nodes> &Node,vector <int> pcenter) {
	int tempid1 = 0;//记录寻找过程中目标函数点
	int tempid2 = 0;
	int tempSc = 0;
	for (int i = 0; i != sizeof(pcenter); i++) {
		for (int j = 0; j != numNode; j++) {
			if (pcenter[i] !=Node[j].id && tempSc< adjDic[pcenter[i]][Node[j].id]) {
				tempSc = adjDic[pcenter[i]][Node[j].id];
				tempid1 = pcenter[i];
				tempid2 = Node[j].id;
			}
		}

	}
	Sc = tempSc;
	return tempid2;
}

void Tabu::initDandFtable(vector <Nodes> &Node) {
    int mindicP=max;
    int mindicPid;
    int secondmindicP=max;
    int secondmindicPid;
    
    for (int j = 0; j != numNode; j++) {
        for (int i = 0; i != numPcenter; i++) {
            if (adjDic[pcenter[i]][Node[j].id] < mindicP) {
                mindicP = adjDic[pcenter[i]][Node[j].id];
                mindicPid = pcenter[i];
            } else if (adjDic[pcenter[i]][Node[j].id] < secondmindicP) {
                secondmindicP = adjDic[pcenter[i]][Node[j].id];
                secondmindicPid = pcenter[i];
            }
        }
        F[Node[j].id][0] = mindicPid;
        D[Node[j].id][0] = mindicP;
        F[Node[j].id][1] = secondmindicPid;
        D[Node[j].id][1] = secondmindicP;
    }
}

//void Tabu::initFtable(vector <Nodes> &Node) {
//
//}
void Tabu::tabusearch(vector <Nodes> &Node) {
    int longestN;

    longestN = initfuncation(Node, pcenter);

}
int Tabu::fine_move(vector <Nodes> &Node) {
	int f;
    int delt = 0;


	return f;//新增的服务边
}


void Tabu::add_facility(vector <Nodes> &Node,int f) {
    for (int i = 0; i != numNode; i++) {
        if (D[Node[i].id][0] > adjDic[f][i]) {
            D[Node[i].id][1] = D[Node[i].id][0];
            F[Node[i].id][1] = F[Node[i].id][0];
            D[Node[i].id][0] = adjDic[f][i];
            F[Node[i].id][0] = f;

        }
        else if (D[Node[i].id][1] > adjDic[f][i]) {
            D[Node[i].id][1] = adjDic[f][i];
            F[Node[i].id][1] = f;
        }

    }
}

int Tabu::findremove_facility(vector <Nodes> &Node) {
    vector <int> tempScarr(numPcenter,0);
    int tempSc=0;
    int tempScid;
    for (int j = 0; j != numPcenter; j++) {
        for (int i = 0; i != numNode; i++) {
            if (D[Node[i].id][0] = pcenter[j]&& tempScarr[j] < D[Node[i].id][1]) {
                tempScarr[j] = D[Node[i].id][1];
            }
        }
    }
    
    for (int j = 0; j != numPcenter; j++) {
        if (tempSc<tempScarr[j]) {
            tempSc = tempScarr[j];
            tempScid = j;
        }
    }
    int f = pcenter[tempScid];
    return f;
}
void Tabu::remove_facility(vector <Nodes> &Node) {
    int f = findremove_facility(Node);
    for (int i = 0; i != numNode; i++) {
        if (D[Node[i].id][0] = pcenter[f]) {
            D[Node[i].id][0] = D[Node[i].id][1];
            F[Node[i].id][0] = F[Node[i].id][1];
            int nextp=find_next(Node,Node[i].id);
            
        }
        else if (D[Node[i].id][1] = pcenter[f]) {
            int nextp=find_next(Node, Node[i].id);
            D[Node[i].id][1] = ;
            F[Node[i].id][1] = ;

        }
    }
}
/*Mf为删除节点f后产生的最长服务边距离（不是当前历史最长距离），
对比所有服务边删除后产生的Mf，选择最小的删除其对应的点,
利用F和D表计算
*/


int Tabu::find_next(vector <Nodes> &Node, int v) {
    for (int j = 0; j != numPcenter; j++) {

    }
}
void Tabu::find_pair(vector <Nodes> &Node,int f) {
 
	add_facility(Node,f);
	//remove_facility(Node);
}
Tabu::~Tabu()
{

}
