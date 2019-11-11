#define _CRT_SECURE_NO_WARNINGS
#include "AnalogClock.h"

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
	const double PI = acos(-1);
	m = (totalSec * 6)/ 180 * PI;
	f = (totalSec * 0.1) / 180 * PI;
	s = (totalSec / 120) / 180 * PI;
	double x1, x2, x3, y1, y2, y3;
	x1 = o.x + (mz) * sin(m);
	y1 = o.y - (mz) * cos(m);
	x2 = o.x + (fz) * sin(f);
	y2 = o.y - (fz) * cos(f);
	x3 = o.x + (sz) * sin(s);
	y3 = o.y - (sz) * cos(s);
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

AnalogClock::AnalogClock(Point p, double rr = 200, double lens = 80, double lenf = 130, double lenm = 180)
	:dialPlate(Point(p.x - r, p.y - r), rr), t1(p, "1"), t2(p, "2"), t3(p, "3"), t4(p, "4"),
	t5(p, "5"), t6(p, "6"), t7(p, "7"), t8(p, "8"), t9(p, "9"), t10(p, "10"), t11(p, "11"), t12(p, "12"),
	dateT(Point(p.x - 75,p.y + rr / 2), 150, 20, "")
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
		dxy.push_back(make_pair(x2-o.x-10,y2 - o.y+10));
	}
	t1.move(dxy[1].first, dxy[1].second);
	t2.move(dxy[2].first, dxy[2].second);
	t3.move(dxy[3].first, dxy[3].second - 3);
	t4.move(dxy[4].first, dxy[4].second - 5);
	t5.move(dxy[5].first + 3, dxy[5].second - 10);
	t6.move(dxy[6].first + 5, dxy[6].second - 12);
	t7.move(dxy[7].first + 8, dxy[7].second - 12);
	t8.move(dxy[8].first + 10, dxy[8].second - 10);
	t9.move(dxy[9].first + 10, dxy[9].second - 5);
	t10.move(dxy[10].first + 9, dxy[10].second - 5);
	t11.move(dxy[11].first + 8, dxy[11].second);
	t12.move(dxy[0].first + 2, dxy[0].second);
}

void AnalogClock::draw_lines()
{
	dialPlate.draw_lines();
	notches.draw_lines();
	getTime();
	if (color().visibility())
		for (int i = 1; i < number_of_points(); i += 2)
			fl_line(point(i - 1).x, point(i - 1).y, point(i).x, point(i).y);
}