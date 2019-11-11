#include<iostream>
#include<string>
using namespace std;

//template<class elemType>
class hfTree
{
private:
	struct node
	{
		char value;
		int weight;
		int parent, left, right;
	};
	node* elem;
	int length;
public:
	struct hfCode
	{
		char data;
		string code;
	};
	hfTree(char* x, int* w, int size);
	~hfTree() { delete elem; }
	void getCode();
	void getcode(hfCode result[])
	{
		int size = length / 2;
		int p, s;
		for (int i = size; i < length; ++i)
		{
			result[i - size].data = elem[i].value;
			result[i - size].code = "";
			p = elem[i].parent;
			s = i;
			while (p)
			{
				if (elem[p].left == s)
					result[i - size].code = '0' + result[i - size].code;
				else
					result[i - size].code = '1' + result[i - size].code;;
				s = p;
				p = elem[p].parent;
			}
		}
	}
};


#include "Huffman_Exercise_1.h"
#include"std_lib_facilities.h"
#include<stack>


using namespace std;

//template<class elemType>
hfTree/*<elemType>*/::hfTree(char* x, int* w, int size)
{
	const int MAX_INT = 32767;
	elem = new node[2 * size];
	length = 2 * size;
	int min1, min2, index1, index2;

	for (int i = size; i < 2 * size; ++i)
	{
		elem[i].value = x[i - size];
		elem[i].weight = w[i - size];
		elem[i].parent = elem[i].left = elem[i].right = 0;
	}

	for (int i = size - 1; i > 0; --i)
	{
		min1 = min2 = MAX_INT;
		index1 = index2 = 0;
		for (int j = i + 1; j < 2 * size; ++j)
		{
			if (elem[j].parent == 0)
			{
				if (elem[j].weight < min1)
				{
					min2 = min1;
					min1 = elem[j].weight;
					index2 = index1;
					index1 = j;
				}
				else
				{
					if (elem[j].weight < min2)
					{
						min2 = elem[j].weight;
						index2 = j;
					}
				}
			}

		}
		elem[i].weight = min1 + min2;
		elem[i].left = index1;
		elem[i].right = index2;
		elem[i].parent = 0;
		elem[index1].parent = i;
		elem[index2].parent = i;
	}
}

//template<class elemType>
void hfTree/*<elemType>*/:: getCode()
 {
     int size = length/2;
     stack<int> s;
     for(int i = size;i < 2*size;++i)
     {
         int j = i;
         while(elem[j].parent != 0)
         {
             int k = elem[j].parent;
             if(elem[k].left == j)
                s.push(0);
             if(elem[k].right == j)
                s.push(1);
             j = k;
         }
     }
 }


int main()
{
     string str1;
	string str2;
	int cnt = 0;
	while (getline(cin, str2))
	{
		cnt++;
		str1 += str2;
	}
	for (int i = 0; i < cnt - 1; ++i)
	{
		str1 += '\n';
	}
	unordered_map<char, int> wordMap;
	for(int i = 0;i < str1.size();++i)
	{
		char temp = str1[i];
		if (wordMap.find(temp) == wordMap.end())
		{
			wordMap[temp] = 1;
		}
		else
			wordMap[temp]++;
	}

	vector<pair<int, char>> freq;
	for (auto it = wordMap.begin(); it != wordMap.end(); ++it)
	{
		freq.push_back(make_pair(it->second, it->first));
	}
	sort(freq.begin(),freq.end());
	int len = freq.size();
	int* w = new int[len];
	char* t = new char[len];
	for (int i = 0; i < len; ++i)
	{
		t[i] = freq[i].second;
		w[i] = freq[i].first;
	}

	hfTree::hfCode* result = new hfTree::hfCode[len];
	hfTree hf(t, w, len);
	hf.getCode();
	hf.getcode(result);
	int sum = 0;
	for (int i = 0; i < len; ++i)
	{
		sum += result[i].code.size() * wordMap[result[i].data];
	}
	cout << sum;
    return 0;
}