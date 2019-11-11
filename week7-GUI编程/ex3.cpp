#pragma once
#include"Graph.h"
#include"Point.h"
class Binary_tree:public Graph_lib::Shape
{
	friend class Simple_window;
private:
	int levels;
	double r;
	double dh;
	Graph_lib::Lines L;
	//vector<Graph_lib::Line> Ls;
	vector<Point> centers;
	vector<Point> cent;
public:
	Binary_tree(int n) :levels(n) { r = 5; dh = 25; }
	double retr() { return r; }
	void set_r(double nr) { r = nr;}
	void set_dh(double ndh) { dh = ndh; }
	//vector<Graph_lib::Line> retL() {return Ls;}
	vector<Point> ret() { return centers; }
	vector<Point> ret1() { return cent; }
	virtual void getCenters(double left,double right, double h, int n);
	virtual void getCenters(double w, double h, int n);
	virtual void Draw(Simple_window& win);
	~Binary_tree(){}
};
class Circles :public Graph_lib::Circle
{
private:
	int nums;
	vector<double> rs;
public:
	Circles(Point p = Point(0,0), int r = 0):Circle(p,r) { nums = 0; }
	void add(Point p, double rr);
	void draw_lines() const;
};
#include "Binary_tree.h"
#include "Simple_window.h"
#include"std_lib_facilities.h"
void Binary_tree::getCenters(double left,double right, double h, int n)
{
	if (n == 1)
	{
		centers.push_back(Point((left + right) / 2, h + r));
		return;
	}
	else
	{
		centers.push_back(Point((left + right) / 2, h + r));
		L.add(Point((left + right) / 2, h + r),Point((left+(left + right) / 2)/2, h + 2 * r + dh));
		L.add(Point((left + right) / 2, h + r),Point(((left + right) / 2+ right)/2, h + 2 * r + dh));
		//Ls.push_back(Graph_lib::Line(Point((left + right) / 2, h + r), Point((left + (left + right) / 2) / 2, h + 2 * r + dh)));
		//Ls.push_back(Graph_lib::Line(Point((left + right) / 2, h + r), Point(((left + right) / 2 + right) / 2, h + 2 * r + dh)));
		getCenters(left, (left + right) / 2,h + 2 * r + dh, n - 1);
		getCenters((left + right) / 2,right, h + 2 * r + dh, n - 1);
	}
}

void Binary_tree::getCenters(double w, double h, int n)
{
	for (int i = 1; i < levels + 1; ++i)
	{
		for (int j = 1; j < pow(2, i - 1) + 1; ++j)
		{
			double x1 = i;
			double x2 = j;
			double xx = ((2 * x2 - 1) / (2 * x1) * w);
			double yy = 2 * (x1 - 1) * r + r + (x1 - 1) * dh;
			cent.push_back(Point(int(xx), int(yy)));
		}
	}
}

void Binary_tree::Draw(Simple_window& win)
{
	L.draw_lines();
	L.set_color(Graph_lib::Color(1));
	win.attach(L);
	win.wait_for_button();
}

void Circles::add(Point p, double rr)
{
	rs.push_back(rr);
	Shape::add(Point(p.x - rr, p.y - rr));
}

void Circles::draw_lines() const
{
	for (int i = 1; i < number_of_points(); ++i)
	{
		if (color().visibility())
			fl_arc(point(i).x, point(i).y, rs[i-1] + rs[i-1], rs[i-1] + rs[i-1], 0, 360);
	}
}
