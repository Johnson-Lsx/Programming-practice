#include "Binary_tree.h"
#include "Simple_window.h"
#include"std_lib_facilities.h"
void Binary_tree::getCenters(double left, double right, double h, int n)
{
	if (n == 1)
	{
		centers.push_back(Point((left + right) / 2, h + r));
		return;
	}
	else
	{
		centers.push_back(Point((left + right) / 2, h + r));
		L.add(Point((left + right) / 2, h + r), Point((left + (left + right) / 2) / 2, h + 2 * r + dh));//将父子节点相连接
		L.add(Point((left + right) / 2, h + r), Point(((left + right) / 2 + right) / 2, h + 2 * r + dh));//将父子节点相连接
		getCenters(left, (left + right) / 2, h + 2 * r + dh, n - 1);
		getCenters((left + right) / 2, right, h + 2 * r + dh, n - 1);
	}
}

void Binary_tree::getCenters(double w, double h, int n)//迭代得到圆心，在此实现中可去掉
{
	for (int i = 1; i < levels + 1; ++i)
	{
		for (int j = 1; j < pow(2, i - 1) + 1; ++j)
		{
			double x1 = i;
			double x2 = j;
			double xx = ((2 * x2 - 1) / pow(2,x1) * w);
			double yy = 2 * (x1 - 1) * r + r + (x1 - 1) * dh;
			cent.push_back(Point(int(xx), int(yy)));
		}
	}
}

void Binary_tree::drawTrees(Simple_window& win)
{
	L.draw_lines();
	L.set_color(Graph_lib::Color(1));
	win.attach(L);
	win.wait_for_button();
}

void Binary_tree::drawNodes(Simple_window& win)
{
	vector<Point> a = ret();
	Circles cs;
	for (int i = 0; i < a.size(); ++i)
	{
		cs.add(a[i], retr());
	}
	cs.draw_lines();
	cs.set_color(Graph_lib::Color(1));
	L.draw_lines();
	L.set_color(Graph_lib::Color(1));
	win.attach(cs);
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
			fl_arc(point(i).x, point(i).y, rs[i - 1] + rs[i - 1], rs[i - 1] + rs[i - 1], 0, 360);//使用了FLTK函数
	}
}
