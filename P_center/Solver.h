#ifndef PCENTER_SOLVER_H
#define PCENTER_SOLVER_H 
#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include "Graph.h"
#define MAX_ITER 1000
#define count 2
#define RECENCY 10
//#define numPcenter 10
#define MAX 10000
#pragma once

using namespace std;
 class Tabu
{
	float best_solution;//Ŀ�꺯��ֵ����������
    int flag;
    int numNode;
    int numPcenter;
	//int **Table;//���ɱ�
    vector <vector<int>> TabuTenure;
    vector<int> pcenter;
   // int Mf;
	//int **PtoNode;
	vector <vector <int>> PtoNode;
	vector <vector <int>> F;
	vector <vector <float>> D;
    //vector <vector<float>> adjDic;
   // vector <vector <float>> distance;
    struct pair {
        int nodeid;
        int centerid;
        float delt;
    };
    struct Scinfo{
        int Scid;
        float Sc;
    };
   // vector <int> Mf;
    
public:
    struct Scpoint {
        int Nodep;
        int Noden;
    };
    Scpoint ScPoint;
	Tabu();
	Tabu(Graph &G,int numN,int numP);
	int findP(Graph &G,Scinfo &ScInfo);//�ҵ���Զ����߶�Ӧ�������С����Զ����ߵĵ㣬���Ѱ����һ��P��
	void init(Graph &G,Scinfo &ScInfo);//��ʼ��
	void initfuncation(Graph &G, Scinfo &ScInfo);//��ʼĿ�꺯��ֵ
	void initDandFtable(Graph &G,int tempP);
	//void initFtable(vector <Nodes> &Node);
    void tabusearch(Graph &G);
    int findadd_facility(Graph &G);
    void find_pair(Graph &G,Scinfo &ScInfo,pair &Pair);
	void add_facility(Graph &G,pair &Pair);//���������f������F���D��
    int findremove_facility(Graph &G,int f);
	void remove_facility(Graph &G,pair &Pair);//ɾ�������f������F���D��
	int fine_move(Graph &G);//Ѱ�������ڵ�i������ʵ�֣�
	void change_pair(Graph &G,pair &Pair);//�Ƚ�Ŀ�꺯��ֵSc�������ڵ������ľ���Mf��ȡ���ߡ�
    int find_next(Graph &G, int v);
	~Tabu();
};

#endif //PCENTER_SOLVER_H 