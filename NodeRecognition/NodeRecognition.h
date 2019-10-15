#pragma once
#include "std_lib_facilities.h"
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<unordered_map>
class NodeRecognition
{
private:
	struct part
	{
		int n;
		int w;
		int s;
	};
	vector<part> ret;
	int parts;//记录连通分量个数
	int nodes, btrees, trees, graphs;
	int cnt;//记录并查集中元素个数
	vector<int> DJS;//存储并查集元素的数组
	vector<vector<int>> set;
	string input;//存储输入的字符串
	vector<int> weight;//记录每个节点的权重
	unordered_map<int, int> wiPair;//记录权重与对应的id
	vector<int> child;//记录父子关系
	vector<int> father;
	int Find(int x);
	void Union(int root1, int root2);
	bool isBinaryTree(int i);
	bool isTree(int i);
	bool isNode(int i);
	void Swap(part& a, part& b);
	void Sort();
	void findRoot();
public:
	void Input(string str);//处理输入
	void getDJS();//获得并查集
	void getAns();
	void Output();
};
