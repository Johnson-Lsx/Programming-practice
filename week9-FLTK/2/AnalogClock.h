#include"Graph.h"
#include"GUI.h"
#include"Point.h"
#include"std_lib_facilities.h"
#include<ctime>
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
	vector<pair<double,double>> dxy;//数字
	void getTime();
public:
	Circle dialPlate;//表盘
	Lines notches;//刻度
	Text t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12;
	Out_box dateT;
	AnalogClock(Point p, double rr,double lens,double lenf,double lenm);
	void draw_lines();
	string retData() { return (to_string(YY) + '/' + to_string(MM) + '/' + to_string(DD)); }
	string retTime(){return to_string(hh) + ":" + to_string(mm) + ":" + to_string(ss);}
};

