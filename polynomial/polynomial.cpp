#include <iostream>
#include"std_lib_facilities.h"
#include "Polynomial.h"

using namespace std;

Polynomial& Polynomial::operator=(const Polynomial& right)
{
	if (this == &right)
		return *this;
	poly.clear();
	poly = right.poly;
	return *this;
}
//修改
string Polynomial::format(int i) const
{
	//double d = poly[i];
	string res;
	//stringstream ss;
	//ss << d;
	//ss >> res;
	res = to_string(poly[i]);
	int pos = -1;
	int len = res.size();
	bool isneg = false;
	for (int i = 0; i < len; ++i)
	{
		if (i == 0 && res[i] == '-')
			isneg = true;
		if (res[i] == 'e')
		{
			if (!isneg)
				return string("0.0000");
			else
				return string("-0.0000");
		}
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
//修改
string Polynomial::format(double d) const
{
	string res;
	//stringstream ss;
	//ss << d;
	//ss >> res;
	res = to_string(d);
	int pos = -1;
	int len = res.size();
	bool isneg = false;
	for (int i = 0; i < len; ++i)
	{
		if (i == 0 && res[i] == '-')
			isneg = true;
		if (res[i] == 'e')
		{
			if (!isneg)
				return string("0.0000");
			else
				return string("-0.0000");
		}
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
		for (int i = 0; i < pos + 5; ++i)//会越界
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

Polynomial Polynomial::dif()
{
	int len = poly.size();
	if (len == 0)
	{
		std::cout << "error" << endl;
		std::cout << "error" << endl;
		std::cout << "error";
		exit(-1);
	}
	if (len == 1)
	{
		return Polynomial("0");
	}
	vector<double> temp(len - 1,0);
	for (int i = 1; i < len; ++i)
	{
		temp[i - 1] = poly[i] * i;
	}
	Polynomial ans(temp);
	return ans;
}

string Polynomial::calc(double x)
{
	double res = 0;
	int len = poly.size();
	if (len == 0)
	{
		std::cout << "error" << endl;
		std::cout << "error" << endl;
		std::cout << "error";
		exit(-1);
	}
	if (len == 1)
	{
		string ans = format(0);
		return ans;
	}
	res += poly[0];
	for (int i = 1; i < len; ++i)
	{
		res += poly[i] * pow(x, i);
	}
	string ans = format(res);
	return ans;
}

Polynomial Polynomial::rQ(const Polynomial& b) const
{
	Polynomial p(poly);
	Polynomial q = b;
	int m = p.returnExp();
	int n = q.returnExp();
	vector<double> temp(m - n + 1, 0);
	int i, j;
	vector<double> P = p.getV();
	vector<double> Q = q.getV();
	for (i = m - n; i >= 0; --i)
	{
		temp[i] = P[i + n] / Q[n];
		for (j = n; j >= 0; --j)
		{
			P[i + j] = P[i + j] - Q[j] * temp[i];
		}
	}
	while (temp.size() >= 1 && abs(temp[temp.size() - 1] - 0) < 1e-8)
	{
		temp.pop_back();
	}
	if (temp.size() == 0)
	{
		temp.push_back(0);
		Polynomial R(temp);
		return R;
	}
	Polynomial R(temp);
	return R;
}

Polynomial Polynomial::rR(const Polynomial& b) const
{
	Polynomial p(poly);
	Polynomial q = b;
	int m = p.returnExp();
	int n = q.returnExp();
	vector<double> temp(m - n + 1, 0);
	int i, j;
	vector<double> P = p.getV();
	vector<double> Q = q.getV();
	for (i = m - n; i >= 0; --i)
	{
		temp[i] = P[i + n] / Q[n];
		for (j = n; j >= 0; --j)
		{
			P[i + j] = P[i + j] - Q[j] * temp[i];
		}
	}
	while ( P.size() >= 1 && abs(P[P.size() - 1] - 0) < 1e-8)
	{
		P.pop_back();
	}
	if (P.size() == 0)
	{
		P.push_back(0);
		Polynomial R(P);
		return R;
	}
	Polynomial R(P);
	return R;
}

int Polynomial::returnExp() const
{
	return poly.size() - 1;
}

vector<double> Polynomial::getV() const
{
	return poly;
}

Polynomial::Polynomial(string s)
{
	string str;
	str = s + '+';
	int len = str.length();
	if (len == 0)
	{
		cout << "error" << endl;
		cout << "error" << endl;
		cout << "error";
		exit(-1);
	}
	vector<double> coef(100,0);
	int maxExp = 0;
	int pos = -1,nOdc = 0,nOde = 0;   //pos == -1说明系数还没有出现小数点；
	string coe, exp;
	bool isExp = false;
	bool isPositive = true;
	bool flag = false;
	char ch;
	for (int i = 0; i < len; ++i)
	{
		ch = str[i];
		if ('0' <= str[i] && str[i] <= '9')//碰到的是数字
		{
			if (isExp)//数字属于指数
			{
				exp += ch;
			}
			else//数字属于系数
			{
				coe += ch;
			}
		}
		else
		{
			if (str[i] == 'x')//碰到的是x，继续检查下一项
			{
				flag = true;
				continue;
			}
			else
			{
				if (str[i] == '^')//碰到的是幂运算符
					isExp = true;
				else
				{
					if (str[i] == '.')//碰到的是小数点
					{
						if (isExp == false)
						{
							nOdc++;
							if (nOdc > 1)
							{
								cout << "error" << endl;
								cout << "error" << endl;
								cout << "error";
								exit(-1);
							}
							coe += str[i];
							pos = i;
						}
						else
						{
							if (isExp)
							{
								cout << "error" << endl;
								cout << "error" << endl;
								cout << "error";
								exit(-1);
							}
						}
					}
					else
					{
						if (str[i] == '+' || str[i] == '-' || i == len - 1)//碰到正负号或者结尾
						{
							if (i == 0)//正负号在开头
							{
								isPositive = (str[i] == '-') ? false : true;
								continue;
							}
							if (str[i] == '-' && str[i - 1] == '^')//指数为正整数
							{
								cout << "error" << endl;
								cout << "error" << endl;
								cout << "error";
								exit(-1);
							}
							if (str[i - 1] == '+' || str[i - 1] == '-')//前面还是正负号
							{
								if (str[i - 1] == '+')
									isPositive = (str[i] == '-') ? false : true;
								else
									isPositive = (str[i] == '-') ? true : false;
								continue;
							}
							else//此时的正负号是连接两个单项式的或者已经读到了结尾
							{
								double temp = 0;//暂时存储系数
								int temp1 = 0;//暂时存储指数
								if (flag == true && exp.length() == 0)
								{
									temp1 = 1;
								}
								if (flag == true && coe.length() == 0)
								{
									temp = 1;
								}
								//计算单项式的系数与指数
								for (int i = 0; i < exp.length(); ++i)
								{
									temp1 = temp1 * 10 + exp[i] - '0';
								}
								maxExp = maxExp > temp1 ? maxExp : temp1;//保存目前最高次幂
								if (pos == -1)//说明系数为整数
								{
									for (int i = 0; i < coe.length(); ++i)
									{
										temp = temp * 10 + coe[i] - '0';
									}
								}
								else//系数是小数
								{
									int dot;
									for (int i = 0; i < coe.length(); ++i)
									{
										if (coe[i] == '.')
										{
											dot = i; break;
										}
									}
									for (int i = 0; i < dot; ++i)
									{
										temp = temp * 10 + coe[i] - '0';
									}
									for (int i = dot + 1; i < coe.length(); ++i)
									{
										temp += (coe[i] - '0') / pow(10, i - dot);
									}
								}
								if (!isPositive)
									temp = -temp;
								coef[temp1] += temp;//将系数插入对应指数下标处
								//准备进行下个单项式的读取
								isExp = false;
								isPositive = (str[i] == '-') ? false : true;
								flag = false;
								coe.clear();
								exp.clear();
								pos = -1;
								nOdc = 0;
								nOde = 0;
							}
						}
						else
						{
							cout << "error" << endl;
							cout << "error" << endl;
							cout << "error";
							exit(-1);
						}
					}
				}
			}
		}
	}
	while ( maxExp > 0 && coef[maxExp] == 0)
	{
		maxExp--;
	}
	poly.reserve(maxExp + 1);
	for (int i = 0; i < maxExp + 1; ++i)
	{
		poly.push_back(coef[i]);
	}
}

Polynomial::Polynomial(vector<double> v)
{
	poly = v;
}


ostream& operator<<(ostream& os, const Polynomial& p)
{
	if (p.poly.size() == 0)
		exit(-1);
	int len = p.poly.size();
	if (len - 1 == 0 && p.poly[len - 1] == 0)//长度为1，且系数值为0
	{
		os << "0.0000";
		return os;
	}
	if (len - 1 == 0)//长度为1，系数值不为0
	{
		os << p.format(len - 1);
	}
	else
	{
		if (p.poly[len - 1] != 0)//长度不为1，系数值不为0
		{
			os << p.format(len - 1);
			if (len - 1 == 1)//指数值为1
				os << "x";
			else
				os << "x^" << len - 1;//指数值不为1
		}
	}
	for (int i = len - 2; i >= 0; --i)
	{
		if (p.poly[i] == 0)
			continue;
		if (i == 0)
		{
			if (p.poly[i] > 0)
			{
				os << '+';
				os << p.format(i);
			}
			else
			{
				os << p.format(i);
			}
		}
		else 
		{
			if (i == 1)
			{
				if (p.poly[i] > 0)
				{
					os << '+';
					os << p.format(i);
					os << 'x';
				}
				else
				{
					if (p.poly[i] < 0)
					{
						os << p.format(i);
						os << 'x';
					}
				}
			}
			else
			{
				if (p.poly[i] > 0)
				{
					os << '+';
					os << p.format(i);
					os << "x^" << i;
				}
				else
				{
					if (p.poly[i] < 0)
					{
						os << p.format(i);
						os << "x^" << i;
					}
				}
			}
		}
	}
	return os;

}
		
			


int main()
{
	string str,str1;
	getline(cin, str);
	getline(cin, str1);
	Polynomial p(str);
	Polynomial q(str1);
	if (q.getV().size() == 1 && q.getV()[0] == 0)
	{
		cout << "error" << endl;
		cout << "error";
		exit(-1);
	}
	if (p.getV().size() == 1 && p.getV()[0] == 0)
	{
		cout << "0.0000" << endl;
		cout << "0.0000";
		return 0;
	}
	if (p.getV().size() < q.getV().size())
	{
		cout << "0.0000" << endl;
		cout << p;
		return 0;
	}
	cout << p.rQ(q) << endl;
	cout << p.rR(q);
	return 0;
}

