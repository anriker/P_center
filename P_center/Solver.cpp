#include "Solver.h"
//vector<vector <int> > ivec(m ,vector<int>(n,0)); //m*n的二维vector，所有元素初始化为0
using namespace std;
static int iter = 1;
Tabu::Tabu() {}
Tabu::Tabu(Graph &G,int numP) :Sc(0),
    numNode(G.Node.size()), 
    numPcenter(numP),
    TabuTenure(numNode, vector<int >(numNode, 0)),  
    //pcenter(numP,0),
    F(2, vector<int>(numNode, 0)),
    D(2, vector<double>(numNode, 0))
    //G.distance(G.distance)
{

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
    G.distance = distance;
    for (int j = 0; j != 2; j++) {
        for (int i = 0; i != Node.size(); i++) {
            F[j].push_back(0);
            D[j].push_back(0);//P、D表初始化
        }
    }
    #endif // 0
}

//void Tabu::compDic(Graph &G, int &numNode) {//计算距离
//    vector <vector <double>> distance(numNode, vector <double>(numNode, 0));
//   // distance[numNode][numNode];
//    for (int i = 0; i != numNode - 1; i++) {
//        for (int j = i + 1; j != numNode; j++) {
//            distance[G.Node[i].id][Node[j].id] = sqrt(double(abs(Node[i].x - Node[j].x) + abs(Node[i].y - Node[j].y)));
//            distance[Node[j].id][Node[i].id] = distance[Node[i].id][Node[j].id];
//            if (i == j) {
//                distance[Node[i].id][Node[j].id] = 0;
//            }
//        }
//    }
//}
void Tabu::tabusearch(Graph &G) {
    //int longestN;//改为最长服务边及相应的被服务点
    pair Pair = { 0,0 };
    Scinfo ScInfo = { 0,0 };
    init(G, ScInfo);//初始解
    //int iter;//迭代次数
    initfuncation(G, pcenter, ScInfo);

    while (iter < 10000)//搜索条件
    {
        find_pair(G, ScInfo, Pair);//tabu发现交换对
        change_pair(G, Pair);//更新交换对
        iter++;
    }
    for (int i = 0; i != pcenter.size(); i++) {
        cout << pcenter[i] << " ";
    }
    cout << ScInfo.Sc << endl;

}
void Tabu::init(Graph &G, Scinfo &ScInfo) {
    pcenter.push_back(rand() % numNode - 1);
    //pcenter[0]=rand()% numNode-1;
    //int longestN;
    //for (int i = 0; i != numNode; i++) {
    //	if(pcenter[0]!=i)
    //		PtoNode[0].push_back = Node[i].id;//1对应的中心点是p[1]
    //}
    for (int i = 0; i != numNode; i++) {
        D[G.Node[i].id][0] = G.distance[pcenter[0]][G.Node[i].id];
        F[G.Node[i].id][0] = pcenter[0];

    }
    
    initfuncation(G, pcenter, ScInfo);
    for (int i = 1; i != numPcenter; i++) {
        int tempP = findP(G, ScInfo);
        initDandFtable(G, tempP);
        pcenter.push_back(tempP);
        initfuncation(G, pcenter, ScInfo);

    }
}

//void Tabu::updatePtoNode(vector <Nodes> &Node,int nextP) {
//	for(int j=0;j!=pcenter.size();j++)
//		for (int i = 0; i != numNode; i++) {
//			if (G.distance[pcenter[j]][Node[i].id] > G.distance[nextP][Node[i].id])
//				PtoNode[pcenter.size() + 1][i] = Node[i].id;
//			else PtoNode[pcenter.size() + 1][i] = -1;
//		}
//}

int Tabu::findP(Graph &G, Scinfo &ScInfo) {
    vector <int> id;
    int tempP;
    for (int i = 0; i != numNode; i++) {
        if (G.distance[ScInfo.Scid][G.Node[i].id] < Sc) {
            id.push_back(G.Node[i].id);
        }
        cout << id[i] << " ";
    }cout << endl;
   
    int tempi=0;
    if (id.size() > 1) {
        srand(time(0));
        tempi = rand() % id.size();
    }
    //else if (id.size() == 0) {//当前最长服务边对应的点已经找不到可改善的点

    //}
    
    tempP = id[tempi];
    return tempP;
}

void Tabu::initDandFtable(Graph &G, int tempP) {

    for (int j = 0; j != numNode; j++) {
        if (pcenter.size() == 1) {
            if (G.distance[pcenter[0]][G.Node[j].id] < G.distance[tempP][G.Node[j].id]) {
                D[G.Node[j].id][0] = G.distance[pcenter[0]][G.Node[j].id];
                F[G.Node[j].id][0] = pcenter[0];
                D[G.Node[j].id][1] = G.distance[tempP][G.Node[j].id];
                F[G.Node[j].id][1] = tempP;
            } else {
                D[G.Node[j].id][0] = G.distance[tempP][G.Node[j].id];
                F[G.Node[j].id][0] = tempP;
                D[G.Node[j].id][1] = G.distance[pcenter[0]][G.Node[j].id];
                F[G.Node[j].id][1] = pcenter[0];
            }
        } else {

            if (G.distance[tempP][G.Node[j].id] < D[G.Node[j].id][0]) {
                D[G.Node[j].id][1] = D[G.Node[j].id][0];
                F[G.Node[j].id][1] = F[G.Node[j].id][0];
                D[G.Node[j].id][0] = G.distance[tempP][G.Node[j].id];
                F[G.Node[j].id][0] = tempP;

            } else if (G.distance[tempP][G.Node[j].id] < D[G.Node[j].id][1]) {
                D[G.Node[j].id][1] = G.distance[tempP][G.Node[j].id];
                F[G.Node[j].id][1] = tempP;
            }

        }
    }
}

void Tabu::initfuncation(Graph &G, vector <int> pcenter, Scinfo &ScInfo) {
    int tempid1 = 0;//记录寻找过程中目标函数点
    int tempid2 = 0;
    double tempSc = 0;
    for (int i = 0; i != pcenter.size(); i++) {
        for (int j = 0; j != numNode; j++) {
            if (pcenter[i] != G.Node[j].id && F[G.Node[j].id][0] == pcenter[i] && tempSc < D[G.Node[j].id][0]) {
                tempSc = D[G.Node[j].id][0];//G.distance[pcenter[i]][G.Node[j].id];
                tempid1 = pcenter[i];
                tempid2 = G.Node[j].id;
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
//        if (G.distance[f][Node[i].id] < Sc) {
//            Newf.push_back(Node[i].id);
//        }
//    }
//
//}

void Tabu::find_pair(Graph &G, Scinfo &ScInfo, pair &Pair) {//确定交换对<nodei，centerj>
    double delt = 0.0;
    vector <int> id;//记录小于最长边的点对应的小于最长服务边的点
    vector <Scinfo> tempScinfo;
    vector <pair> tempPair;
    int tempP;
    pair tabu_pair = { 0 };
    pair no_tabu_pair = { 0 };
    int no_tabu_samenumber=0;
    int tabu_samenumber=0;
    for (int i = 0; i != numNode; i++) {
        if (G.distance[ScInfo.Scid][G.Node[i].id] < Sc) {
            id.push_back(G.Node[i].id);
        }
    }
    for (int i = 0; i != id.size(); i++) {
        //找最好的交换对
        pair tempPair1;
        tempPair1.nodeid = id[i];
        vector <vector <int> > tempF(F);
        vector <vector <double> > tempD(D);
        for (int j = 0; j != numNode; j++) {//添加了服务点id[i]
            if (tempD[G.Node[j].id][0] > G.distance[id[i]][G.Node[j].id]) {
                tempD[G.Node[j].id][1] = tempD[G.Node[j].id][0];
                tempF[G.Node[j].id][1] = tempF[G.Node[j].id][0];
                tempD[G.Node[j].id][0] = G.distance[id[i]][G.Node[j].id];
                tempF[G.Node[j].id][0] = id[i];
            } else if (tempD[G.Node[i].id][1] > G.distance[id[i]][G.Node[j].id ]) {
                tempD[G.Node[j].id][1] = G.distance[id[i]][G.Node[j].id];
                tempF[G.Node[j].id][1] = id[i];
            }
        }
        vector <int> Mf(numPcenter, 0);
        for (int t = 0; t!= pcenter.size(); t++) {//寻找加入节点后删除中心节点pcenter[j]得到的最长服务边
            for (int j = 0; j != numNode; j++) {
                if (tempF[G.Node[j].id][0] == pcenter[t] ){//&& Mf[t] < tempD[Node[j].id][1]) {
                    Mf[t] = tempD[G.Node[j].id][1];
                }
            }
        }
        tempScinfo[i].Sc = Mf[0];
        for (int t = 1; t != pcenter.size(); t++) {
            if (tempScinfo[i].Sc > Mf[t]) {
                tempScinfo[i].Sc = Mf[t];
                tempScinfo[i].Scid = pcenter[t];
            } else if (tempScinfo[i].Sc == Mf[t]) {
                if (rand() % 2 == 0) {//相等时，随机选择
                    tempScinfo[i].Sc = Mf[t];
                    tempPair1.centerid = pcenter[t];
                }
            }
            tempPair1.delt = ScInfo.Sc - tempScinfo[i].Sc;
        }
        tempPair.push_back(tempPair1);
    }
    for (int i = 0; i != id.size(); i++) {
        if (TabuTenure[tempPair[i].centerid][tempPair[i].nodeid] < iter) {//update the no_tabu best move;
            if (tempPair[i].delt > no_tabu_pair.delt) {
                no_tabu_pair = tempPair[i];
                no_tabu_samenumber = 1;
            } else if (tempPair[i].delt == no_tabu_pair.delt) {
                no_tabu_samenumber++;
                if (rand() % no_tabu_samenumber == 0)
                    no_tabu_pair = tempPair[i];
            }
        } else {//update the tabu best move;
            if (tempPair[i].delt > tabu_pair.delt) {
                tabu_pair = tempPair[i];
                tabu_samenumber = 1;
            } else if (tempPair[i].delt == tabu_pair.delt) {
                tabu_samenumber++;
                if (rand() % tabu_samenumber == 0)
                    tabu_pair = tempPair[i];
            }
        }

    }
    if ((tabu_pair.delt > no_tabu_pair.delt) && (tabu_pair.delt >0)) //解禁条件：禁忌解优于当前查找的非禁忌解中最好的且优于历史最优解
    {
        Pair = tabu_pair;
    } else
        Pair= no_tabu_pair;
    

}


void Tabu::add_facility(Graph &G, pair &Pair) {
    for (int i = 0; i != numNode; i++) {
        if (D[G.Node[i].id][0] > G.distance[Pair.nodeid][G.Node[i].id]) {
            D[G.Node[i].id][1] = D[G.Node[i].id][0];
            F[G.Node[i].id][1] = F[G.Node[i].id][0];
            D[G.Node[i].id][0] = G.distance[Pair.nodeid][i];
            F[G.Node[i].id][0] = Pair.nodeid;

        } else if (D[G.Node[i].id][1] > G.distance[Pair.nodeid][i]) {
            D[G.Node[i].id][1] = G.distance[Pair.nodeid][G.Node[i].id];
            F[G.Node[i].id][1] = Pair.nodeid;
        }

    }
    pcenter.push_back(Pair.nodeid);
    //pcenter[numPcenter + 1] = f;
}

#if 0
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
#endif

void Tabu::remove_facility(Graph &G, pair &Pair) {
    int tempPlace;
    for (int j = 0; j != pcenter.size(); j++) {
        if (pcenter[j] == Pair.centerid) tempPlace = j;
    }
    //int f = pcenter[tempPlace];

    for (int i = 0; i != numNode; i++) {
        if (F[G.Node[i].id][0] = Pair.centerid) {
            D[G.Node[i].id][0] = D[G.Node[i].id][1];
            F[G.Node[i].id][0] = F[G.Node[i].id][1];
            int nextp = find_next(G, G.Node[i].id, tempPlace);
            D[G.Node[i].id][1] = G.distance[nextp][i];
            F[G.Node[i].id][1] = nextp;

        } else if (F[G.Node[i].id][1] = Pair.centerid) {
            int nextp = find_next(G, G.Node[i].id, tempPlace);
            D[G.Node[i].id][1] = G.distance[nextp][i];
            F[G.Node[i].id][1] = nextp;
        }
    }
    pcenter[tempPlace] = pcenter[numPcenter + 1];
    pcenter[numPcenter + 1] = -1;
}
/*Mf为删除节点f后产生的最长服务边距离（不是当前历史最长距离），
对比所有服务边删除后产生的Mf，选择最小的删除其对应的点,
利用F和D表计算
*/


int Tabu::find_next(Graph &G, int v, int fplace) {
    double tempsecondmax = max;
    int tempsecondmaxP;
    for (int j = 0; j != numPcenter + 1; j++) {
        if (j != fplace && pcenter[j] != F[v][pcenter[j]] && tempsecondmax < G.distance[pcenter[j]][v]) {
            tempsecondmax = G.distance[pcenter[j]][v];
            tempsecondmaxP = pcenter[j];
        }
    }
    return tempsecondmaxP;
}


void Tabu::change_pair(Graph &G,pair &Pair) {
    //更新tabu表
    TabuTenure[Pair.centerid][Pair.nodeid] = TabuTenure[Pair.nodeid][Pair.centerid] = 100 + iter;

	add_facility(G,Pair);//添加Pair.nodeid服务点
   // int i=findremove_facility(Node,f);
	remove_facility(G,Pair);//删除Pair.centerid服务点
}

Tabu::~Tabu() {

}
