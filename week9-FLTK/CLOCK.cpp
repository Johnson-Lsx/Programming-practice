#include"Graph.h"
#include"GUI.h"
#include"Point.h"
#include"std_lib_facilities.h"
#include<ctime>
#include<cmath>
using namespace Graph_lib;

class AnalogClock:public Graph_lib::Shape
{
private:
	int len = 10;//刻度的长度
	int mz, fz, sz;//时分秒针长度
	double r;//表盘半径
	int YY, MM, DD;//年月日
	int hh, mm, ss;//时分秒
	Point o;//表盘圆心
	Circle dialPlate;//表盘
	Lines notches;//刻度
	Lines pins;//表针
	vector<Point> ts;//数字
	void getTime();
public:
	AnalogClock(Point p, double rr,double lens,double lenf,double lenm);
	void draw_lines();
	vector<Point> retP() { return ts; }
	string retData() { return (to_string(YY) + '/' + to_string(MM) + '/' + to_string(DD)); }
};

#define _CRT_SECURE_NO_WARNINGS
#include "AnalogClock.h"
#include<iostream>

void AnalogClock::getTime()
{
	time_t t = time(NULL);
	struct tm* localt = localtime(&t);
	YY = localt->tm_year + 1900;
	MM = localt->tm_mon + 1;
	DD = localt->tm_mday;
	string Data = to_string(YY) + '/' + to_string(MM) + '/' + to_string(DD);
	hh = localt->tm_hour;
	mm = localt->tm_min;
	ss = localt->tm_sec;
	double totalSec;
	totalSec = double(hh * 3600) + double(mm * 60) + double(ss);
	double s, f, m;
	m = (totalSec * 6) / 180 * 3.14;
	f = (totalSec * 0.1) / 180 * 3.14;
	s = (totalSec / 120) / 180 * 3.14;
	double x1, x2, x3, y1, y2, y3;
	x1 = o.x + (mz) * sin(m);
	y1 = o.y - (mz) * cos(m);
	x2 = o.x + (fz) * sin(f);
	y2 = o.y - (fz) * cos(f);
	x3 = o.x + (sz) * sin(s);
	y3 = o.y - (sz) * cos(s);
	pins.add(o, Point(x1, y1));
	pins.add(o, Point(x2, y2));
	pins.add(o, Point(x3, y3));
	if (number_of_points() == 0)
	{
		add(o);
		add(Point(x1, y1));
		add(o);
		add(Point(x2, y2));
		add(o);
		add(Point(x3, y3));
	}
	else
	{
		Graph_lib::Shape::set_point(1, Point(x1, y1));
		Graph_lib::Shape::set_point(3, Point(x2, y2));
		Graph_lib::Shape::set_point(5, Point(x3, y3));
	}
}

AnalogClock::AnalogClock(Point p, double rr, double lens, double lenf, double lenm)
:dialPlate(Point(p.x - r, p.y - r), rr)
{
	r = rr;
	o = p;
	mz = lenm;
	fz = lenf;
	sz = lens;
	for (int i = 0; i < 12; ++i)
	{
		double j = i;
		double x1 = o.x + r * sin((j * 30 / 180) * 3.14);
		double x2 = o.x +(r - len) * sin((j * 30 / 180) * 3.14);
		double y1 = o.y - r * cos((j * 30 / 180) * 3.14);
		double y2 = o.y - (r - len) * cos((j * 30 / 180) * 3.14);
		notches.add(Point(x1, y1), Point(x2, y2));
		ts.push_back(Point(x2, y2));
	}
}

void AnalogClock::draw_lines()
{
	dialPlate.draw_lines();
	notches.draw_lines();
	getTime();
	//pins.draw_lines();
	if (color().visibility())
		for (int i = 1; i < number_of_points(); i += 2)
			fl_line(point(i - 1).x, point(i - 1).y, point(i).x, point(i).y);
	if (color().visibility())
		for (int i = 0; i < number_of_points(); ++i)
		{
			string lab = to_string(i + 1);
			fl_draw(lab.c_str(), point(0).x, point(0).y);
		}
}

#define _CRT_SECURE_NO_WARNINGS
#include"AnalogClock.h"
#include"BarChart.h"
#include"Binary_tree.h"
#include"TriangleBinary_tree.h"
#include"hyperelliptic.h"
#include"righttriangle.h"
#include"std_lib_facilities.h"
#include"Simple_window.h"
#include"Graph.h"
#include"GUI.h"
#include<iostream>
#include<conio.h>
using namespace Graph_lib;
using namespace std;

int main()
{
	void ex1();
	void ex2();
	void ex3();
	void ex4();
	void ex5();
	Simple_window win(Point(100, 100), 1000, 800, "hyperelliptic");
	AnalogClock c(Point(300, 300), 200,80,130,180);
	while (!_kbhit())
	{
		c.draw_lines();
		win.attach(c);
		Sleep(1);
	}
	win.wait_for_button();
	return 0;
}
void ex1()
{
	Simple_window win(Point(100, 100), 1000, 800, "hyperelliptic");
	double a, b, m, n;
	int N;
	cin >> a >> b >> m >> n;
	cin >> N;
	hyperelliptic h(a, b, m, n, N);
	h.draw();
	win.attach(h);
	win.wait_for_button();
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
void ex3()
{
	Simple_window win(Point(100, 100), 1000, 800, "Binary_tree");
	int n;
	cin >> n;
	Binary_tree b(n);
	b.getCenters(0, win.x_max(), 0, n);
	b.drawNodes(win);
}
void ex4()
{
	Simple_window win(Point(100, 100), 1000, 800, "TriangleBinary_tree");
	int n;
	cin >> n;
	TriangleBinary_tree tt(n);
	tt.getCenters(0, win.x_max(), 0, n);
	tt.drawNodes(win);
}
void ex5()
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
	X.set_color(Graph_lib::Color(8));
	Y.set_color(Graph_lib::Color(8));
	chart1.set_color(Graph_lib::Color::red);
	chart2.set_color(Graph_lib::Color::blue);
	t1.set_color(Graph_lib::Color::red);
	t2.set_color(Graph_lib::Color::blue);
	X.draw_lines();
	Y.draw_lines();
	chart1.draw_lines();
	chart2.draw_lines();
	t1.draw_lines();
	t2.draw_lines();
	win.attach(X);
	win.attach(Y);
	win.attach(chart1);
	win.attach(chart2);
	win.attach(t1);
	win.attach(t2);
	win.redraw();
	win.wait_for_button();
}