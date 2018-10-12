#include "Tabu.h"
//vector<vector <int> > ivec(m ,vector<int>(n,0)); //m*n的二维vector，所有元素初始化为0
using namespace std;
Tabu::Tabu(){}
Tabu::Tabu(vector <Nodes> &Node)
{

	Sc = 0;
	numNode = Node.size();
	Table = 0 ;//禁忌表初始化
    adjDic=distance;
	for (int j = 0; j != 2; j++) {
		for (int i = 0; i !=Node.size(); i++) {
			F[j].push_back(0);
			D[j].push_back(0);//P、D表初始化
		}
	}
	
}

void Tabu::init(vector <Nodes> &Node) {
    pcenter.push_back(rand() % numNode - 1);
	//pcenter[0]=rand()% numNode-1;
	int longestN;
	//for (int i = 0; i != numNode; i++) {
	//	if(pcenter[0]!=i)
	//		PtoNode[0].push_back = Node[i].id;//1对应的中心点是p[1]
	//}
	longestN = initfuncation(Node,pcenter);
	for (int i = 1; i !=numPcenter; i++) {
		int tempP=findP(Node,longestN);
        initDandFtable(Node, tempP);
		//updatePtoNode(Node,tempP);
        pcenter.push_back(tempP);
       // pcenter[i] = tempP;
		longestN = initfuncation(Node, pcenter);

	}
}

//void Tabu::updatePtoNode(vector <Nodes> &Node,int nextP) {
//	for(int j=0;j!=pcenter.size();j++)
//		for (int i = 0; i != numNode; i++) {
//			if (adjDic[pcenter[j]][Node[i].id] > adjDic[nextP][Node[i].id])
//				PtoNode[pcenter.size() + 1][i] = Node[i].id;
//			else PtoNode[pcenter.size() + 1][i] = -1;
//		}
//}

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

void Tabu::initDandFtable(vector <Nodes> &Node,int tempP) {
    int mindicP = max;
    int mindicPid;
    int secondmindicP = max;
    int secondmindicPid;

    for (int j = 0; j != numNode; j++) {
        if (pcenter.size() == 1) {
            if (adjDic[pcenter[0]][Node[j].id] < adjDic[tempP][Node[j].id]) {
                D[Node[j].id][0] = adjDic[pcenter[0]][Node[j].id];
                F[Node[j].id][0] = pcenter[0];
                D[Node[j].id][1] = adjDic[tempP][Node[j].id];
                F[Node[j].id][1] = tempP;
            } else {
                D[Node[j].id][0] = adjDic[tempP][Node[j].id];
                F[Node[j].id][0] = tempP;
                D[Node[j].id][1] = adjDic[pcenter[0]][Node[j].id];
                F[Node[j].id][1] = pcenter[0];
            }
        } else {

            if (adjDic[tempP][Node[j].id] < D[Node[j].id][0]) {
                D[Node[j].id][1] = D[Node[j].id][0];
                F[Node[j].id][1] = F[Node[j].id][0];
                D[Node[j].id][0] = adjDic[tempP][Node[j].id];
                F[Node[j].id][0] = tempP;

            } else if (adjDic[tempP][Node[j].id] < D[Node[j].id][1]) {
                D[Node[j].id][1] = adjDic[tempP][Node[j].id];
                F[Node[j].id][1] = tempP;
            }

        }
    }
}

int Tabu::initfuncation(vector <Nodes> &Node,vector <int> pcenter) {
	int tempid1 = 0;//记录寻找过程中目标函数点
	int tempid2 = 0;
	int tempSc = 0;
	for (int i = 0; i != pcenter.size(); i++) {
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


void Tabu::tabusearch(vector <Nodes> &Node) {
    int longestN;

    longestN = initfuncation(Node, pcenter);

}
int Tabu::fine_move(vector <Nodes> &Node) {
	int f;
    int delt = 0;


	return f;//新增的服务边
}


void Tabu::add_facility(vector <Nodes> &Node,int f) {//有问题,f如何找
    for (int i = 0; i != numNode; i++) {
        if (D[Node[i].id][0] > adjDic[f][Node[i].id]) {
            D[Node[i].id][1] = D[Node[i].id][0];
            F[Node[i].id][1] = F[Node[i].id][0];
            D[Node[i].id][0] = adjDic[f][i];
            F[Node[i].id][0] = f;

        }
        else if (D[Node[i].id][1] > adjDic[f][i]) {
            D[Node[i].id][1] = adjDic[f][Node[i].id];
            F[Node[i].id][1] = f;
        }

    }
    pcenter.push_back(f);
    //pcenter[numPcenter + 1] = f;
}

int Tabu::findremove_facility(vector <Nodes> &Node) {//前p个服务点中找到一个删除后产生的最大服务边最小的点删
    vector <int> Mf(numPcenter,0);
    int tempSc=0;
    int tempScid;
    for (int j = 0; j != numPcenter; j++) {
        for (int i = 0; i != numNode; i++) {
            if (F[Node[i].id][0] == pcenter[j]&& Mf[j] < D[Node[i].id][1]) {
                Mf[j] = D[Node[i].id][1];
            }
        }
    }   
    tempSc = Mf[0];
    for (int j = 1; j != numPcenter; j++) {
        if (tempSc>Mf[j]) {
            tempSc = Mf[j];
            tempScid = j;
        }
        else if(tempSc == Mf[j]) {
            if (rand() % 2 == 0) {//相等时，随机选择
                tempSc = Mf[j];
                tempScid = j;
            }
        }
    }
    int f = pcenter[tempScid];
    //更新Sc
    if (tempSc > Sc) Sc = tempSc;
    return tempScid;//找到删除边在数组中的位置
}

void Tabu::remove_facility(vector <Nodes> &Node) {
    int tempPlace = findremove_facility(Node);
    int f = pcenter[tempPlace];
    for (int i = 0; i != numNode; i++) {
        if (F[Node[i].id][0] = f) {
            D[Node[i].id][0] = D[Node[i].id][1];
            F[Node[i].id][0] = F[Node[i].id][1];
            int nextp=find_next(Node,Node[i].id,tempPlace);
            D[Node[i].id][1] = adjDic[nextp][i];
            F[Node[i].id][1] = nextp;
            
        }
        else if (F[Node[i].id][1] = f) {
            int nextp=find_next(Node, Node[i].id,tempPlace);
            D[Node[i].id][1] = adjDic[nextp][i];
            F[Node[i].id][1] = nextp;
        }
    }
    pcenter[tempPlace] = pcenter[numPcenter + 1];
    pcenter[numPcenter + 1] = -1;
}
/*Mf为删除节点f后产生的最长服务边距离（不是当前历史最长距离），
对比所有服务边删除后产生的Mf，选择最小的删除其对应的点,
利用F和D表计算
*/


int Tabu::find_next(vector <Nodes> &Node, int v,int fplace) {
    int tempsecondmax=max;
    int tempsecondmaxP;
    for (int j = 0; j != numPcenter+1; j++) {
        if (j != fplace && pcenter[j]!=F[v][pcenter[j]]&&tempsecondmax<adjDic[pcenter[j]][v]) {
            tempsecondmax = adjDic[pcenter[j]][v];
            tempsecondmaxP = pcenter[j];
        }
    }
    return tempsecondmaxP;
}


void Tabu::find_pair(vector <Nodes> &Node,int f) {
    
	add_facility(Node,f);
	remove_facility(Node);
}

Tabu::~Tabu()
{

}
