#include <iostream>
#include"std_lib_facilities.h"
#include"Newton.h"
#include "LinearEquations.h"
using namespace std;

int main()
{
	bool exercise1 = true;
	if (exercise1) 
	{
		string str;
		getline(cin, str);
		double a, b;
		cin >> a >> b;
		Polynomial p(str);
		if (!p.checkNewton(a, b))
		{
			cout << "error";
			return -1;
		}
		else
		{
			double ret = p.Newton(b);
			cout << p.format(ret);
		}
		return 0;
	}
	else 
	{
		LinearEquations e;
		string str;
		while (getline(cin, str))
		{
			e.getEqua(str);
		}
		e.output();
		return 0;
	}
}

