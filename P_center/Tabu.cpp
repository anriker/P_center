#include "Tabu.h"
//vector<vector <int> > ivec(m ,vector<int>(n,0)); //m*n的二维vector，所有元素初始化为0
using namespace std;
static int iter = 1;
Tabu::Tabu() {}
Tabu::Tabu(vector <Nodes> &Node) :Sc(0),
    TabuTenure(numNode, vector<int >(numNode, 0)),
    numNode(Node.size()),
    F(2, vector<int>(numNode, 0)),
    D(2, vector<double>(numNode, 0)),
    adjDic(distance) {

    #if 0
    Sc = 0;
    numNode = Node.size();
    vector <vector <int>> TabuTenure(numNode, vector<int >(numNode, 0));//禁忌表初始化
    TabuTenure.resize(numNode);
    for (int i = 0; i != numNode; i++) {
        TabuTenure[i].resize(numNode) ;
    }
    vector <vector <int>> F(2, vector<int>(numNode, 0));
    vector <vector <int>> D(2, vector<int>(numNode, 0));
    adjDic = distance;
    for (int j = 0; j != 2; j++) {
        for (int i = 0; i != Node.size(); i++) {
            F[j].push_back(0);
            D[j].push_back(0);//P、D表初始化
        }
    }
    #endif // 0
}
void Tabu::compDic(vector <Nodes> &Node, int &numNode) {//计算距离
    vector <vector <double>> distance(numNode, vector <double>(numNode, 0));
   // distance[numNode][numNode];
    for (int i = 0; i != Node.size() - 1; i++) {
        for (int j = i + 1; j != Node.size(); j++) {
            distance[Node[i].id][Node[j].id] = sqrt(double(abs(Node[i].x - Node[j].x) + abs(Node[i].y - Node[j].y)));
            distance[Node[j].id][Node[i].id] = distance[Node[i].id][Node[j].id];
            if (i == j) {
                distance[Node[i].id][Node[j].id] = 0;
            }
        }
    }
}
void Tabu::tabusearch(vector <Nodes> &Node) {
    //int longestN;//改为最长服务边及相应的被服务点
    pair Pair = { 0,0 };
    Scinfo ScInfo = { 0,0 };
    init(Node, ScInfo);//初始解
    //int iter;//迭代次数
    initfuncation(Node, pcenter, ScInfo);

    while (iter < 10000)//搜索条件
    {
        find_pair(Node, ScInfo, Pair);//tabu发现交换对
        change_pair(Node,  Pair);//更新交换对
        iter++;
    }

}
void Tabu::init(vector <Nodes> &Node, Scinfo &ScInfo) {
    pcenter.push_back(rand() % numNode - 1);
    //pcenter[0]=rand()% numNode-1;
    //int longestN;
    //for (int i = 0; i != numNode; i++) {
    //	if(pcenter[0]!=i)
    //		PtoNode[0].push_back = Node[i].id;//1对应的中心点是p[1]
    //}
    initfuncation(Node, pcenter, ScInfo);
    for (int i = 1; i != numPcenter; i++) {
        int tempP = findP(Node, ScInfo);
        initDandFtable(Node, tempP);
        pcenter.push_back(tempP);
        initfuncation(Node, pcenter, ScInfo);

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

int Tabu::findP(vector <Nodes> &Node, Scinfo &ScInfo) {
    vector <int> id;
    int tempP;
    for (int i = 0; i != numNode; i++) {
        if (adjDic[ScInfo.Scid][Node[i].id] < Sc) {
            id.push_back(Node[i].id);
        }
    }
    srand(time(0));
    int tempi = rand() % id.size() - 1;
    tempP = id[tempi];
    return tempP;
}

void Tabu::initDandFtable(vector <Nodes> &Node, int tempP) {

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

void Tabu::initfuncation(vector <Nodes> &Node, vector <int> pcenter, Scinfo &ScInfo) {
    int tempid1 = 0;//记录寻找过程中目标函数点
    int tempid2 = 0;
    double tempSc = 0;
    for (int i = 0; i != pcenter.size(); i++) {
        for (int j = 0; j != numNode; j++) {
            if (pcenter[i] != Node[j].id && tempSc < adjDic[pcenter[i]][Node[j].id]) {
                tempSc = adjDic[pcenter[i]][Node[j].id];
                tempid1 = pcenter[i];
                tempid2 = Node[j].id;
            }
        }
    }
    Sc = tempSc;
    ScPoint.Noden = tempid2;
    ScPoint.Nodep = tempid1;
    ScInfo.Sc = tempSc;
    ScInfo.Scid = tempid2;
    //return tempid2;
}


//int Tabu::findadd_facility(vector <Nodes> &Node) {
//    int f = ScPoint.Noden;
//    vector <int > Newf;
//    for (int i = 0; i != numNode; i++) {
//        if (adjDic[f][Node[i].id] < Sc) {
//            Newf.push_back(Node[i].id);
//        }
//    }
//
//}

void Tabu::find_pair(vector <Nodes> &Node, Scinfo &ScInfo, pair &Pair) {//确定交换对<nodei，centerj>
    int delt = 0;
    vector <int> id;//记录小于最长边的点对应的小于最长服务边的点
    int tempP;
    pair tabu_Pair = { 0 };
    pair no_tabu_pair = { 0 };
    for (int i = 0; i != numNode; i++) {
        if (adjDic[ScInfo.Scid][Node[i].id] < Sc) {
            id.push_back(Node[i].id);
        }
    }
    for (int i = 0; i != id.size(); i++) {
        //找最好的交换对


        
    }

}


void Tabu::add_facility(vector <Nodes> &Node, pair &Pair) {
    for (int i = 0; i != numNode; i++) {
        if (D[Node[i].id][0] > adjDic[Pair.nodeid][Node[i].id]) {
            D[Node[i].id][1] = D[Node[i].id][0];
            F[Node[i].id][1] = F[Node[i].id][0];
            D[Node[i].id][0] = adjDic[Pair.nodeid][i];
            F[Node[i].id][0] = Pair.nodeid;

        } else if (D[Node[i].id][1] > adjDic[Pair.nodeid][i]) {
            D[Node[i].id][1] = adjDic[Pair.nodeid][Node[i].id];
            F[Node[i].id][1] = Pair.nodeid;
        }

    }
    pcenter.push_back(Pair.nodeid);
    //pcenter[numPcenter + 1] = f;
}

int Tabu::findremove_facility(vector <Nodes> &Node, int f) {//前p个服务点中找到一个删除后产生的最大服务边最小的点删(禁忌策略找交换对<f,i>）
    vector <int> Mf(numPcenter, 0);
    double tempSc = 0;
    int tempScid;
    for (int j = 0; j != numPcenter; j++) {
        for (int i = 0; i != numNode; i++) {
            if (F[Node[i].id][0] == pcenter[j] && Mf[j] < D[Node[i].id][1]) {
                Mf[j] = D[Node[i].id][1];
            }
        }
    }
    tempSc = Mf[0];
    for (int j = 1; j != numPcenter; j++) {
        if (tempSc > Mf[j]) {
            tempSc = Mf[j];
            tempScid = j;
        } else if (tempSc == Mf[j]) {
            if (rand() % 2 == 0) {//相等时，随机选择
                tempSc = Mf[j];
                tempScid = j;
            }
        }
    }
    int i = pcenter[tempScid];
    //更新Sc
    if (tempSc > Sc) Sc = tempSc;
    return i;
    //return tempScid;//找到删除边在数组中的位置
}

void Tabu::remove_facility(vector <Nodes> &Node, pair &Pair) {
    int tempPlace;
    for (int j = 0; j != pcenter.size(); j++) {
        if (pcenter[j] == Pair.centerid) tempPlace = j;
    }
    //int f = pcenter[tempPlace];

    for (int i = 0; i != numNode; i++) {
        if (F[Node[i].id][0] = Pair.centerid) {
            D[Node[i].id][0] = D[Node[i].id][1];
            F[Node[i].id][0] = F[Node[i].id][1];
            int nextp = find_next(Node, Node[i].id, tempPlace);
            D[Node[i].id][1] = adjDic[nextp][i];
            F[Node[i].id][1] = nextp;

        } else if (F[Node[i].id][1] = Pair.centerid) {
            int nextp = find_next(Node, Node[i].id, tempPlace);
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


int Tabu::find_next(vector <Nodes> &Node, int v, int fplace) {
    double tempsecondmax = max;
    int tempsecondmaxP;
    for (int j = 0; j != numPcenter + 1; j++) {
        if (j != fplace && pcenter[j] != F[v][pcenter[j]] && tempsecondmax < adjDic[pcenter[j]][v]) {
            tempsecondmax = adjDic[pcenter[j]][v];
            tempsecondmaxP = pcenter[j];
        }
    }
    return tempsecondmaxP;
}


void Tabu::change_pair(vector <Nodes> &Node,pair &Pair) {
    //更新tabu表
    TabuTenure[Pair.centerid][Pair.nodeid] = TabuTenure[Pair.nodeid][Pair.centerid] = 100 + iter;

	add_facility(Node,Pair);//添加Pair.nodeid服务点
   // int i=findremove_facility(Node,f);
	remove_facility(Node,Pair);//删除Pair.centerid服务点
    
}

Tabu::~Tabu() {

}
