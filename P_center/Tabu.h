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
	int Sc;//目标函数值，即最大距离
	int **Table;//禁忌表
	int numNode;

	//int **PtoNode;
	vector <vector <int>> PtoNode;
	vector <vector <int>> F;
	vector <vector <int>> D;
	
public:
	Tabu();
	Tabu(vector <Nodes> &Node);
	int findP(vector <Nodes> &Node,int longestN);//找到最远服务边对应点的其他小于最远服务边的点，随机寻找下一个P点
	void init(vector <Nodes> &Node);//初始解
	void updatePtoNode(vector <Nodes> &Node,int nextP);//更新服务点和被服务节点的关系
	int funcation(vector <Nodes> &Node,int *p);//初始目标函数值
	void initDtable(vector <Nodes> &Node);
	void initPtable(vector <Nodes> &Node);
	void add_facility(vector <Nodes> &Node);//新增服务点f，更新F表和D表
	void delete_facility(vector <Nodes> &Node);//删除服务点f，更新F表和D表
	int fine_move(vector <Nodes> &Node);//寻找新增节点i，禁忌实现？
	void find_pair(vector <Nodes> &Node);//比较目标函数值Sc和新增节点后产生的距离Mf，取大者。
	~Tabu();
};

#endif