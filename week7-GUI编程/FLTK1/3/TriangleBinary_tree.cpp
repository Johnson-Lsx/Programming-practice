#include "TriangleBinary_tree.h"


void TriangleBinary_tree::drawNodes(Simple_window& win)
{
	vector<Point> a = ret();
	Lines L1;
	for (int i = 0; i < a.size(); ++i)//默认的三角形，不提供用户更改三角形的接口
	{
		L1.add(Point(a[i].x - 5, a[i].y - 5), Point(a[i].x + 5, a[i].y - 5));
		L1.add(Point(a[i].x - 5, a[i].y - 5), Point(a[i].x, a[i].y + 5));
		L1.add(Point(a[i].x + 5, a[i].y - 5), Point(a[i].x, a[i].y + 5));
	}
	L1.draw_lines();
	L1.set_color(Graph_lib::Color(1));
	win.attach(L1);
	Binary_tree::drawTrees(win);
}
