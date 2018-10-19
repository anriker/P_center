//计算delt有错误
#include "Solver.h"
//vector<vector <int> > ivec(m ,vector<int>(n,0)); //m*n的二维vector，所有元素初始化为0
using namespace std;
static int iter = 1;
Tabu::Tabu() {}
Tabu::Tabu(Graph &G, int numN, int numP) :
best_solution(0),
flag(1),
numNode(numN),
numPcenter(numP),
TabuTenure(numNode, vector<int >(numNode, 0)),
//pcenter(numP,0),
F(numNode, vector<int>(2, 0)),
D(numNode, vector<float>(2, 0))
//G.distance(G.distance)
{
   // cout << numNode << endl;
    #if 0
    Sc = 0;
    numNode = Node.size();
    vector <vector <int>> TabuTenure(numNode, vector<int >(numNode, 0));//禁忌表初始化
    TabuTenure.resize(numNode);
    for (int i = 0; i != numNode; i++) {
        TabuTenure[i].resize(numNode);
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

void Tabu::tabusearch(Graph &G) {
    //int longestN;//改为最长服务边及相应的被服务点
    pair Pair = { 0,0 };
    Scinfo ScInfo = { 0,0 };
    init(G, ScInfo);//初始解
    //int iter;//迭代次数
    initfuncation(G, pcenter, ScInfo);
    best_solution = ScInfo.Sc;
   /* for (int i = 0; i != pcenter.size(); i++) {
        cout << pcenter[i] + 1 << " ";
    }*/
    cout << ScInfo.Sc << endl;
    clock_t start_time = clock();
    while (iter != MAX_ITER)//搜索条件
    {
        flag = 0;
        find_pair(G, ScInfo, Pair);//tabu发现交换对
        /*if (flag == 0)
            break;*/
        change_pair(G, Pair);//更新交换对 
        initfuncation(G, pcenter, ScInfo);
        if (abs(ScInfo.Sc - best_solution) < 0.01) {
            break;
        }
        if (ScInfo.Sc < best_solution)
            best_solution = ScInfo.Sc;
        cout << "change nodeid :" << Pair.nodeid << " and centerid " << Pair.centerid;
        cout << " ,the Sc is:" << ScInfo.Sc << endl;
      
        iter++;
    }
    clock_t end_time = clock();

    cout << "the iter: " << iter << endl;
    cout << "the pcenters of best solution :";
   
    for (int i = 0; i != pcenter.size(); i++) {
        cout << pcenter[i]+1 << " ";
    }
    cout << endl;
    cout << "the most solution: " << best_solution << endl;
    cout << "the time is:" << (end_time - start_time)*1.0 / CLOCKS_PER_SEC << "s" << endl;
}

void Tabu::init(Graph &G, Scinfo &ScInfo) {
    //srand(time(0));
    pcenter.push_back(rand() % numNode - 1);
    //pcenter[0]=rand()% numNode-1;
    //int longestN;
    //for (int i = 0; i != numNode; i++) {
    //	if(pcenter[0]!=i)
    //		PtoNode[0].push_back = Node[i].id;//1对应的中心点是p[1]
    //}
    for (int i = 0; i != numNode; i++) {
        D[i][0] = G.distance[pcenter[0]][i];
        F[i][0] = pcenter[0];

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
        if (G.distance[ScInfo.Scid][i] < ScInfo.Sc) {
            id.push_back(i);
            //cout << id[i] << " ";
        }

    }

    int tempi = 0;
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
            if (G.distance[pcenter[0]][j] < G.distance[tempP][j]) {
                D[j][0] = G.distance[pcenter[0]][j];
                F[j][0] = pcenter[0];
                D[j][1] = G.distance[tempP][j];
                F[j][1] = tempP;
            } else {
                D[j][0] = G.distance[tempP][j];
                F[j][0] = tempP;
                D[j][1] = G.distance[pcenter[0]][j];
                F[j][1] = pcenter[0];
            }
        } else {

            if (G.distance[tempP][j] < D[j][0]) {
                D[j][1] = D[j][0];
                F[j][1] = F[j][0];
                D[j][0] = G.distance[tempP][j];
                F[j][0] = tempP;

            } else if (G.distance[tempP][j] < D[j][1]) {
                D[j][1] = G.distance[tempP][j];
                F[j][1] = tempP;
            }

        }
    }
}

void Tabu::initfuncation(Graph &G, vector <int> pcenter, Scinfo &ScInfo) {
    //int tempid1 = 0;//记录寻找过程中目标函数点
    int tempid2 = 0;
    float tempSc = 0;
    int numSame = 0;
    for (int i = 0; i != pcenter.size(); i++) {
        for (int j = 0; j != numNode; j++) {//最长边对应的服务点有多个时应该随机选择一个
            if (pcenter[i] != j && F[j][0] == pcenter[i] && tempSc < D[j][0]) {
                tempSc = D[j][0];//G.distance[pcenter[i]][j];
                //tempid1 = pcenter[i];
                tempid2 = j;
                numSame = 1;
            }
            else if (pcenter[i] != j && F[j][0] == pcenter[i] && tempSc == D[j][0]) {
                numSame++;
                if (rand() % numSame == 0) {
                    tempSc = D[j][0];//G.distance[pcenter[i]][j];
                   // tempid1 = pcenter[i];
                    tempid2 = j;
                }
            }
        }
    }
    //Sc = tempSc;
    //ScPoint.Noden = tempid2;
    //ScPoint.Nodep = tempid1;
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
    float delt = 0.0;
    vector <int> id;//记录小于最长边的点对应的小于最长服务边的点
    vector <pair> tempPair;
    int tempP;
    pair tabu_pair = { 0 };
    pair no_tabu_pair = { 0 };
    int no_tabu_samenumber = 0;
    int tabu_samenumber = 0;
    for (int i = 0; i != numNode; i++) {
        if (G.distance[ScInfo.Scid][i] < ScInfo.Sc) {
            id.push_back(i);
        }
    }
    //cout << "the maxId:"<<ScInfo.Scid << endl;
    //cout << "the maxSc:" << ScInfo.Sc << endl;
    vector <Scinfo> tempScinfo(id.size());
    for (int i = 0; i != id.size(); i++) {
        //找最好的交换对
        pair tempPair1;
        vector <vector <int> > tempF(F);
        vector <vector <float> > tempD(D);
        for (int j = 0; j != numNode; j++) {//添加了服务点id[i]
            if (tempD[j][0] > G.distance[id[i]][j]) {
                tempD[j][1] = tempD[j][0];
                tempF[j][1] = tempF[j][0];
                tempD[j][0] = G.distance[id[i]][j];
                tempF[j][0] = id[i];
            } else if (tempD[j][1] > G.distance[id[i]][j]) {
                tempD[j][1] = G.distance[id[i]][j];
                tempF[j][1] = id[i];
            }
        }
        vector <float> Mf(numPcenter, 0);

        for (int t = 0; t != pcenter.size(); t++) {//寻找加入节点id[i]后删除中心节点pcenter[t]得到的最长服务边
            for (int j = 0; j != numNode; j++) {
                if (tempF[j][0] == pcenter[t] && Mf[t] < tempD[j][1]) {//&& Mf[t] < tempD[j][1]) {
                    Mf[t] = tempD[j][1];
                }
            }
        }
        tempPair1.nodeid = id[i];
        tempScinfo[i].Sc = Mf[0];
        tempPair1.centerid = pcenter[0];
        tempPair1.delt = ScInfo.Sc - tempScinfo[i].Sc;
        for (int t = 1; t != pcenter.size(); t++) {
            if (tempScinfo[i].Sc > Mf[t]) {
                tempScinfo[i].Sc = Mf[t];
                tempPair1.centerid = pcenter[t];
                tempPair1.delt = ScInfo.Sc - tempScinfo[i].Sc;
                //tempScinfo[i].Scid = pcenter[t];
            } else if (tempScinfo[i].Sc == Mf[t]) {
                if (rand() % 2 == 0) {//相等时，随机选择
                    tempScinfo[i].Sc = Mf[t];
                    tempPair1.centerid = pcenter[t];
                    tempPair1.delt = ScInfo.Sc - tempScinfo[i].Sc;

                }
            }

        }
        tempPair.push_back(tempPair1);
    }
    for (int i = 0; i != id.size(); i++) {
       // cout << endl<<"add node "<<id[i]<<" and remove center "<<tempPair[i].centerid<< ", the delt: "<<tempPair[i].delt << ",";
        if (tempPair[i].delt > 0.01) {
            flag = 1;
        }
    }//cout << endl;
    for (int i = 0; i != id.size(); i++) {
        if (TabuTenure[tempPair[i].centerid][tempPair[i].nodeid] < iter) {//update the no_tabu best move,有错误;
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
    if ((tabu_pair.delt > no_tabu_pair.delt) && (tabu_pair.delt > 0)) //解禁条件：禁忌解优于当前查找的非禁忌解中最好的且优于历史最优解
    {
        Pair = tabu_pair;
    } else
        Pair = no_tabu_pair;


}


void Tabu::add_facility(Graph &G, pair &Pair) {
    for (int i = 0; i != numNode; i++) {
        if (D[i][0] > G.distance[Pair.nodeid][i]) {
            D[i][1] = D[i][0];
            F[i][1] = F[i][0];
            D[i][0] = G.distance[Pair.nodeid][i];
            F[i][0] = Pair.nodeid;

        } else if (pcenter.size() > 1 && D[i][1] > G.distance[Pair.nodeid][i]) {
            D[i][1] = G.distance[Pair.nodeid][i];
            F[i][1] = Pair.nodeid;
        }

    }
   // pcenter.push_back(Pair.nodeid);
    //pcenter[numPcenter + 1] = f;
}

#if 0
int Tabu::findremove_facility(vector <Nodes> &Node, int f) {//前p个服务点中找到一个删除后产生的最大服务边最小的点删(禁忌策略找交换对<f,i>）
    vector <int> Mf(numPcenter, 0);
    float tempSc = 0;
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
    int tempPlace = 0;
    for (int j = 0; j != pcenter.size(); j++) {
        if (pcenter[j] == Pair.centerid) {
            //tempPlace = j;
            pcenter[j] = Pair.nodeid;
        }
    }
    //int f = pcenter[tempPlace];
    cout << endl;
    for (int i = 0; i != numNode; i++) {
        if (F[i][0] == Pair.centerid) {
            D[i][0] = D[i][1];
            F[i][0] = F[i][1];
            int nextp = find_next(G, i);
           // cout  << "nextp1:" << nextp;
            D[i][1] = G.distance[nextp][i];
            F[i][1] = nextp;

        } else if (pcenter.size() > 1 && F[i][1] == Pair.centerid) {
            int nextp = find_next(G, i);
            //if (nextp == -1) {
            //    flag = 0;
            //    //pcenter[j] = Pair.centerid;
            //    break;
            //}
            //cout << "nextp2:" << nextp;
            D[i][1] = G.distance[nextp][i];
            F[i][1] = nextp;
        }
    }
    /*cout << "F,D:" << endl;

    for (int j = 0; j != numNode; j++) {
        for (int i = 0; i != 2; i++) {
            cout << F[j][i] << "," << D[j][i] << ";";
        }
        cout << endl;
    }*/

    //pcenter[numPcenter + 1] = -1;
}
/*Mf为删除节点f后产生的最长服务边距离（不是当前历史最长距离），
对比所有服务边删除后产生的Mf，选择最小的删除其对应的点,
利用F和D表计算
*/


int Tabu::find_next(Graph &G, int v) {
    float tempsecondmax = max;
    int tempsecondmaxP = -1;
    for (int j = 0; j != numPcenter; j++) {
        if (pcenter[j] != F[v][0] && tempsecondmax > G.distance[pcenter[j]][v]) {
            tempsecondmax = G.distance[pcenter[j]][v];
            tempsecondmaxP = pcenter[j];
        }
        else if (pcenter[j] != F[v][0] && tempsecondmax == G.distance[pcenter[j]][v]) {
            if (rand() % 2 == 0) {
                tempsecondmax = G.distance[pcenter[j]][v];
                tempsecondmaxP = pcenter[j];
            }
        }
    }

    return tempsecondmaxP;
}


void Tabu::change_pair(Graph &G, pair &Pair) {
    //更新tabu表
    TabuTenure[Pair.centerid][Pair.nodeid] = TabuTenure[Pair.nodeid][Pair.centerid] = RECENCY + iter;

    add_facility(G, Pair);//添加Pair.nodeid服务点
   // int i=findremove_facility(Node,f);
    remove_facility(G, Pair);//删除Pair.centerid服务点
}

Tabu::~Tabu() {

}
