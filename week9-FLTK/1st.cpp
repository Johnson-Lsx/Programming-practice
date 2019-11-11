#include"Graph.h"
#include"Point.h"
#include"std_lib_facilities.h"

class BarChart:public Graph_lib::Lines
{
private:
	double base_y;//x轴的y坐标
	double x;//第一个矩形的左下角x坐标
	double width;//矩形的宽度
	double dist;//矩形之间的间距
	int numOfBars;//矩形的个数
	vector<vector<double>> temperature;//按月份存储每天的温度
	vector<double> temAvg;//每个月平均气温
	void process(ifstream& fin);//处理文件数据
	void rmPunc(string& str);//去除一行数据中的标点
	void getAvg();
	void generateBar();
public:
	BarChart(ifstream& fin,double w, double xx,double dis,double yy);
	int retNumOfBars() { return numOfBars; }
	void draw_lines();
};

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
		Point p2(x + i * (width + dist), base_y - temAvg[i]);
		Point p3(x + i * (width + dist) + width, base_y - temAvg[i]);
		Point p4(x + i * (width + dist) + width, base_y);
		Graph_lib::Lines::add(p1, p2);
		Graph_lib::Lines::add(p2, p3);
		Graph_lib::Lines::add(p3, p4);
	}
}

BarChart::BarChart(ifstream& fin, double w, double xx, double dis, double yy) :width(w), x(xx), dist(dis), base_y(yy)
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
