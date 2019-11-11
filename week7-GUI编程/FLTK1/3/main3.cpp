#include"Binary_tree.h"
#include"TriangleBinary_tree.h"
#include"std_lib_facilities.h"
#include"Simple_window.h"
#include"Graph.h"
#include<iostream>
using namespace Graph_lib;
using namespace std;
int main()
{
	void ex3();
	void ex4();
    ex3();
	//ex4();
	return 0;
}
void ex3()
{
	Simple_window win(Point(100, 100), 1000, 800, "Binary_tree");
	int n;
	cin >> n;
	Binary_tree b(n);
	b.getCenters(0, win.x_max(), 0, n);
	b.drawNodes(win);
}
void ex4()
{
	Simple_window win(Point(100, 100), 1000, 800, "TriangleBinary_tree");
	int n;
	cin >> n;
	TriangleBinary_tree tt(n);
	tt.getCenters(0, win.x_max(), 0, n);
	tt.drawNodes(win);
}