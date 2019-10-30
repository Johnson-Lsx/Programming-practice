#pragma once
#include "std_lib_facilities.h"
#include<unordered_map>
using namespace std;

class Token {
private:
	unordered_map<string, vector<string>> V;
	vector<pair<string, int>> Top5;//存储词频最高的前五单词
	int count;//存储总词数
	string text;//存储传进来的文本
	vector<string> requried;//存储需要被输出的单词
	unordered_map<string, int> WordMap;//用来统计词频
	bool isword(char ch);//判断一个字符是不是一个单词
	bool validWord(string str);//判断一个字符串是不是一个单词
	void change();//将标点改为空格
public:
	Token(const string str1, const string str2);
	void Fre();
	void strcmp_sort();//找到词频最高的前五
	void print();//按格式要求输出
	int Count() { return count; }//返回count
};

#include "Token.h"
void Token::print()
{
	Fre();
	strcmp_sort();
	cout << count << endl;
	for (int i = 0; i < Top5.size() - 1; ++i)
	{
		cout << "(" << Top5[i].first << "," << Top5[i].second << ")" << " ";
	}
	cout << "(" << Top5.back().first << "," << Top5.back().second << ")";
	cout << endl;
	for (int i = 0; i < requried.size(); ++i)
	{
		string temp = requried[i];
		if (!validWord(temp))
			continue;
		for (int i = 0; i < temp.size(); ++i)
		{
			if (temp[i] >= 'A' && temp[i] <= 'Z')
			{
				temp[i] += 32;
			}
		}
		if (WordMap.find(temp) != WordMap.end())
		{
			cout << "(" << requried[i] << "," << WordMap[temp] << ")";
			if (i != requried.size() - 1)
				cout << " ";
		}
		else
		{
			cout << "(" << requried[i] << "," << 0 << ")";
			if (i != requried.size() - 1)
				cout << " ";
		}
	}
}
void Token::strcmp_sort()
{
	vector<pair<int, string>> v;//将WordMap装进线性容器，便于sort()函数使用
	for (auto it = WordMap.begin(); it != WordMap.end(); ++it)
	{
		vector<string> rep = V.find(it->first)->second;//rep代表的是同一个单词在文中出现过的所有形式（大小写）
		sort(rep.begin(), rep.end());//按照字典序对单词出现形式排序，选择最大的
		v.push_back(make_pair(it->second, rep.back()));//将单词的代表形式和对应词频加入v中
	}
	sort(v.begin(), v.end());//按照词频高低排序，但是是升序排列
	int max = v.back().first;//最高词频
	int min = v.front().first;//最低词频
	vector<vector<pair<string, int>>> groups(max - min + 2);//用于存储相同词频的单词，便于按照字典序升序输出
	for (int i = v.size() - 1; i >= 0; --i)
	{
		groups[v[i].first - min + 1].push_back(make_pair(v[i].second, v[i].first));
		//v[i].first表示v[i].second出现次数，v[i].first - min + 1就对应到了相应的groups的下标
	}
	int cnt = 5;//表示只需要前面五个最高词频
	for (int i = groups.size() - 1; i >= 0; --i)
	{
		sort(groups[i].begin(), groups[i].end());//对词频相同的单词，按字典序排序
	}
	for (int i = groups.size() - 1; i >= 0; --i)
	{
		while (cnt > 0 && !groups[i].empty())
		{
			Top5.push_back(groups[i].front());//将最高词频的前五个加入Top5
			groups[i].erase(groups[i].begin());
			cnt--;
		}
	}
}

bool Token::isword(char ch)
{
	if ((ch > 'z' || ch < 'a') && (ch > 'Z' || ch < 'A') && (ch < '0' || ch > '9'))
		return false;
	else
		return true;
}

bool Token::validWord(string str)
{
	for (int i = 0; i < str.size(); ++i)
	{
		if (isword(str[i]))
		{
			return true; break;
		}
	}
	return false;
}

void Token::change()
{
	string temp = text;
	int i;
	for (i = 0; i < text.size() - 1; ++i)
	{
		if (!isword(text[i]))
		{
			if (text[i] == '-' || text[i] == '_')
			{
				if (i == 0 && isword(temp[i + 1]))
				{
					text[i] = ' ';
					continue;
				}
				else
				{
					if ((isword(temp[i + 1])|| temp[i +1] == ' ' )&& isword(temp[i - 1]))//有改动 || temp[i +1] == ' '
						continue;
				}
			}
			text[i] = ' ';
		}
	}
	/*if (!isword(text[i]))
		text[i] = ' ';*/
	if (!isword(text[i]))
	{
		if (text[i] == '-' || text[i] == '_')
		{
			if (!isword(temp[i - 1]))
				text[i] = ' ';
		}
		else
			text[i] = ' ';
	}
}

Token::Token(const string str1, const string str2)
{
	count = 0;
	text = str1;
	change();
	if (text.empty())
	{
		exit(-1);
	}
	stringstream is2(str2);
	string temp;
	while (is2 >> temp)
	{
		requried.push_back(temp);
	}
	stringstream is1(text);
	while (is1 >> temp)
	{
		count++;
	}
}
void Token::Fre()
{
	stringstream is1(text);
	string temp = text;
	string word;
	vector<string> ori;//存储原来的单词
	vector<string> lowc;//存储全部转化为小写字母后的单词
	while (is1 >> word)
	{
		ori.push_back(word);
	}
	for (int i = 0; i < temp.size(); ++i)//将所有的大写字母变为小写字母
	{
		if (temp[i] >= 'A' && temp[i] <= 'Z')
		{
			temp[i] += 32;
		}
	}
	stringstream is(temp);
	while (is >> word)
	{
		lowc.push_back(word);
	}
	for (int i = 0; i < lowc.size(); ++i)//进行词频统计
	{
		if (WordMap.find(lowc[i]) == WordMap.end())//之前没遇到过的
		{
			WordMap[lowc[i]] = 1;
			vector<string> t;
			t.push_back(ori[i]);//将原来大小写都有的单词添加到V中
			V[lowc[i]] = t;
		}
		else//之前已经遇到过的
		{
			WordMap[lowc[i]]++;
			auto it = V.find(lowc[i]);
			it->second.push_back(ori[i]);
		}
	}
}

