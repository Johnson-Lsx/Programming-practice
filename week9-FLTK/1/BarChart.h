#include"Graph.h"
#include"Point.h"
#include"std_lib_facilities.h"

class BarChart :public Graph_lib::Lines
{
private:
	double yScale;//纵坐标数据缩放比例
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
	BarChart(ifstream& fin, double w, double xx, double dis, double yy,double y_scale);
	int retNumOfBars() { return numOfBars; }
	void draw_lines();
};