#include"hyperelliptic.h"
#include"std_lib_facilities.h"
#include"Simple_window.h"
#include"Graph.h"
#include<iostream>
using namespace Graph_lib;
using namespace std;
int main()
{
	void ex1();
	ex1();
	return 0;
}
void ex1()
{
	Simple_window win(Point(100, 100), 1000, 800, "hyperelliptic");
	double a, b, m, n;
	int N;
	cin >> a >> b >> m >> n;
	cin >> N;
	hyperelliptic h(a, b, m, n, N);
	h.draw();
	win.attach(h);
	win.wait_for_button();
}