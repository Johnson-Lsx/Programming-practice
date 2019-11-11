#pragma once
#include"Binary_tree.h"
#include"Simple_window.h"
#include"Point.h"
using namespace Graph_lib;

class TriangleBinary_tree:public Binary_tree
{
public:
	TriangleBinary_tree(int n) :Binary_tree(n) {}
	virtual void drawNodes(Simple_window& win);//将节点由圆形变为三角形
};

