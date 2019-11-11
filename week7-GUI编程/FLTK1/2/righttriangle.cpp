#include "righttriangle.h"
#include<cmath>
void righttriangle::draw()
{
	double x1, y1, x2, y2;//(x1,y1),(x2,y2)是另外两个顶点的坐标
	x1 = p.x + a * cos(degree / 180 * 3.14);
	y1 = p.y - a * sin(degree / 180 * 3.14);
	x2 = p.x - b * sin(degree / 180 * 3.14);
	y2 = p.y - b * cos(degree / 180 * 3.14);
	add(p);
	add(Point(x1, y1));
	add(Point(x2, y2));
	Graph_lib::Closed_polyline::draw_lines();
}
