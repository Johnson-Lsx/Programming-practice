#include"righttriangle.h"
#include"std_lib_facilities.h"
#include"Simple_window.h"
#include"Graph.h"
#include<iostream>
using namespace Graph_lib;
using namespace std;
int main()
{
	void ex2();
	ex2();
	return 0;
}
void ex2()
{
	Simple_window win(Point(100, 100), 1000, 800, "righttriangle");
	righttriangle rt1(Point(100, 100), 100, 100, 90);
	righttriangle rt2(Point(100 + 50 * sqrt(2), 50 * sqrt(2)), 100, 100, 45);
	righttriangle rt3(Point(100 + 100 * sqrt(2), 100), 100, 100, 0);
	righttriangle rt4(Point(50 * sqrt(2), 100 + 50 * sqrt(2)), 100, 100, 135);
	righttriangle rt5(Point(100, 100 + 100 * sqrt(2)), 100, 100, 180);
	righttriangle rt6(Point(100 + 50 * sqrt(2), 200 + 50 * sqrt(2)), 100, 100, 225);
	righttriangle rt7(Point(100 + 100 * sqrt(2), 100 + 100 * sqrt(2)), 100, 100, 270);
	righttriangle rt8(Point(200 + 50 * sqrt(2), 100 + 50 * sqrt(2)), 100, 100, 315);
	rt1.draw();
	rt1.set_color(Color(1));
	rt2.draw();
	rt2.set_color(Color(2));
	rt3.draw();
	rt3.set_color(Color(3));
	rt4.draw();
	rt4.set_color(Color(4));
	rt5.draw();
	rt5.set_color(Color(5));
	rt6.draw();
	rt6.set_color(Color(6));
	rt7.draw();
	rt7.set_color(Color(7));
	rt8.draw();
	rt8.set_color(Color(8));
	win.attach(rt1);
	win.attach(rt2);
	win.attach(rt3);
	win.attach(rt4);
	win.attach(rt5);
	win.attach(rt6);
	win.attach(rt7);
	win.attach(rt8);
	win.wait_for_button();
}