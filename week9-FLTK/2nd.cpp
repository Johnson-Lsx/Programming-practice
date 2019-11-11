#include"Graph.h"
#include"Simple_window.h"
#include"Point.h"
#include"std_lib_facilities.h"

class BarChart:public Graph_lib::Lines
{
private:
	const int x_max, y_max;
	const int x_offset, y_offset;
	const int x_space, y_space;
	const int x_length, y_length;
	vector<vector<pair<double, double>>> value_pairs;
	int numOfDataset;//有几组要绘制
	int max_x, min_x;//x的最大最小值
	int max_y, min_y;//y的最大最小值
	int numOfNotches;
	double lengthOfNotches;
	double xScale, yScale;
	void getX();
	void getY();
	void generateChart();
	bool check();
public:
	BarChart(const int x_max, const int y_max, const vector<vector<pair<double, double>>>& vp);
	void draw_lines(Simple_window& win);
};

#include "BarChart.h"
#include<algorithm>
void BarChart::getX()
{
	vector<double> xMax;
	vector<double> xMin;
	for (int i = 0; i < value_pairs.size(); ++i)
	{
		vector<double> temp;
		for (int j = 0; j < value_pairs[i].size(); ++j)
			temp.push_back(value_pairs[i][j].first);
		sort(temp.begin(), temp.end());
		xMax.push_back(temp.back());
		xMin.push_back(temp.front());
	}
	sort(xMax.begin(), xMax.end());
	sort(xMin.begin(), xMin.end());
	max_x = xMax.back();
	min_x = xMin.front();
}

void BarChart::getY()
{
	vector<double> yMax;
	vector<double> yMin;
	for (int i = 0; i < value_pairs.size(); ++i)
	{
		vector<double> temp;
		for (int j = 0; j < value_pairs[i].size(); ++j)
			temp.push_back(value_pairs[i][j].second);
		sort(temp.begin(), temp.end());
		yMax.push_back(temp.back());
		yMin.push_back(temp.front());
	}
	sort(yMax.begin(), yMax.end());
	sort(yMin.begin(), yMin.end());
	max_y = yMax.back();
	min_y = yMin.front();
}

void BarChart::generateChart()
{
	for (int i = 0; i < value_pairs.size(); ++i)
	{
		for (int j = 0; j < value_pairs[i].size(); ++j)
		{
			Point p1((value_pairs[i][j].first - 1) * lengthOfNotches + i * lengthOfNotches, y_max - y_offset);
			Point p2((value_pairs[i][j].first - 1) * lengthOfNotches + i * lengthOfNotches, y_max - y_offset - (value_pairs[i][j].second * yScale));
			Point p3((value_pairs[i][j].first - 1) * lengthOfNotches + i * lengthOfNotches + lengthOfNotches - 1, y_max - y_offset - (value_pairs[i][j].second * yScale));
			Point p4((value_pairs[i][j].first - 1) * lengthOfNotches + i * lengthOfNotches + lengthOfNotches - 1, y_max - y_offset);
			Graph_lib::Lines::add(p1, p2);
			Graph_lib::Lines::add(p2, p3);
			Graph_lib::Lines::add(p3, p4);
		}
	}
}

bool BarChart::check()
{
	for (int i = 0; i < value_pairs.size() - 1; ++i)
	{
		if (value_pairs[i].size() != value_pairs[i + 1].size())
			return false;
	}
	if (value_pairs[value_pairs.size() - 1].size() != value_pairs[value_pairs.size() - 2].size())
		return false;
	return true;
}

BarChart::BarChart(const int x_max, const int y_max, const vector<vector<pair<double, double>>>& vp):
	x_max(x_max),y_max(y_max),
	x_offset(x_max / 6),y_offset(y_max / 6),x_space(x_max/10),y_space(y_max/10),
	x_length(x_max-x_offset-x_space),y_length(y_max-y_offset-y_space)
{
	value_pairs = vp;
	if (!check())
	{
		exit(-1);
	}
	numOfDataset = value_pairs.size();
	getX();
	getY();
	xScale = double(x_length) / (max_x - min_x);
	yScale = double(y_length) / (max_y);
	numOfNotches = numOfDataset * value_pairs[0].size();
	lengthOfNotches = double(x_length) / numOfNotches;
	generateChart();
}

void BarChart::draw_lines(Simple_window& win)
{
	Graph_lib::Axis xaxis(Graph_lib::Axis::x,Point(x_offset,y_max - y_offset),x_length,numOfNotches,"month");
	Graph_lib::Axis yaxis(Graph_lib::Axis::y, Point(x_offset, y_max - y_offset), x_length, max_y, "temperature");
	xaxis.set_color(Graph_lib::Color(8));
	yaxis.set_color(Graph_lib::Color(8));
	xaxis.draw_lines();
	yaxis.draw_lines();
	win.attach(xaxis);
	win.attach(yaxis);
	Graph_lib::Lines::set_color(Graph_lib::Color(1));
	Graph_lib::Lines::draw_lines();
}
