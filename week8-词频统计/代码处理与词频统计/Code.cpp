#pragma once
#include"std_lib_facilities.h"
#include<unordered_map>
class Code
{
private:
	unordered_map<string, int> keyWords;//存储关键字
	vector<string> code;//按行存储代码
	unordered_map<string,int> identifier;//存储标识符
	bool isPun(char ch);//判断是不是无关的符号
	bool startCom1(string str);//判断是不是字符串是不是含有注释符 //
	bool startCom2(string str);//判断是不是字符串是不是含有注释符/*
	bool endCom(string str);//判断是不是字符串是不是含有注释符 */
	bool isTran(string str);
	void change(vector<string>& v);
	void cleanCode(string& str);
	void process();
public:
	Code();//为keyWords赋值
	void input();//获得代码
	void output();//输出
};

#include "Code.h"

bool Code::isPun(char ch)
{
	if (ch == '\\' || ch == '_' || ch == '/' || ch == '*' || (ch <= '9' && ch >= '0') || (ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A'))
		return false;
	else
		return true;
}

//判断是不是字符串是不是含有注释符 //
bool Code::startCom1(string str)
{
	if (str == "//")
		return true;
	for (int i = 0; i < str.size() - 1; ++i)
	{
		if (str[i] == '/' && str[i + 1] == '/')
			return true;
	}
	return false;
}

//判断是不是字符串是不是含有注释符/*
bool Code::startCom2(string str)
{
	if (str == "/*")
		return true;
	for (int i = 0; i < str.size() - 1; ++i)
	{
		if (str[i] == '/' && str[i + 1] == '*')
			return true;
	}
	return false;
}

//判断是不是字符串是不是含有注释符*/
bool Code::endCom(string str)
{
	if (str == "*/")
		return true;
	for (int i = 0; i < str.size() - 1; ++i)
	{
		if (str[i] == '*' && str[i + 1] == '/')
			return true;
	}
	return false;
}

bool Code::isTran(string str)
{
	if (str == "\n")
		return true;
	return false;
}

void Code::change(vector<string>& v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		for (int j = 0; j < v[i].size(); ++j)
		{
			if (isPun(v[i][j]))
				v[i][j] = ' ';
		}
	}
}

void Code::cleanCode(string& str)
{
	if (!startCom1(str) && !startCom2(str) && !endCom(str))
	{
		for (int i = 0; i < str.size(); ++i)
		{
			char ch = str[i];
			if ((ch > '9' || ch < '0') && (ch > 'z' || ch < 'a') && (ch > 'Z' || ch < 'A') && ch != '_')
				str[i] = ' ';
		}
		stringstream is(str);
		string temp;
		is >> temp;
		str = temp;
	}
}


Code::Code()
{
	vector<string> v;
	v.push_back("alignas alignof and and_eq");
	v.push_back("asm	atomic_cancel	atomic_commit	atomic_noexcept");
	v.push_back("auto	bitand	bitor	bool");
	v.push_back("break	case	catch	char");
	v.push_back("char8_t	char16_t	char32_t	class");
	v.push_back("compl	concept	const	consteval");
	v.push_back("constexpr	constinit	const_cast	continue");
	v.push_back("co_await	co_return	co_yield	decltype");
	v.push_back("default	define	defined	delete");
	v.push_back("do	double	dynamic_cast	elif");
	v.push_back("else	error	endif	enum");
	v.push_back("explicit	export	extern	false");
	v.push_back("final	float	for	friend");
	v.push_back("goto	if	ifdef	ifndef");
	v.push_back("import	include	inline	int");
	v.push_back("line	long	module	mutable");
	v.push_back("namespace	new	noexcept	not");
	v.push_back("not_eq	nullptr	operator	or");
	v.push_back("or_eq	override	pragma	private");
	v.push_back("protected	public	reflexpr	register");
	v.push_back("reinterpret_cast	requires	return	short");
	v.push_back("signed	sizeof	static	static_assert");
	v.push_back("static_cast	struct	switch	synchronized");
	v.push_back("template	this	thread_local	throw");
	v.push_back("xor_eq true	try	typedef");
	v.push_back("typeid	typename	undef	union");
	v.push_back("unsigned	using	virtual	void");
	v.push_back("volatile	wchar_t	while	xor");
	for (int i = 0; i < v.size(); ++i)
	{
		stringstream is(v[i]);
		string kw;
		while (is >> kw)
		{
			if (keyWords.find(kw) == keyWords.end())
				keyWords[kw] = 1;
			else
				keyWords[kw]++;
		}
	}
}

void Code::input()
{
	string str1;
	while (cin)
	{
		getline(cin, str1);
		code.push_back(str1);
	}
}

void Code::process()
{
	vector<string> v = code;
	vector<pair<string, int>> v1;
	vector<string> neatCode;
	change(v);
	for (int i = 0; i < v.size(); ++i)
	{
		string temp;
		stringstream is(v[i]);
		while (is >> temp)
		{
			v1.push_back(make_pair(temp, i));
		}
	}
	bool isComment1 = false;
	bool isComment2 = false;
	for (int i = 0; i < v1.size(); ++i)
	{
		string token = v1[i].first;
		if (token == "\\n")
			continue;
		cleanCode(token);
		if (startCom1(token))
			isComment1 = true;
		if (startCom2(token))
			isComment2 = true;
		if (isComment1 == true)//用//注释的一整行跳过
		{
			int line = v1[i].second;
			while (i < v1.size() && v1[i].second == line)
				i++;
			isComment1 = false;
			i--;
			continue;
		}
		if (isComment2 == true)
		{
			while (i < v1.size() && !endCom(v1[i].first))
				i++;
			if (i == v1.size())
				exit(-1);
			isComment2 = false;
			continue;
		}
		if (keyWords.find(token) == keyWords.end() && identifier.find(token) == identifier.end())
			identifier[token] = 1;
	}
}

void Code::output()
{
	process();
	vector<string> output;
	for (auto it = identifier.begin(); it != identifier.end(); ++it)
	{
		output.push_back(it->first);
	}
	sort(output.begin(), output.end());
	for (int i = 0; i < output.size(); ++i)
	{
		cout << output[i];
		if (i != output.size() - 1)
			cout << " ";
	}
}
