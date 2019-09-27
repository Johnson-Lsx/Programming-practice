#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<fstream>
using namespace std;
const int max = 128;  //max表示Number类最大位数（包括负号和小数点在内）
//定义一个数类，可接收普通整数、大整数、小数等等作为实例
class Number
{
	friend ostream& operator<<(ostream& os, const Number& obj)
	{
		int len = obj.num.size();
		if (len == 0)
		{
			cout << "error";
			exit(-1);
		}
		for (int i = 0; i < len; ++i)
		{
			os << obj.num[i];
		}
		return os;
	}
private:
	vector<char> num;
	bool Add;
	bool checkStyle(vector<char>& number)
	{
		int len = number.size(),cnt = 0;
		if (Add && (len > max + 1 || len <= 0))
			return false;
		if (!Add && (len > max || len <= 0))//提交成功的代码是将这一行的128改为129//
			return false;
		if (len == 1 && number[0] == '-')
			return false;
		if (number[0] == '.')
			return false;
		if (len >= 2 && ((number[0] == '-' && number[1] == '.') || (number[0] == '-' && number[1] == '-')))
			return false;
		for (int i = 0; i < len; ++i)
		{
			if (number[i] == '.')
				cnt++;
		}
		if (cnt >= 2)
			return false;
		return true;
	}
public:
	Number() { Add = false; }
	void changeAdd()
	{
		if (Add)
			Add = false;
		else
		{
			Add = true;
		}

	}
	bool returnAdd()
	{
		return Add;
	}
	void makeNumber(vector<char>& number)
	{
		if (!checkStyle(number))
		{
			cout << "error";
			exit(-1);
		}
		int len = number.size();
		num.reserve(len);//改动
		num = number;
	}
	Number& operator=(const Number& right)
	{
		if (this == &right)
			return *this;
		num.clear();
		num.reserve(right.num.size());
		num = right.num;
		Add = right.Add;
		return *this;
	}
	vector<char>& getNum()
	{
		return num;
	}
};


//定义一个表达式类，支持任意两个Number类实例的加减乘除操作，计算规则满足一般的数学计算法则
class Expression
{
private:
	Number op1, op2;
	vector<char> intSub(const vector<char> op1, const vector<char> op2)
	{
		vector<char> res;
		vector<char> t1 = op1;
		vector<char> t2 = op2;
		res.reserve(op1.size() + 1);
		if (op1 == op2)
		{
			res.push_back('0');
			return res;
		}
		int len1 = op1.size();
		int len2 = op2.size();
		int minus = 0, result;
		for (int i = 0; i < len1 - len2; ++i)
		{
			t2.insert(t2.begin(), '0');
		}
		for (int i = len1 - 1; i >= 0; --i)
		{
			result = t1[i] - t2[i] - minus;
			if (result < 0)
			{
				result += 10;
				minus = 1;
			}
			else
				minus = 0;
			res.insert(res.begin(), result + '0');
		}
		while (res.size() > 0 && (res[0] == '0'))
			res.erase(res.begin());
		return res;
	}//op1 > op2
	bool checkZero(const vector<char>& op)
	{
		bool isZero = true;
		int len = op.size();
		if (len == 0)
		{
			cout << "error";
			exit(-1);
		}
		for (int i = 0; i < len; ++i)
		{
			if (op[i] == '0' || op[i] == '.')
				continue;
			else
			{
				isZero = false; break;
			}
		}
		return isZero;
	}
	bool intGreater(const vector<char> op1, const vector<char> op2)
	{
		int len1 = op1.size();
		int len2 = op2.size();
		if (len1 > len2)
			return true;
		else
		{
			if (len1 < len2)
				return false;
		}
		for (int i = 0; i < len1; ++i)
		{
			if (op1[i] > op2[i])
				return true;
			else
				if (op1[i] < op2[i])
					return false;
		}
		return true;
	}//大于等于
	bool greater(const vector<char> op1, const vector<char> op2)
	{
		int len1 = op1.size();
		int len2 = op2.size();
		int pos1 = -1, pos2 = -1;
		for (int i = 0; i < len1; ++i)
		{
			if (op1[i] == '.')
			{
				pos1 = i; break;
			}
		}
		for (int j = 0; j < len2; ++j)
		{
			if (op2[j] == '.')
			{
				pos2 = j; break;
			}
		}
		if (pos1 == -1)
			pos1 = len1;
		if (pos2 == -1)
			pos2 = len2;
		if (pos1 > pos2)
			return true;
		if (pos1 < pos2)
			return false;
		int k;
		for (k = 0; k < len1 && k < len2; ++k)
		{
			if (op1[k] < op2[k])
				return false;
			else
				if (op1[k] > op2[k])
					return true;
		}
		if (k < len1)
		{
			int flag = false;
			for (int i = k; i < len1; ++i)
			{
				if (op1[i] == '0' || op1[i] == '.')
					continue;
				else
				{
					flag = true; break;
				}
			}
			return flag;
		}
		else
			return false;
	}//严格大于
	void makeUp(vector<char>& op1, vector<char>& op2)
	{
		int len1 = op1.size();
		int len2 = op2.size();
		int pos1 = -1, pos2 = -1;
		for (int i = 0; i < len1; ++i)
		{
			if (op1[i] == '.')
			{
				pos1 = i; break;
			}
		}
		for (int j = 0; j < len2; ++j)
		{
			if (op2[j] == '.')
			{
				pos2 = j; break;
			}
		}

		if (pos1 == -1)
		{
			pos1 = len1;
			op1.push_back('.');
		}
		if (pos2 == -1)
		{
			pos2 = len2;
			op2.push_back('.');
		}
		{
			int after1 = op1.size() - 1 - pos1;
			int after2 = op2.size() - 1 - pos2;
			if (pos1 > pos2)
			{
				for (int k = 0; k < pos1 - pos2; ++k)
				{
					op2.insert(op2.begin(), '0');
				}
			}
			else
			{
				if (pos1 < pos2)
				{
					for (int k = 0; k < pos2 - pos1; ++k)
					{
						op1.insert(op1.begin(), '0');
					}
				}
			}
			if (after1 > after2)
			{
				for (int k = 0; k < after1 - after2; ++k)
				{
					op2.push_back('0');
				}
			}
			else
			{
				if (after1 < after2)
				{
					for (int k = 0; k < after2 - after1; ++k)
					{
						op1.push_back('0');
					}
				}
			}
		}
	}
	vector<char> add(const vector<char> op1, const vector<char> op2)
	{
		vector<char> oper1 = op1;
		vector<char> oper2 = op2;
		vector<char> res;
		makeUp(oper1, oper2);
		int len = oper1.size();
		res.reserve(len + 1);
		int carry = 0, result;
		for (int i = len - 1; i >= 0; --i)
		{
			if (oper1[i] == '.')
			{
				res.insert(res.begin(), '.'); continue;
			}
			result = oper1[i] - '0' + oper2[i] - '0' + carry;
			res.insert(res.begin(), result % 10 + '0');
			carry = result / 10;
		}
		if (carry != 0)
			res.insert(res.begin(), carry + '0');//
		int len1 = res.size();
		for (int i = len1 - 1; i > 0; --i)
		{
			if (res[i] == '0')
				res.pop_back();
			else if (res[i] == '.')
			{
				res.pop_back(); break;
			}
			else
			{
				break;
			}

		}//
		return res;
	}
	vector<char> sub(const vector<char> op1, const vector<char> op2)
	{
		vector<char> res;
		if (op1 == op2)
		{
			res.push_back('0');
			return res;
		}
		vector<char> oper1 = op1;
		vector<char> oper2 = op2;
		makeUp(oper1, oper2);
		int len = oper1.size();
		res.reserve(len + 1);
		int minus = 0, result;
		for (int i = len - 1; i >= 0; --i)
		{
			if (oper1[i] == '.')
			{
				res.insert(res.begin(), '.'); continue;
			}
			result = oper1[i] - oper2[i] - minus;
			if (result < 0)
			{
				result += 10;
				minus = 1;
			}
			else
				minus = 0;
			res.insert(res.begin(), result + '0');
		}
		while (res.size() >= 2 && (res[0] == '0' && res[1] != '.'))
			res.erase(res.begin());
		int len1 = res.size();
		for (int i = len1 - 1; i > 0; --i)
		{
			if (res[i] == '0')
				res.pop_back();
			else if (res[i] == '.')
			{
				res.pop_back(); break;
			}
			else
			{
				break;
			}

		}
		return res;
	}
	vector<char> multi(const vector<char> op1, const vector<char> op2)
	{
		int len1 = op1.size();
		int len2 = op2.size();
		int i, j, k, tmp;
		/*if ((len1 == 1 && op1[0] == '0') || (len2 == 1 && op2[0] == '0'))
		{
			vector<char> tmp(1, '0');
			return tmp;
		}*/
		vector<int> res(len1 + len2 - 1, 0);
		for (i = 0; i < len1; ++i)
		{
			k = i;
			for (j = 0; j < len2; ++j)
			{
				res[k++] += (op1[i] - '0') * (op2[j] - '0');
			}
		}
		for (k = res.size() - 1; k >= 0; --k)
		{
			if (res[k] > 9)
			{
				if (k != 0)
				{

					res[k - 1] += res[k] / 10;
					res[k] %= 10;
				}
				else   //如果是第一项大于9则添加一项于头部
				{
					tmp = res[k] / 10;
					res[k] %= 10;
					res.insert(res.begin(), tmp);
				}
			}
		}
		vector<char> result;
		int lenRes = res.size();
		result.reserve(lenRes);
		for (int cnt = 0; cnt < lenRes; ++cnt)
		{
			result.push_back(res[cnt] + '0');
		}
		return result;
	}//正整数相乘
	vector<char> div(const vector<char> op1, const vector<char> op2)
	{
		vector<char> res, t10;
		vector<char> t1 = op1;
		vector<char> t2 = op2;
		int cnt = 0;
		if (op2.size() == 1 && op2[0] == '0')
		{
			cout << "error";
			exit(-1);
		}
		if (op2.size() == 3 && op2[0] == '0' && op2[1] == '.' && op2[2] == '0')
		{
			cout << "error";
			exit(-1);
		}
		if (op1.size() == 1 && op1[0] == '0')
		{
			res.push_back('0');
			return res;
		}
		if (op1.size() == 3 && op1[0] == '0' && op1[1] == '.' && op1[2] == '0')
		{
			res.push_back('0');
			return res;
		}
		if (op1 == op2)
		{
			res.push_back('1');
			return res;
		}
		res.reserve(max);
		t10.reserve(2 * t1.size());
		bool flag = false;

		while (res.size() <= max)
		{
			if (t1[0] == '0')
			{
				break;
			}
			t10 = t1;
			t10.push_back('0');
			while (!intGreater(t1, t2) && !intGreater(t10, t2))
			{
				if (flag == false)
				{
					res.push_back('.');
					flag = true;
				}
				t1.push_back('0');
				res.push_back('0');
				t10 = t1;
				t10.push_back('0');
			}
			if (!intGreater(t1, t2) && intGreater(t10, t2))
			{
				if (flag == false)
				{
					res.push_back('.');
					flag = true;
				}
				t1.push_back('0');
			}
			int temp = 0;
			int la = t1.size();
			int lb = t2.size();
			int dv = la - lb;
			for (int i = 0; i < dv; ++i)
				t2.push_back('0');
			if (!intGreater(t1, t2))
				t2.pop_back();
			while (intGreater(t1, t2))
			{
				t1 = intSub(t1, t2);
				temp++;
			}
			cnt = t2.size() - lb;
			for (int i = 0; i < cnt; ++i)
				t2.pop_back();
			if (temp != 0)
			{
				if (res.size() > cnt + 1 && flag == false)
				{
					for (int i = 0; i < cnt + 1; ++i)
					{
						res.pop_back();
					}
				}
				res.push_back(temp + '0');
				if (flag == false)
				{
					for (int i = 0; i < cnt; ++i)
					{
						res.push_back('0');
					}
				}
				temp = 0;
			}
		}
		if (res[0] == '.')
		{
			res.insert(res.begin(), '0');
		}
		while (res.size() > max)
		{
			res.pop_back();
		}
		return res;
	}
public:
	Expression(Number v1, Number v2)
	{
		op1 = v1;
		op2 = v2;
	}
	Number add()
	{
		Number c;
		if (op1.returnAdd() == true || op2.returnAdd() == true)
		{
			c.changeAdd();
		}
		vector<char> temp;
		temp.reserve(op1.getNum().size() + 1);
		if (op1.getNum()[0] != '-' && op2.getNum()[0] != '-')
		{
			vector<char> t1 = op1.getNum();
			vector<char> t2 = op2.getNum();
			//makeUp(t1, t2);
			temp = add(t1, t2);
			c.makeNumber(temp);
			return c;
		}
		if (op1.getNum()[0] == '-' && op2.getNum()[0] == '-')
		{

			op1.getNum().erase(op1.getNum().begin());
			op2.getNum().erase(op2.getNum().begin());
			temp = add(op1.getNum(), op2.getNum());
			if (!checkZero(temp))
			{
				temp.insert(temp.begin(), '-');
			}
			c.makeNumber(temp);
			return c;
		}
		if (op1.getNum()[0] == '-' && op2.getNum()[0] != '-')
		{
			vector<char> t1 = op1.getNum();
			vector<char> t2 = op2.getNum();
			t1.erase(t1.begin());
			if (greater(t1, t2))
			{
				temp = sub(t1, t2);
				temp.insert(temp.begin(), '-');
			}
			else
			{
				temp = sub(t2, t1);
			}
			c.makeNumber(temp);
			return c;
		}
		if (op1.getNum()[0] != '-' && op2.getNum()[0] == '-')
		{
			vector<char> t1 = op1.getNum();
			vector<char> t2 = op2.getNum();
			t2.erase(t2.begin());
			if (greater(t1, t2))
			{
				temp = sub(t1, t2);
			}
			else
			{
				temp = sub(t2, t1);
				if (temp.size() == 1 && temp[0] == '0') {}
				else
					temp.insert(temp.begin(), '-');
			}
			c.makeNumber(temp);
			return c;
		}
	}
	Number reduce()
	{
		Number c, t;

		if (op1.getNum() == op2.getNum())
		{
			vector<char> tmp;
			tmp.push_back('0');
			c.makeNumber(tmp);
			return c;
		}
		vector<char> temp = op2.getNum();
		if (temp[0] == '-')
		{
			temp.erase(temp.begin());
			t.makeNumber(temp);
		}
		else
		{
			temp.insert(temp.begin(), '-');
			t.changeAdd();
			t.makeNumber(temp);

		}
		Expression tmp(op1, t);
		c = tmp.add();
		return c;
	}
	Number multiply()
	{
		bool ispositive = true;
		int pos1 = 0, pos2 = 0;
		if (op1.getNum()[0] == '-' && op2.getNum()[0] != '-')
		{
			op1.getNum().erase(op1.getNum().begin());
			if (checkZero(op1.getNum()))
				ispositive = true;
			else
				ispositive = false;
		}
		else
			if (op1.getNum()[0] != '-' && op2.getNum()[0] == '-')
			{
				op2.getNum().erase(op2.getNum().begin());
				if (checkZero(op2.getNum()))
					ispositive = true;
				else
					ispositive = false;
			}
			else
			{
				if (op1.getNum()[0] == '-' && op2.getNum()[0] == '-')
				{
					op1.getNum().erase(op1.getNum().begin());
					op2.getNum().erase(op2.getNum().begin());
				}
			}
		int len1 = op1.getNum().size();
		int len2 = op2.getNum().size();
		vector<char> oper1, oper2;
		oper1.reserve(len1);
		oper2.reserve(len2);
		for (int i = 0; i < len1; ++i)
		{
			if (op1.getNum()[i] == '.')
			{
				pos1 = i;
				continue;
			}
			else
			{
				oper1.push_back(op1.getNum()[i]);
			}
		}
		for (int j = 0; j < len2; ++j)
		{
			if (op2.getNum()[j] == '.')
			{
				pos2 = j;
				continue;
			}
			else
			{
				oper2.push_back(op2.getNum()[j]);
			}
		}
		while (oper1.size() > 1 && oper1[0] == '0')
			oper1.erase(oper1.begin());
		while (oper2.size() > 1 && oper2[0] == '0')
			oper2.erase(oper2.begin());
		int after1 = (pos1 == 0) ? 0 : len1 - 1 - pos1;
		int after2 = (pos2 == 0) ? 0 : len2 - 1 - pos2;
		vector<char> res;
		res.reserve(oper1.size() + oper2.size());
		res = multi(oper1, oper2);
		vector<char> result;
		int lenRes = res.size();
		if (lenRes - after1 - after2 < 0)
		{
			for (int i = 0; i < after1 + after2 - lenRes; ++i)
			{
				res.insert(res.begin(), '0');
			}
		}
		lenRes = res.size();
		result.reserve(lenRes + 1);
		for (int i = lenRes - 1; i >= lenRes - after1 - after2; --i)
		{
			result.insert(result.begin(), res[i]);
		}
		result.insert(result.begin(), '.');
		for (int i = lenRes - after1 - after2 - 1; i >= 0; --i)
		{
			result.insert(result.begin(), res[i]);
		}
		int lenResult = result.size();
		for (int i = lenResult - 1; i > 0; --i)
		{
			if (result[i] == '0')
				result.pop_back();
			else if (result[i] == '.')
			{
				result.pop_back(); break;
			}
			else
			{
				break;
			}
		}
		while (result.size() >= 2 && (result[0] == '0' && result[1] != '.'))
			result.erase(result.begin());
		if (result[0] == '.')
			result.insert(result.begin(), '0');
		if (!ispositive)
		{
			result.insert(result.begin(), '-');
		}
		if (checkZero(result))
		{
			result.clear();
			result.push_back('0');
		}
		Number c;
		c.makeNumber(result);
		return c;
	}
	Number divide()
	{
		int len1 = op1.getNum().size();
		int len2 = op2.getNum().size();
		for (int i = 0; i < len1; ++i)
		{
			if (op1.getNum()[i] == '.')
			{
				cout << "error";
				exit(-1);
			}
		}
		for (int j = 0; j < len2; ++j)
		{
			if (op2.getNum()[j] == '.')
			{
				cout << "error";
				exit(-1);
			}
		}
		vector<char> t1 = op1.getNum();
		vector<char> t2 = op2.getNum();
		bool ispositive = true;
		if (t1[0] == '-' && t2[0] == '-')
		{
			t1.erase(t1.begin());
			t2.erase(t2.begin());
		}
		else
		{
			if (t1[0] == '-' && t2[0] != '-')
			{
				if (t1.size() == 2 && t1[1] == '0')
					ispositive = true;
				else
					ispositive = false;
				t1.erase(t1.begin());

			}
			else
			{
				if (t1[0] != '-' && t2[0] == '-')
				{
					t2.erase(t2.begin());
					ispositive = false;
				}
			}
		}
		vector<char> result;
		result.reserve(max);
		result = div(t1, t2);
		if (!ispositive)
			result.insert(result.begin(), '-');
		while (result.size() > max)
		{
			result.pop_back();
		}
		if (result.back() == '.')
			result.pop_back();
		{
			while (result.size() > 2 && (result[0] == '0' && result[1] != '.'))
				result.erase(result.begin());
			int lenResult = result.size();
			int posOfDot = -1;
			for (int i = 0; i < lenResult; ++i)
			{
				if (result[i] == '.')
				{
					posOfDot = i; break;
				}
			}
			if (posOfDot == -1)
				posOfDot = lenResult;
			for (int i = lenResult - 1; i > posOfDot; --i)
			{
				if (result[i] == '0')
					result.pop_back();
				else if (result[i] == '.')
				{
					result.pop_back(); break;
				}
				else
				{
					break;
				}

			}
			if (result.size() == 2 && result[0] == '-' && result[1] == '0')
				result.erase(result.begin());
		}
		Number c;
		c.makeNumber(result);
		return c;
	}
};


//定义main函数
int main()
{
	//ifstream in;
	//in.open("fin0.txt");
	string str;          //测试输入数据存放变量
    getline(cin, str);    //读取测试输入，并存入str
   /********** Begin **********/
	//while (in >> str)
	//{
		vector<char> op1;
		vector<char> op2;
		op1.reserve(max);
		op2.reserve(max);
		char curr;
		int len = str.length(), i = 0, flag;
		while (i < len && str[i] != '<')
		{
			curr = str[i];
			if (curr <= '9' && curr >= '0')
				op1.push_back(curr);
			else
			{
				if (curr == '-' || curr == '.')
					op1.push_back(curr);
				else
				{
					cout << "error";
					exit(-1);
				}
			}
			i++;
		}
		if (i >= len)
		{
			cout << "error";
			exit(-1);
		}
		curr = str[++i];
		switch (curr)
		{
		case '+': {flag = 1; break; }
		case '-': {flag = 2; break; }
		case '*': {flag = 3; break; }
		case '/': {flag = 4; break; }
		default:
		{
			cout << "error";
			exit(-1);
		}
		}
		curr = str[++i];
		if (curr != '>')
		{
			cout << "error";
			exit(-1);
		}
		i++;
		while (i < len)
		{
			curr = str[i];
			if (curr <= '9' && curr >= '0')
				op2.push_back(curr);
			else
			{
				if (curr == '-' || curr == '.')
					op2.push_back(curr);
				else
				{
					cout << "error";
					exit(-1);
				}
			}
			i++;
		}
		Number res, a, b;
		a.makeNumber(op1);
		b.makeNumber(op2);
		Expression result(a, b);
		switch (flag)
		{
		case 1: {res = result.add(); break; }
		case 2: {res = result.reduce(); break; }
		case 3: {res = result.multiply(); break; }
		case 4: {res = result.divide(); break; }
		default:
			break;
		}
		//请打印输出运算结果，输出结果时无需换行
		cout << res;
		//cout << endl;
	//}
	/********** End **********/
	return 0;
}
