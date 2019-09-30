#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<cmath>
#include<sstream>
using namespace std;
class NewtonInter
{
private:
	vector<double> x;
	vector<double> y;
	vector<vector<double>> dif;
	double xx;
	double h;
	double fract(int k);
	bool checkX();
	void checkInput(string str);
public:
	NewtonInter() {};
	~NewtonInter() {};
	void Input();
	string format(double d);
	double Interpolation();
};