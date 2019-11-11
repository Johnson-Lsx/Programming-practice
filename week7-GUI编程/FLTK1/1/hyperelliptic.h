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
	hyperelliptic(double aa, double bb, double mm, double nn, int N) :a(aa), b(bb), m(mm), n(nn)//构造函数，将需要被连线的点的坐标一一计算出来先存储在mpoints中，再转到points
	{
		double dx = 4 * a / N;//dx表示每个点之间再x轴上的间隔
		vector<double> xx;//存储横坐标
		for (int i = 0; i <= N / 2; ++i)
		{
			xx.push_back(-a + i * dx);
		}
		vector<double> y1, y2;//y1存储大于0的纵坐标，y2存储小于0的纵坐标
		for (int i = 1; i < xx.size() - 1; ++i)
		{
			double temp;
			temp = pow(1 - pow(fabs(xx[i] / a), m), 1 / n) * b;//利用超椭圆的定义，由x计算y
			y1.push_back(temp);
			y2.push_back(-temp);
		}
		mpoints.push_back(Point(xx[0] + int(abs(a)), 0 + int(abs(b))));//将(-a,0)存储进去，x坐标后面加上abs(a)和y坐标后面加上abs(b)是为了将图像全部显示再窗口
		for (int i = 1; i < xx.size() - 1; ++i)//将中间成对的点存储进去
		{
			mpoints.push_back(Point(xx[i] + int(abs(a)), y1[i - 1] + int(abs(b))));
			mpoints.push_back(Point(xx[i] + int(abs(a)), y2[i - 1] + int(abs(b))));
		}
		mpoints.push_back(Point(xx.back() + int(abs(a)), 0 + int(abs(b))));//将(a,0)存储进去
	}
	vector<Point> visitP()//返回mpoints
	{
		return mpoints;
	}
	~hyperelliptic() {}
	void draw()//画图函数，利用Lines来画图
	{
		for (int i = 0; i < mpoints.size(); ++i)
		{
			for (int j = i + 1; j < mpoints.size(); ++j)
			{
				Graph_lib::Lines::add(mpoints[i], mpoints[j]);
			}
		}
		Graph_lib::Lines::draw_lines();
		Graph_lib::Lines::set_color(Graph_lib::Color(1));
	}
};