#pragma once
#include"Graph.h"
#include"Point.h"
class Binary_tree :public Graph_lib::Shape
{
	friend class Simple_window;
private:
	int levels;//记录二叉树的层数
	double r;//节点的半径
	double dh;//每一层与下一层之间的高度差
	Graph_lib::Lines L;//存储所有节点间的连线（树干）
	vector<Point> centers;//利用递归函数得到的节点圆心坐标存储在这里
	vector<Point> cent;//利用迭代法得到的节点圆心坐标存储再这里，在此实现中可去掉
public:
	Binary_tree(int n) :levels(n) { r = 5; dh = 25; }//构造函数，默认r = 5,dh = 25
	double retr() { return r; }//返回节点半径
	void set_r(double nr) { r = nr; }//改变节点半径
	void set_dh(double ndh) { dh = ndh; }//改变层与层之间的高度
	vector<Point> ret() { return centers; }//返回节点圆心坐标
	vector<Point> ret1() { return cent; }//返回节点圆心坐标
	virtual void getCenters(double left, double right, double h, int n);//递归得到圆心
	virtual void getCenters(double w, double h, int n);//迭代得到圆心，在此实现中可去掉
	virtual void drawTrees(Simple_window& win);//画树干
	virtual void drawNodes(Simple_window& win);//画节点
	~Binary_tree() {}
};
class Circles :public Graph_lib::Circle//该类是为了能将所有节点视为一个整体，类似于Line和Lines的关系
{
private:
	int nums;
	vector<double> rs;
public:
	Circles(Point p = Point(0, 0), int r = 0) :Circle(p, r) { nums = 0; }
	void add(Point p, double rr);
	void draw_lines() const;
};