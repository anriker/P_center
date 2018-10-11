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
	int Sc;//目标函数值，即最大距离
	int **Table;//禁忌表
	int numNode;

	//int **PtoNode;
	vector <vector <int>> PtoNode;
	vector <vector <int>> F;
	vector <vector <int>> D;
    vector <vector<int>> adjDic;
	
public:
	Tabu();
	Tabu(vector <Nodes> &Node);
	int findP(vector <Nodes> &Node,int longestN);//找到最远服务边对应点的其他小于最远服务边的点，随机寻找下一个P点
	void init(vector <Nodes> &Node);//初始解
	void updatePtoNode(vector <Nodes> &Node,int nextP);//更新服务点和被服务节点的关系
	int initfuncation(vector <Nodes> &Node, vector <int> pCenter);//初始目标函数值
	void initDandFtable(vector <Nodes> &Node);
	void initFtable(vector <Nodes> &Node);
    void tabusearch(vector <Nodes> &Node);
	void add_facility(vector <Nodes> &Node,int f);//新增服务点f，更新F表和D表
    int findremove_facility(vector <Nodes> &Node);
	void remove_facility(vector <Nodes> &Node);//删除服务点f，更新F表和D表
	int fine_move(vector <Nodes> &Node);//寻找新增节点i，禁忌实现？
	void find_pair(vector <Nodes> &Node,int f);//比较目标函数值Sc和新增节点后产生的距离Mf，取大者。
    int find_next(vector <Nodes> &Node, int v);
	~Tabu();
};

#endif