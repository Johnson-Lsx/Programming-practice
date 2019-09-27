#pragma once
#include<vector>
#include<string>
#include<cmath>
#include<iostream>
#include<iomanip>
#include<sstream>
#include<unordered_map>
#include<algorithm>
using namespace std;
class LinearEquations
{
private:
	vector<string> equation;
	vector<double> ans;//存储答案
	vector<double> B;//记录常数项
	vector<vector<double>> matrix;//记录最终系数
	vector<int> index;//记录所有出现过的下标
	vector<vector<double>> helperMatrix;//辅助矩阵,记录第一次系数
	unordered_map<int, int> map;//将下标的数字与应该在系数矩阵中的数字对应
	double* constAtLeft;//出现在等号左边的常数项

	void setConst();//设置constAtLeft，对其进行初始化
	void unique();//删除Index数组中的重复元素
	void getMap();//获取map
	void getMatrix();//获得matrix系数矩阵
	void Gauss();//高斯消去法
	void swap(double& a, double& b);
	void getPrepare();
	void reshape();
	string format(double d);
public:
	LinearEquations() {};
	~LinearEquations() {};
	void getEqua(string s);//共有函数，用于从用户的输入处获得方程组
	void output();
};
void LinearEquations::getMatrix()
{
	getPrepare();//调用该函数之后，已经得到了B，辅助矩阵
	unique();
	getMap();
	if (index.size() > equation.size())
	{
		cout << "error";
		exit(-1);
	}
	//vector<double> temp(index.size(), 0);
	for (int i = 0; i < helperMatrix.size(); ++i)
	{
		vector<double> temp(index.size(), 0);
		for (int j = 1; j < helperMatrix[i].size(); ++j)
		{
			if (map.find(j) != map.end())
			{
				temp[map[j] - 1] = helperMatrix[i][j];
			}
		}
		matrix.push_back(temp);
	}
}

void LinearEquations::getMap()
{
	int len = index.size();
	for (int i = 0; i < len; ++i)
	{
		map[index[i]] = i + 1;
	}
}
void LinearEquations::unique()
{
	vector<int> tmp = index;
	index.clear();
	sort(tmp.begin(), tmp.end());
	int len = tmp.size();
	index.push_back(tmp[0]);
	int prev = tmp[0];
	for (int i = 1; i < len; ++i)
	{
		int cur = tmp[i];
		if (cur != prev)
		{
			index.push_back(cur);
		}
		prev = cur;
	}
}
void LinearEquations::setConst()
{
	delete[] constAtLeft;
	constAtLeft = new double[equation.size()];
	for (int i = 0; i < equation.size(); ++i)
		constAtLeft[i] = 0;
}
void LinearEquations::getEqua(string s)
{
	equation.push_back(s);
}

void LinearEquations::output()
{
	Gauss();
	int len = ans.size();
	for (int i = 0; i < len - 1; ++i)
		cout << format(ans[i]) << ' ';
	cout << format(ans[len - 1]);
}

void LinearEquations::Gauss()
{
	getMatrix();//调用该函数之后，已经得到系数矩阵，B
	if (index.size() < equation.size())
	{
		reshape();
		//调用该函数，处理方程个数比未知数个数多的情况
	}
	vector<double> x(index.size(), 0);
	double temp;
	int i, j, k;
	int n = index.size();
	for (k = 0; k < n - 1; ++k)
	{
		//选取主元
		int maxRow = k;
		double max = fabs(matrix[k][k]);
		for (int r = k; r < n; ++r)
		{
			if (fabs(matrix[r][k]) > max)
			{
				max = fabs(matrix[r][k]);
				maxRow = r;
			}
		}
		if (maxRow != k)
		{
			swap(B[k], B[maxRow]);
			for (int col = 0; col < n; ++col)
				swap(matrix[k][col], matrix[maxRow][col]);
		}
		if (!matrix[k][k])
		{
			cout << "error";
			exit(-1);
		}
		for (i = k + 1; i < n; ++i)
		{
			temp = matrix[i][k] / matrix[k][k];
			for (j = k; j < n; ++j)
			{
				matrix[i][j] = matrix[i][j] - temp * matrix[k][j];
			}
			B[i] = B[i] - temp * B[k];
		}
	}
	if (matrix[n - 1][n - 1] == 0)
	{
		cout << "error";
		exit(-1);
	}
	if (B[n - 1] == 0)
		x[n - 1] = 0;
	else
		x[n - 1] = B[n - 1] / matrix[n - 1][n - 1];
	for (k = n - 2; k >= 0; --k)
	{
		double S = B[k];
		for (j = k + 1; j < n; ++j)
		{
			S = S - matrix[k][j] * x[j];
		}
		x[k] = S / matrix[k][k];
	}
	ans = x;
}

string LinearEquations::format(double d)
{
	string res;
	res = to_string(d);
	int pos = -1;
	int len = res.size();
	bool isneg = false;
	bool hasDot = false;//新增
	int cnt = 0;//新增
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
void LinearEquations::reshape()
{
	//调用该函数之前，必须已经获得了系数矩阵和B，并且方程数目大于未知数数目
	//下面要做的是检查是不是有成比例的两行
	int rows = matrix.size();
	if (rows == 0)
	{
		cout << "error";
		exit(-1);
	}
	int cols = matrix[0].size();
	int i, j, k;
	while (matrix.size() > matrix[0].size())
	{
		for (i = 0; i < matrix.size(); ++i)
		{
			for (j = i + 1; j < matrix.size(); ++j)
			{
				bool flag = true;
				double tmp = matrix[i][0] / matrix[j][0];
				for (k = i; k < cols; ++k)
				{
					if (matrix[j][k] != 0 && matrix[i][k] / matrix[j][k] != tmp)
					{
						flag = false; break;
					}
				}
				if (flag)
				{
					if ((B[j] != 0 && B[i] / B[j] != tmp) || (B[j] == 0 && B[i] != 0))
					{
						cout << "error";
						exit(-1);
					}
					for (int c = j + 1; c < matrix.size(); ++c)
					{
						matrix[c - 1].clear();
						matrix[c - 1] = matrix[c];
					}
					for (int c = j + 1; c < B.size(); ++c)
					{
						B[c - 1] = B[c];
					}
					matrix.pop_back();
					B.pop_back();
					continue;//说明i,j行成比例
				}
			}
		}
		if (i == matrix.size())
			break;
	}
	if (matrix.size() < matrix[0].size())
	{
		cout << "error";
		exit(-1);
	}
	else
	{
		while (matrix.size() > matrix[0].size())
		{
			matrix.pop_back();
			B.pop_back();
		}
	}
}
void LinearEquations::swap(double& a, double& b)
{
	double c;
	c = a;
	a = b;
	b = c;
}

void LinearEquations::getPrepare()
{
	setConst();
	vector<double> bT(equation.size(), 0);
	for (int c = 0; c < equation.size(); ++c)
	{
		string s;
		s = equation[c];
		string str;
		str = s;
		if (str.length() == 0)
		{
			cout << "error";
			exit(-1);
		}
		str += '+';
		int len = str.length();
		vector<double> coef(100, 0);//存储对应下标的系数
		int maxIndex = 0;//记录最大下标
		int pos = -1, nOdc = 0, nOdi = 0;   //pos == -1说明系数还没有出现小数点；
		string coe, ind;
		bool atRight = false;
		bool isIndex = false;
		bool isPositive = true;
		bool flag = false;//falg==false则说明处理的是常数项
		char ch;
		int i;
		for (i = 0; i < len; ++i)
		{
			ch = str[i];
			if ('0' <= str[i] && str[i] <= '9')//碰到的是数字
			{
				if (isIndex)//数字属于未知数下标
				{
					ind += ch;
				}
				else//数字属于系数
				{
					coe += ch;
				}
			}
			else
			{
				if (str[i] == 'x')//碰到的是x，继续检查下字符
				{
					flag = true;//说明不是常数项
					continue;
				}
				else
				{
					if (str[i] == '_')//碰到的是下标符号
						isIndex = true;
					else
					{
						if (str[i] == '.')//碰到的是小数点
						{
							if (isIndex == false)//小数点不是下标的
							{
								nOdc++;
								if (nOdc > 1)
								{
									cout << "error";//一个系数出现多个小数点
									exit(-1);
								}
								coe += str[i];
								pos = i;
							}
							else
							{
								if (isIndex)
								{
									cout << "error";//下标应该是正整数
									exit(-1);
								}
							}
						}
						else
						{
							if (str[i] == '=' || str[i] == '+' || str[i] == '-')//碰到正负号或者结尾
							{
								if ((str[i] == '+' || str[i] == '-') && i == 0)//正负号在开头
								{
									isPositive = (str[i] == '-') ? false : true;
									continue;
								}
								if (str[i] == '-' && str[i - 1] == '_')//下标应该为正整数
								{
									cout << "error";
									exit(-1);
								}
								if ((str[i] == '+' || str[i] == '-') && (str[i - 1] == '+' || str[i - 1] == '-'))//前面还是正负号
								{
									if (str[i - 1] == '+')
										isPositive = (str[i] == '-') ? false : true;
									else
										isPositive = (str[i] == '-') ? true : false;
									continue;
								}
								else//此时的正负号是连接两个单项的或者已经读到了结尾
								{
									int now = i;
									double temp = 0;//暂时存储系数
									int temp1 = 0;//暂时存储下标
									if (flag == true && coe.length() == 0)
									{
										temp = 1;
									}
									//计算系数与下标
									for (int j = 0; j < ind.length(); ++j)
									{
										temp1 = temp1 * 10 + ind[j] - '0';
									}
									maxIndex = maxIndex > temp1 ? maxIndex : temp1;//保存目前最大下标
									if (temp1 != 0)
									{
										index.push_back(temp1);
									}
									if (pos == -1)//说明系数为整数
									{
										for (int j = 0; j < coe.length(); ++j)
										{
											temp = temp * 10 + coe[j] - '0';
										}
									}
									else//系数是小数
									{
										int dot;
										for (int j = 0; j < coe.length(); ++j)
										{
											if (coe[j] == '.')
											{
												dot = j; break;
											}
										}
										for (int j = 0; j < dot; ++j)
										{
											temp = temp * 10 + coe[j] - '0';
										}
										for (int j = dot + 1; j < coe.length(); ++j)
										{
											temp += (coe[j] - '0') / pow(10, j - dot);
										}
									}
									if (!isPositive)
										temp = -temp;
									if (!flag)//说明计算到的其实是常数项
									{
										//constAtLeft[c] += temp;
										if (!atRight)//常数项在左边
										{
											bT[c] -= temp;
										}
										else
										{
											bT[c] += temp;
										}
										if (str[now] == '=')
											atRight = true;
									}
									else
									{
										if (!atRight)//常数项在左边
										{
											coef[temp1] += temp;//将系数插入对应指数下标处
										}
										else
										{
											coef[temp1] -= temp;//将系数插入对应指数下标处
										}
										if (str[now] == '=')
											atRight = true;
									}
									//准备进行下个单项式的读取
									isIndex = false;
									isPositive = (str[i] == '-') ? false : true;
									flag = false;
									coe.clear();
									ind.clear();
									pos = -1;
									nOdc = 0;
									nOdi = 0;
								}
							}
							else
							{
								cout << "error";
								exit(-1);
							}
						}
					}
				}
			}
		}
		vector<double> ret;
		for (int i = 0; i <= maxIndex; ++i)
			ret.push_back(coef[i]);
		helperMatrix.push_back(ret);
	}
	B = bT;
}
