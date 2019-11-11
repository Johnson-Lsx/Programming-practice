#pragma once
#include"Graph.h"
#include"Point.h"
class righttriangle:public Graph_lib::Closed_polyline
{
private:
	Point p;
	double a, b;
	double degree;//边长为a的直角边与x轴正方向的夹角，单位：°
public:
	righttriangle(Point pp,double aa,double bb,double deg = 0):p(pp),a(aa),b(bb),degree(deg){}
	void draw();
};

