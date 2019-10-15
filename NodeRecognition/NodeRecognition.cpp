#include "NodeRecognition.h"

using namespace std;
void NodeRecognition::Input(string str)
{
	if (str.size() == 2)
	{
		cout << "We have recognized 0 graph.";
		exit(1);
	}
	weight.resize(100);
	cnt = 0;
	input = str;
	int len = str.size();
	string temp = "";
	bool flag = false;
	for (int i = 0; i < len; ++i)
	{
		if (input[i] == '<')
		{
			flag = true;
			continue;
		}
		if (input[i] == ' ' && !flag)
			continue;
		if (input[i] == '>')
		{
			stringstream is(temp);
			string str1, str2;
			is >> str1;
			is >> str2;
			if (str2.empty())//说明只有单个节点
			{
				stringstream is2(temp);
				int w1;
				is2 >> w1;
				if (wiPair.find(w1) == wiPair.end())//说明w1之前没有出现
				{
					wiPair[w1] = cnt;//将w1存储进wiPair
					weight[cnt] = w1;
					cnt++;
				}
				child.push_back(wiPair[w1]);
				father.push_back(-1);
			}
			else//说明有两个节点
			{
				int w1, w2;
				stringstream is1(temp);
				is1 >> w1 >> w2;
				if (wiPair.find(w1) == wiPair.end())
				{
					wiPair[w1] = cnt;//将w1存储进wiPair
					weight[cnt] = w1;
					cnt++;
				}
				if (wiPair.find(w2) == wiPair.end())
				{
					wiPair[w2] = cnt;//将w1存储进wiPair
					weight[cnt] = w2;
					cnt++;
				}
				child.push_back(wiPair[w1]);
				father.push_back(wiPair[w2]);
			}
			temp = "";
			flag = false;
		}
		else
		{
			temp += input[i];
		}
	}
	findRoot();
}

void NodeRecognition::getDJS()
{
	parts = 0;
	vector<int> tmp(cnt, -1);
	DJS = tmp;
	for (int i = 0; i < child.size(); ++i)
	{
		if (father[i] != -1)
		{
			if (Find(child[i]) != Find(father[i]))
			{
				Union(Find(child[i]), Find(father[i]));
			}
		}
	}
	for (int i = 0; i < cnt; ++i)
	{
		if (DJS[i] < 0)
		{
			parts++;
			vector<int> temp;
			for (int j = 0; j < cnt; ++j)
			{
				if (Find(j) == i)
					temp.push_back(j);
			}
			set.push_back(temp);
		}
	}
}

int NodeRecognition::Find(int x)
{
	if (DJS[x] < 0)
		return x;
	return DJS[x] = Find(DJS[x]);
}

void NodeRecognition::Union(int root1, int root2)
{
	if (root1 == root2)
		return;
	if (DJS[root1] >= DJS[root2])
	{
		DJS[root2] += DJS[root1];
		DJS[root1] = root2;
	}
	else
	{
		DJS[root1] += DJS[root2];
		DJS[root2] = root1;
	}
}

void NodeRecognition::getAns()
{
	int count = 0;
	nodes = btrees = trees = graphs = 0;
	ret.resize(parts);
	for (int i = 0; i < parts; ++i)
	{
		ret[i].n = -1;
		ret[i].w = 0;
		ret[i].s = 0;
	}
	for (int i = 0; i < set.size(); ++i)
	{
		if (isNode(i))
		{
			ret[i].n = 1;
			ret[i].s = set[i].size();
			for (int j = 0; j < set[i].size(); ++j)
			{
				ret[i].w += weight[set[i][j]];
			}
			nodes++;
			continue;
		}
		if (isBinaryTree(i))
		{
			ret[i].n = 2;
			ret[i].s = set[i].size();
			for (int j = 0; j < set[i].size(); ++j)
			{
				ret[i].w += weight[set[i][j]];
			}
			btrees++;
			continue;
		}
		if (isTree(i))
		{
			ret[i].n = 3;
			ret[i].s = set[i].size();
			for (int j = 0; j < set[i].size(); ++j)
			{
				ret[i].w += weight[set[i][j]];
			}
			trees++;
			continue;
		}
		else {
			ret[i].n = 4;
			ret[i].s = set[i].size();
			for (int j = 0; j < set[i].size(); ++j)
			{
				ret[i].w += weight[set[i][j]];
			}
			graphs++;
		}
	}
}

bool NodeRecognition::isBinaryTree(int i)
{
	int len = set[i].size();
	int cnt1 = 0;
	for (int j = 0; j < len; ++j)
	{
		for (int k = 0; k < child.size(); ++k)
		{
			if (child[k] == set[i][j])
			{
				if (father[k] == -1)
					cnt1++;
			}
		}
	}
	if (cnt1 != 1)
		return false;
	for (int j = 0; j < len; ++j)
	{
		int cnt2 = 0;
		for (int k = 0; k < child.size(); ++k)
		{
			if (child[k] == set[i][j])
			{
				cnt2++;
			}
		}
		if (cnt2 > 1)
			return false;
	}
	for (int j = 0; j < len; ++j)
	{
		int cnt3 = 0;
		for (int k = 0; k < father.size(); ++k)
		{
			if (father[k] == set[i][j])
			{
				cnt3++;
			}
		}
		if (cnt3 > 2)
			return false;
	}
	return true;
}

bool NodeRecognition::isTree(int i)
{
	int len = set[i].size();
	int cnt1 = 0;
	for (int j = 0; j < len; ++j)
	{
		for (int k = 0; k < child.size(); ++k)
		{
			if (child[k] == set[i][j])
			{
				if (father[k] == -1)
					cnt1++;
			}
		}
	}
	if (cnt1 != 1)
		return false;
	for (int j = 0; j < len; ++j)
	{
		int cnt2 = 0;
		for (int k = 0; k < child.size(); ++k)
		{
			if (child[k] == set[i][j])
			{
				cnt2++;
			}
		}
		if (cnt2 > 1)
			return false;
	}
	int max = -1;
	for (int j = 0; j < len; ++j)
	{
		int cnt3 = 0;
		for (int k = 0; k < father.size(); ++k)
		{
			if (father[k] == set[i][j])
			{
				cnt3++;
			}
		}
		if (max < cnt3)
			max = cnt3;
	}
	if (max <= 2)
		return false;
	return true;
}

bool NodeRecognition::isNode(int i)
{
	if (set[i].size() == 1)
		return true;
	else
		return false;
}

void NodeRecognition::Swap(part& a, part& b)
{
	part temp;
	temp = a;
	a = b;
	b = temp;
}

void NodeRecognition::Sort()
{
	int len = ret.size();
	for (int i = 1; i < len; ++i)
	{
		for (int j = 0; j < len - i; ++j)
		{
			if (ret[j].n > ret[j + 1].n)
			{
				Swap(ret[j], ret[j + 1]);
			}
			else
			{
				if (ret[j].n == ret[j + 1].n)
				{
					if (ret[j].w > ret[j + 1].w)
					{
						Swap(ret[j], ret[j + 1]);
					}
					else
					{
						if (ret[j].w == ret[j + 1].w)
						{
							if (ret[j].s > ret[j + 1].s)
							{
								Swap(ret[j], ret[j + 1]);
							}
						}
					}
				}
			}
		}
	}
}

void NodeRecognition::findRoot()
{
	int i, j;
	for (i = 0; i < wiPair.size(); ++i)
	{
		for (j = 0; j < child.size(); ++j)
		{
			if (i == child[j])
				break;
		}
		if (j == child.size())
		{
			child.push_back(i);
			father.push_back(-1);
		}
	}
}

void NodeRecognition::Output()
{
	Sort();
	if (parts <= 1)
	{
		cout << "We have recognized " << parts << " graph." << endl;
	}
	else
	{
		cout << "We have recognized " << parts << " graphs." << endl;
	}
	for (int i = 0; i < ret.size() - 1; ++i)
	{
		switch (ret[i].n)
		{
		case 1:
		{
			cout << "--Node. Weight: " << ret[i].w << ". Size: " << ret[i].s << '.' << endl;
			break;
		}
		case 2:
		{
			cout << "--Binary tree. Weight: " << ret[i].w << ". Size: " << ret[i].s << '.' << endl;
			break;
		}
		case 3:
		{
			cout << "--Tree. Weight: " << ret[i].w << ". Size: " << ret[i].s << '.' << endl;
			break;
		}
		case 4:
		{
			cout << "--Graph. Weight: " << ret[i].w << ". Size: " << ret[i].s << '.' << endl;
		}
		}
	}
	int le = ret.size() - 1;
	switch (ret[le].n)
	{
	case 1:
	{
		cout << "--Node. Weight: " << ret[le].w << ". Size: " << ret[le].s << '.';
		break;
	}
	case 2:
	{
		cout << "--Binary tree. Weight: " << ret[le].w << ". Size: " << ret[le].s << '.';
		break;
	}
	case 3:
	{
		cout << "--Tree. Weight: " << ret[le].w << ". Size: " << ret[le].s << '.';
		break;
	}
	case 4:
	{
		cout << "--Graph. Weight: " << ret[le].w << ". Size: " << ret[le].s << '.';
	}
	}
}

int main()
{
	string str;
	getline(cin, str);
	NodeRecognition s;
	s.Input(str);
	s.getDJS();
	s.getAns();
	s.Output();
	return 0;
}