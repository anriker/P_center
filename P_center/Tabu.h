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
	int Sc;//Ŀ�꺯��ֵ����������
	int **Table;//���ɱ�
	int numNode;

	//int **PtoNode;
	vector <vector <int>> PtoNode;
	vector <vector <int>> F;
	vector <vector <int>> D;
    vector <vector<int>> adjDic;
	
public:
	Tabu();
	Tabu(vector <Nodes> &Node);
	int findP(vector <Nodes> &Node,int longestN);//�ҵ���Զ����߶�Ӧ�������С����Զ����ߵĵ㣬���Ѱ����һ��P��
	void init(vector <Nodes> &Node);//��ʼ��
	void updatePtoNode(vector <Nodes> &Node,int nextP);//���·����ͱ�����ڵ�Ĺ�ϵ
	int initfuncation(vector <Nodes> &Node, vector <int> pCenter);//��ʼĿ�꺯��ֵ
	void initDandFtable(vector <Nodes> &Node);
	void initFtable(vector <Nodes> &Node);
    void tabusearch(vector <Nodes> &Node);
	void add_facility(vector <Nodes> &Node,int f);//���������f������F���D��
    int findremove_facility(vector <Nodes> &Node);
	void remove_facility(vector <Nodes> &Node);//ɾ�������f������F���D��
	int fine_move(vector <Nodes> &Node);//Ѱ�������ڵ�i������ʵ�֣�
	void find_pair(vector <Nodes> &Node,int f);//�Ƚ�Ŀ�꺯��ֵSc�������ڵ������ľ���Mf��ȡ���ߡ�
    int find_next(vector <Nodes> &Node, int v);
	~Tabu();
};

#endif