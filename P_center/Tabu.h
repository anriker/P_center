#ifndef PCENTER_TABU_H
#define PCENTER_TABU_H 
#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include "Graph.h"
#define count 2
#define numPcenter 10
#define max 1000
#pragma once

using namespace std;
 class Tabu
{
	double Sc;//Ŀ�꺯��ֵ����������

	//int **Table;//���ɱ�
    vector <vector<int>> TabuTenure;
	int numNode;
   // int Mf;
	//int **PtoNode;
	vector <vector <int>> PtoNode;
	vector <vector <int>> F;
	vector <vector <double>> D;
    vector <vector<double>> adjDic;
    vector <vector <double>> distance;
    struct pair {
        int nodeid;
        int centerid;
        int delt;
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
	Tabu(vector <Nodes> &Node);
    void compDic(vector <Nodes> &Node, int &numNode);
	int findP(vector <Nodes> &Node,Scinfo &ScInfo);//�ҵ���Զ����߶�Ӧ�������С����Զ����ߵĵ㣬���Ѱ����һ��P��
	void init(vector <Nodes> &Node,Scinfo &ScInfo);//��ʼ��
	void updatePtoNode(vector <Nodes> &Node,int nextP);//���·����ͱ�����ڵ�Ĺ�ϵ
	void initfuncation(vector <Nodes> &Node, vector <int> pCenter,Scinfo &ScInfo);//��ʼĿ�꺯��ֵ
	void initDandFtable(vector <Nodes> &Node,int tempP);
	//void initFtable(vector <Nodes> &Node);
    void tabusearch(vector <Nodes> &Node);
    int findadd_facility(vector <Nodes> &Node);
    void find_pair(vector <Nodes> &Node,Scinfo &ScInfo,pair &Pair);
	void add_facility(vector <Nodes> &Node,pair &Pair);//���������f������F���D��
    int findremove_facility(vector <Nodes> &Node,int f);
	void remove_facility(vector <Nodes> &Node,pair &Pair);//ɾ�������f������F���D��
	int fine_move(vector <Nodes> &Node);//Ѱ�������ڵ�i������ʵ�֣�
	void change_pair(vector <Nodes> &Node,pair &Pair);//�Ƚ�Ŀ�꺯��ֵSc�������ڵ������ľ���Mf��ȡ���ߡ�
    int find_next(vector <Nodes> &Node, int v,int fplace);
	~Tabu();
};

#endif