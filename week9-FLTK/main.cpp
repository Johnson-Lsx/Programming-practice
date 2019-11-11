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
	/*while (!_kbhit())
	{
		time_t t = time(NULL);
		struct tm* localt = localtime(&t);
		system("cls");
		cout << '\n' << "\t\t";
		cout << localt->tm_year + 1900 << '\\';
		cout << localt->tm_mon + 1 << '\\';
		cout << localt->tm_mday << '\t';
		cout << localt->tm_hour << ':',
		cout << localt->tm_min << ':',
		cout << localt->tm_sec;
		Sleep(1);
	}*/
	/*
	string DT = to_string(YY) + '/' + to_string(MM) + '/' 
	+ to_string(DD) + "    " + to_string(hh) + ":" + to_string(mm) + ":" + to_string(ss);
	dateT.put(DT);
	*/
	Simple_window win(Point(100, 100), 1000, 800, "hyperelliptic");
	//AnalogClock c(Point(300, 300), 200);
	//c.draw_lines();
	Point o(300, 300);
	double r = 200;
	Texts texts;
	Circle dialPlate(o,r);//表盘
	Lines notches;//刻度
	vector<Point> ts;//数字
	int len = 10;//刻度的长度
	for (int i = 0; i < 12; ++i)
	{
		double j = i;
		double x1 = o.x + r * sin((j * 30 / 180) * 3.14);
		double x2 = o.x + (r - len) * sin((j * 30 / 180) * 3.14);
		double y1 = o.y - r * cos((j * 30 / 180) * 3.14);
		double y2 = o.y - (r - len) * cos((j * 30 / 180) * 3.14);
		notches.add(Point(x1, y1), Point(x2, y2));
		ts.push_back(Point(x2, y2));
	}
	for (int i = 0; i < ts.size(); ++i)
	{
		texts.add(ts[i], to_string(i + 1));
	}
	win.redraw();
	dialPlate.draw_lines();
	notches.draw_lines();
	texts.draw_lines();
	//vector<Point> ts = c.retP();
	/*Text t1(ts[0], "12");
	t1.draw_lines();
	t1.set_color(Graph_lib::Color::black);
	Text t2(ts[1], "1");
	t2.draw_lines();
	t2.set_color(Graph_lib::Color::black);
	Text t3(ts[2], "2");
	t3.draw_lines();
	t3.set_color(Graph_lib::Color::black);
	Text t4(ts[3], "3");
	t4.draw_lines();
	t4.set_color(Graph_lib::Color::black);
	Text t5(ts[4], "4");
	t5.draw_lines();
	t5.set_color(Graph_lib::Color::black);
	Text t6(ts[5], "5");
	t6.draw_lines();
	t6.set_color(Graph_lib::Color::black);
	Text t7(ts[6], "6");
	t7.draw_lines();
	t7.set_color(Graph_lib::Color::black);
	Text t8(ts[7], "7");
	t8.draw_lines();
	t8.set_color(Graph_lib::Color::black);
	Text t9(ts[8], "8");
	t9.draw_lines();
	t9.set_color(Graph_lib::Color::black);
	Text t10(ts[9], "9");
	t10.draw_lines();
	t10.set_color(Graph_lib::Color::black);
	Text t11(ts[10], "10");
	t11.draw_lines();
	t11.set_color(Graph_lib::Color::black);
	Text t12(ts[11], "11");
	t12.draw_lines();
	t12.set_color(Graph_lib::Color::black);*/
	//c.draw_lines();
	//win.attach(c);
	/*win.attach(t1);
	win.attach(t2);
	win.attach(t3);
	win.attach(t4);
	win.attach(t5);
	win.attach(t6);
	win.attach(t7);
	win.attach(t8);
	win.attach(t9);
	win.attach(t10);
	win.attach(t11);
	win.attach(t12);*/
	win.attach(dialPlate);
	win.attach(notches);
	win.attach(texts);
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


class Texts :public Shape
{
private:
	vector<string> labs;
public:
	void add(Point p,const string& str)
	{
		labs.push_back(str);
		Shape::add(p);
	}
	void draw_lines()
	{
		for (int i = 0; i < number_of_points(); ++i)
		{
			int ofnt = fl_font();
			int osz = fl_size();
			fl_draw(labs[i].c_str(), point(i).x, point(i).y);
			fl_font(ofnt, osz);
		}
	}
};