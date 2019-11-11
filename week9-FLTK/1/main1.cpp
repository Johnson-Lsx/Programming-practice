#include"BarChart.h"
#include"std_lib_facilities.h"
#include"Simple_window.h"
#include"Graph.h"
#include<iostream>
using namespace Graph_lib;
using namespace std;

int main()
{
	Simple_window win(Point(100, 100), 1000, 800, "temperature");
	Axis X(Axis::x, Point(50, 600), 600, 12, "1           2          3          4          5          6"
		"           7          8          9          10        11        12        month");
	X.label.move(-130, 0);
	Axis Y(Axis::y, Point(50, 600), 340, 17, "temperature  one notch = 2Celsius degree");
	const double yScale = 320 / 32;
	ifstream fin1("Austin.csv");
	ifstream fin2("NewYork.csv");
	BarChart chart1(fin1, 24, 51, 26, 600, yScale);
	BarChart chart2(fin2, 24, 76, 26, 600, yScale);
	Text t1(Point(500, 200), "red color represents Austin");
	Text t2(Point(500, 250), "blue color represents NewYork");
	Text t3(Point(25, 610), "0");
	Text t4(Point(25, 270), "34");
	X.set_color(Graph_lib::Color(8));
	Y.set_color(Graph_lib::Color(8));
	chart1.set_color(Graph_lib::Color::red);
	chart2.set_color(Graph_lib::Color::blue);
	t1.set_color(Graph_lib::Color::red);
	t2.set_color(Graph_lib::Color::blue);
	t3.set_color(Color::black);
	t4.set_color(Color::black);
	X.draw_lines();
	Y.draw_lines();
	chart1.draw_lines();
	chart2.draw_lines();
	t1.draw_lines();
	t2.draw_lines();
	t3.draw_lines();
	t4.draw_lines();
	win.attach(X);
	win.attach(Y);
	win.attach(chart1);
	win.attach(chart2);
	win.attach(t1);
	win.attach(t2);
	win.attach(t3);
	win.attach(t4);
	win.redraw();
	win.wait_for_button();
	return 0;
}