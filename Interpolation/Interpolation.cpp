#include <iostream>
#include "Interpolation.h"
using namespace std;
double NewtonInter::fract(int k)
{
	if (k < 0)
		throw"k cant't be negative";
	if (k == 0 || k == 1)
		return 1;
	else
		return k * fract(k - 1);
}

bool NewtonInter::checkX()
{
	int len = x.size();
	if (len == 1)
	{
		return true;
	}
	double tmp = x[1] - x[0];
	for (int i = 2; i < len; ++i)
		if (fabs(x[i] - x[i - 1] - tmp) > 1e-4)
			return false;
	return true;

}
void NewtonInter::checkInput(string str)
{
	int len = str.size();
	for (int i = 0; i < len; ++i)
	{
		if (str[i] != '.' && str[i] != '-' && (str[i] > '9' || str[i] < '0'))
		{
			cout << "error";
			exit(-1);
		}
	}
}
string NewtonInter::format(double d)
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
void NewtonInter::Input()
{
	string str, strX, strY;
	double X, Y;
	cin >> str;
	stringstream is(str);
	checkInput(str);
	is >> xx;
	unordered_map<double, double> map;
	while (cin >> strX >> strY)
	{
		stringstream isX(strX);
		stringstream isY(strY);
		isX >> X;
		isY >> Y;
		x.push_back(X);
		map[X] = Y;
	}
	sort(x.begin(), x.end());
	h = (x[x.size() - 1] - x[0]) / (x.size() - 1);
	for (int i = 0; i < x.size(); ++i)
		y.push_back(map[x[i]]);
	vector<vector<double>> tmp(y.size(), vector<double>(y.size(), 0));
	for (int i = 0; i < y.size(); ++i)
		tmp[i][0] = y[i];
	for (int col = 1; col < y.size(); ++col)
	{
		for (int row = col; row < y.size(); ++row)
			tmp[row][col] = tmp[row][col - 1] - tmp[row - 1][col - 1];
	}
	dif = tmp;
}

double NewtonInter::Interpolation()
{
	if (!checkX())
	{
		cout << "error";
		exit(-1);
	}
	double t = (xx - x[0]) / h;
	double sum = dif[0][0];
	int n = y.size();
	for (int k = 1; k < n; ++k)
	{
		double p = 1;
		for (int i = 0; i < k; ++i)
			p *= (t - i);
		sum += dif[k][k] / fract(k) * p;
	}
	return sum;
}
int main()
{
	NewtonInter s;
	s.Input();
	cout << s.format(s.Interpolation());
	return 0;
}

