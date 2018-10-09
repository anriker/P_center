#ifndef PCENTER_TABU_Z
#define PCENTER_TABU_Z 
#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include "dataForm.h"
#define count 2
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
	
public:
	Tabu();
	Tabu(vector <Nodes> &Node);
	int findP(vector <Nodes> &Node,int longestN);//�ҵ���Զ����߶�Ӧ�������С����Զ����ߵĵ㣬���Ѱ����һ��P��
	void init(vector <Nodes> &Node);//��ʼ��
	void updatePtoNode(vector <Nodes> &Node,int nextP);//���·����ͱ�����ڵ�Ĺ�ϵ
	int funcation(vector <Nodes> &Node,int *p);//��ʼĿ�꺯��ֵ
	void initDtable(vector <Nodes> &Node);
	void initPtable(vector <Nodes> &Node);
	void add_facility(vector <Nodes> &Node);//���������f������F���D��
	void delete_facility(vector <Nodes> &Node);//ɾ�������f������F���D��
	int fine_move(vector <Nodes> &Node);//Ѱ�������ڵ�i������ʵ�֣�
	void find_pair(vector <Nodes> &Node);//�Ƚ�Ŀ�꺯��ֵSc�������ڵ������ľ���Mf��ȡ���ߡ�
	~Tabu();
};

#endif