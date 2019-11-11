#pragma once
#include"std_lib_facilities.h"
#include"Point.h"
#include"Graph.h"


class hyperelliptic :public Graph_lib::Lines
{
private:
	double a, b, m, n;
	vector<Point> mpoints;
public:
	hyperelliptic(double aa, double bb, double mm, double nn, int N) :a(aa), b(bb), m(mm), n(nn)
	{
		double dx = 4 * a / N;
		vector<double> xx;
		for (int i = 0; i <= N / 2; ++i)
		{
			xx.push_back(-a + i * dx);
		}
		vector<double> y1, y2;
		for (int i = 1; i < xx.size() - 1; ++i)
		{
			double temp;
			temp = pow(1 - pow(fabs(xx[i] / a), m), 1 / n) * b;
			y1.push_back(temp);
			y2.push_back(-temp);
		}
		mpoints.push_back(Point(xx[0] + int(abs(a)), 0 + int(abs(b))));
		for (int i = 1; i < xx.size() - 1; ++i)
		{
			mpoints.push_back(Point(xx[i] + int(abs(a)), y1[i - 1] + int(abs(b))));
			mpoints.push_back(Point(xx[i] + int(abs(a)), y2[i - 1] + int(abs(b))));
		}
		mpoints.push_back(Point(xx.back() + int(abs(a)), 0 + int(abs(b))));
	}
	vector<Point> visitP()
	{
		return mpoints;
	}
	void draw()
    {
        for (int i = 0; i < mpoints.size(); ++i)
	{
		for (int j = i + 1; j < mpoints.size(); ++j)
		{
			Graph_lib::Lines::add(tmp[i], tmp[j]);
		}
	}
	Graph_lib::Lines::draw_lines();
	Graph_lib::Lines::set_color(Color(1));
    }
};