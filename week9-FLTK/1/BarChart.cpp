#include "BarChart.h"

void BarChart::process(ifstream& fin)
{
	if (!fin)
	{
		throw"fail to open the file!";
	}
	vector<vector<double>> temp(13, vector<double>(0));
	string line;
	getline(fin, line);
	line = "";
	while (getline(fin, line))
	{
		rmPunc(line);
		int y, m, d;
		double temAvg;
		stringstream is(line);
		is >> y >> m >> d >> temAvg;
		temp[m].push_back(temAvg);
	}
	temperature = temp;
	getAvg();
	numOfBars = temAvg.size();
}

void BarChart::rmPunc(string& str)
{
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == '/' || str[i] == ',')
			str[i] = ' ';
	}
}

void BarChart::getAvg()
{
	for (int i = 1; i < temperature.size(); ++i)
	{
		double sum = 0;
		for (int j = 0; j < temperature[i].size(); ++j)
		{
			sum += temperature[i][j];
		}
		double avg = sum / temperature[i].size();
		temAvg.push_back(avg);
	}
}

void BarChart::generateBar()
{
	for (int i = 0; i < numOfBars; ++i)
	{
		Point p1(x + i * (width + dist), base_y);
		Point p2(x + i * (width + dist), base_y - temAvg[i] * yScale);
		Point p3(x + i * (width + dist) + width, base_y - temAvg[i] * yScale);
		Point p4(x + i * (width + dist) + width, base_y);
		Graph_lib::Lines::add(p1, p2);
		Graph_lib::Lines::add(p2, p3);
		Graph_lib::Lines::add(p3, p4);
	}
}

BarChart::BarChart(ifstream& fin, double w, double xx, double dis, double yy, double y_scale) :
	width(w), x(xx), dist(dis), base_y(yy),yScale(y_scale)
{
	if (!fin)
	{
		throw"fail to open the file!";
	}
	process(fin);
}

void BarChart::draw_lines()
{
	generateBar();
	Graph_lib::Lines::draw_lines();
}