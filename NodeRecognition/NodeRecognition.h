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
	int parts;//��¼��ͨ��������
	int nodes, btrees, trees, graphs;
	int cnt;//��¼���鼯��Ԫ�ظ���
	vector<int> DJS;//�洢���鼯Ԫ�ص�����
	vector<vector<int>> set;
	string input;//�洢������ַ���
	vector<int> weight;//��¼ÿ���ڵ��Ȩ��
	unordered_map<int, int> wiPair;//��¼Ȩ�����Ӧ��id
	vector<int> child;//��¼���ӹ�ϵ
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
	void Input(string str);//��������
	void getDJS();//��ò��鼯
	void getAns();
	void Output();
};
