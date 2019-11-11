#pragma once
#include"Graph.h"
#include"Point.h"
class Binary_tree :public Graph_lib::Shape
{
	friend class Simple_window;
private:
	int levels;
	double r;
	double dh;
	Graph_lib::Lines L;
	vector<Point> centers;
	vector<Point> cent;
public:
	Binary_tree(int n) :levels(n) { r = 5; dh = 25; }
	double retr() { return r; }
	void set_r(double nr) { r = nr; }
	void set_dh(double ndh) { dh = ndh; }
	vector<Point> ret() { return centers; }
	vector<Point> ret1() { return cent; }
	virtual void getCenters(double left, double right, double h, int n);
	virtual void getCenters(double w, double h, int n);
	virtual void drawTrees(Simple_window& win);
	virtual void drawNodes(Simple_window& win);
	~Binary_tree() {}
	void draw()
	{
		
	}
};
class Circles :public Graph_lib::Circle
{
private:
	int nums;
	vector<double> rs;
public:
	Circles(Point p = Point(0, 0), int r = 0) :Circle(p, r) { nums = 0; }
	void add(Point p, double rr);
	void draw_lines() const;
};