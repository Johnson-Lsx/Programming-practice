#pragma once
#include<vector>
#include<string>
#include<cmath>
#include<iostream>
#include<iomanip>
#include<sstream>
using namespace std;
class Polynomial
{
	friend ostream& operator<<(ostream&,const Polynomial&);
private:
	vector<double> poly;
	//string dbs(const string& s)const;
public:
	Polynomial(string s);
	Polynomial(vector<double> v);
	~Polynomial(){}
	Polynomial& operator=(const Polynomial&);
	string format(int i) const;
	string format(double d)const;
	Polynomial dif()const;
	Polynomial dif2()const;
	string calc(double)const;
	double calcu(double)const;
	Polynomial rQ(const Polynomial& b)const;//������
	Polynomial rR(const Polynomial& b)const;//��������
	int returnExp()const;
	vector<double> getV()const;
	bool checkNewton(double a, double b)const;
	double Newton(double x)const;
};

