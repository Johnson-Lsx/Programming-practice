#include "std_lib_facilities.h"
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
#include<sstream>
//#include "SimpleLinearRegression.h"
using namespace std;

class SimpleLinearRegression
{
private:
	vector<double> x;
	vector<double> y;
	double xx,yy,r;
	double Lxy, Lxx, Lyy;
	double a, b;
	void checkInput(string str);
	string format(double d);
public:
	SimpleLinearRegression() { Lxy = 0, Lxx = 0, Lyy = 0;};
	void Input();
	void SLR();
};
void SimpleLinearRegression::checkInput(string str)
{
	int count1 = 0,count2 = 0;
	int len = str.size();
	if (len == 0)
	{
		cout << "error" << endl;
		cout << "error" << endl;
		cout << "error";
		exit(-1);
	}
	for(int i = 0;i < len;++i)
	{
		if(str[i] != '.' && str[i] != '-' && (str[i] > '9' || str[i] < '0'))
		{
			cout << "error" << endl;
			cout << "error" << endl;
			cout << "error";
			exit(-1);
		}
		if (str[i] == '.')
		{
			count1++;
			if (count1 > 1)
			{
				cout << "error" << endl;
				cout << "error" << endl;
				cout << "error";
				exit(-1);
			}
		}
		if (str[i] == '-')
		{
			count2++;
			if (count2 > 1)
			{
				cout << "error" << endl;
				cout << "error" << endl;
				cout << "error";
				exit(-1);
			}
		}
	}

}
string SimpleLinearRegression::format(double d)
{
	string res;
	res = to_string(d);
	int pos = -1;
	int len = res.size();
	bool isneg = false;
	bool hasDot = false;
	int cnt = 0;
	if (res[0] == '-')
		isneg = true;
	for (int i = 0; i < len; ++i)
	{
		if (res[i] == '0')
			cnt++;
		if (res[i] == '.')
			hasDot = true;
	}
	if (isneg && hasDot && cnt == res.size() - 2)
	{
		return"0.0000";
	}
	if (!isneg && hasDot && cnt == res.size() - 1)
	{
		return"0.0000";
	}
	if (isneg && !hasDot && cnt == res.size() - 1)
	{
		return"0.0000";
	}
	if (!isneg && !hasDot && cnt == res.size())
	{
		return"0.0000";
	}
	for (int i = 0; i < len; ++i)
	{
		if (res[i] == '.')
		{
			pos = i; break;
		}
	}
	if (pos == -1)
	{
		string ans;
		ans = res + ".0000";
		return ans;
	}
	string ans(pos + 5, '0');
	if (pos + 5 < res.size())
	{
		for (int i = 0; i < pos + 5; ++i)
		{
			ans[i] = res[i];
		}
	}
	else
	{
		for (int i = 0; i < res.size(); ++i)
		{
			ans[i] = res[i];
		}
	}
	return ans;
}

void SimpleLinearRegression::Input()
{
	string str, strX, strY;
	double X, Y;
	int cnt = 0;
	cin >> str;
	stringstream is(str);
	checkInput(str);
	is >> xx;
	while (cin >> strX >> strY)
	{
		cnt++;
		stringstream isX(strX);
		stringstream isY(strY);
		checkInput(strX);
		checkInput(strY);
		isX >> X;
		isY >> Y;
		x.push_back(X);
		y.push_back(Y);
	}
	if (x.size() != y.size())
	{
		cout << "error";
		exit(-1);
	}
	if (cnt < 2)
	{
		cout << "error" << endl;
		cout << "error" << endl;
		cout << "error";
		exit(-1);
	}
	int count = x.size();
	double x_sum = 0, y_sum = 0;
	double x_avg, y_avg;
	for (int i = 0; i < count; ++i)
	{
		x_sum += x[i];
		y_sum += y[i];
	}
	x_avg = x_sum / count;
	y_avg = y_sum / count;
	for (int i = 0; i < count; ++i)
	{
		Lxy += (x[i] - x_avg) * (y[i] - y_avg);
		Lxx += (x[i] - x_avg) * (x[i] - x_avg);
		Lyy += (y[i] - y_avg) * (y[i] - y_avg);
	}
	r = Lxy / sqrt(Lxx * Lyy);
	b = Lxy / Lxx;
	a = y_avg - b * x_avg;
	yy = a + b * xx;
}

void SimpleLinearRegression::SLR()
{
	if (fabs(r) <= 0.75)
	{
		cout << format(r) << endl;
		cout << "error" << endl;
		cout << "error";
		return;
	}
	cout << format(r) << endl;
	if(a > 0)
	cout << "y=" << format(b) << "*x+" << format(a) << endl;
	else
	{
		cout << "y=" << format(b) << "*x" << format(a) << endl;
	}
	cout << format(yy);
}


int main()
{
	SimpleLinearRegression s;
	s.Input();
	s.SLR();
	return 0;
}
