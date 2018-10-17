#ifndef PCENTER_SOLVER_H
#define PCENTER_SOLVER_H 
#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include "Graph.h"
#define count 2
//#define numPcenter 10
#define max 1000
#pragma once

using namespace std;
 class Tabu
{
	double Sc;//目标函数值，即最大距离
    int numNode;
    int numPcenter;
	//int **Table;//禁忌表
    vector <vector<int>> TabuTenure;
    vector<int> pcenter;
   // int Mf;
	//int **PtoNode;
	vector <vector <int>> PtoNode;
	vector <vector <int>> F;
	vector <vector <double>> D;
    //vector <vector<double>> adjDic;
   // vector <vector <double>> distance;
    struct pair {
        int nodeid;
        int centerid;
        double delt;
    };
    struct Scinfo{
        int Scid;
        double Sc;
    };
   // vector <int> Mf;
    
public:
    struct Scpoint {
        int Nodep;
        int Noden;
    };
    Scpoint ScPoint;
	Tabu();
	Tabu(Graph &G,int numP);
    void compDic(Graph &G, int &numNode);
	int findP(Graph &G,Scinfo &ScInfo);//找到最远服务边对应点的其他小于最远服务边的点，随机寻找下一个P点
	void init(Graph &G,Scinfo &ScInfo);//初始解
	void updatePtoNode(Graph &G,int nextP);//更新服务点和被服务节点的关系
	void initfuncation(Graph &G, vector <int> pCenter,Scinfo &ScInfo);//初始目标函数值
	void initDandFtable(Graph &G,int tempP);
	//void initFtable(vector <Nodes> &Node);
    void tabusearch(Graph &G);
    int findadd_facility(Graph &G);
    void find_pair(Graph &G,Scinfo &ScInfo,pair &Pair);
	void add_facility(Graph &G,pair &Pair);//新增服务点f，更新F表和D表
    int findremove_facility(Graph &G,int f);
	void remove_facility(Graph &G,pair &Pair);//删除服务点f，更新F表和D表
	int fine_move(Graph &G);//寻找新增节点i，禁忌实现？
	void change_pair(Graph &G,pair &Pair);//比较目标函数值Sc和新增节点后产生的距离Mf，取大者。
    int find_next(Graph &G, int v,int fplace);
	~Tabu();
};

#endif //PCENTER_SOLVER_H 