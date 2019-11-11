#define _CRT_SECURE_NO_WARNINGS
#include"AnalogClock.h"
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
	Simple_window win(Point(100, 100), 1000, 800, "AnalogClock");
	AnalogClock c(Point(500, 300), 200, 80, 130, 180);
	c.set_color(Color::black);
	c.dialPlate.set_color(Color::black);
	c.notches.set_color(Color::black);
	c.t1.set_color(Color::black);
	c.t2.set_color(Color::black);
	c.t3.set_color(Color::black);
	c.t4.set_color(Color::black);
	c.t5.set_color(Color::black);
	c.t6.set_color(Color::black);
	c.t7.set_color(Color::black);
	c.t8.set_color(Color::black);
	c.t9.set_color(Color::black);
	c.t10.set_color(Color::black);
	c.t11.set_color(Color::black);
	c.t12.set_color(Color::black);
	win.attach(c);
	win.attach(c.dialPlate);
	win.attach(c.notches);
	win.attach(c.t1);
	win.attach(c.t2);
	win.attach(c.t3);
	win.attach(c.t4);
	win.attach(c.t5);
	win.attach(c.t6);
	win.attach(c.t7);
	win.attach(c.t8);
	win.attach(c.t9);
	win.attach(c.t10);
	win.attach(c.t11);
	win.attach(c.t12);
	win.attach(c.dateT);
	while (!_kbhit())
	{
		time_t t = time(NULL);
		struct tm* localt = localtime(&t);
		string Y = to_string(localt->tm_year + 1900);
		string M = to_string(localt->tm_mon + 1);
		string D = to_string(localt->tm_mday);
		string h = to_string(localt->tm_hour);
		string m = to_string(localt->tm_min);
		string s = to_string(localt->tm_sec);
		if (M.size() == 1)
			M = '0' + M;
		if (D.size() == 1)
			D = '0' + D;
		if (h.size() == 1)
			h = '0' + h;
		if (m.size() == 1)
			m = '0' + m;
		if (s.size() == 1)
			s = '0' + s;
		string DT = Y + '/' + M + '/' + D +
			"   " + h + ':' + m + ':' + s;
		c.dateT.put(DT);
		c.draw_lines();
		win.attach(c);
		win.redraw();
		Fl::wait(1);
	}
	win.wait_for_button();
	return 0;
}