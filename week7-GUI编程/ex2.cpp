Simple_window win(Point(100, 100), 600, 600, "righttriangle");
	righttriangle tr1(50 * sqrt(2), 0, 0, 50 * sqrt(2), 50 * sqrt(2), 50 * sqrt(2), 50 * sqrt(2), 50 * sqrt(2));
	tr1.draw_lines();
	tr1.set_color(Color(1));

	righttriangle tr2(50 * sqrt(2), 0, 100 + 50 * sqrt(2), 0, 50 + 50 * sqrt(2), 50, 50 * sqrt(2), 50 * sqrt(2));
	tr2.draw_lines();
	tr2.set_color(Color(2));

	righttriangle tr3(100 + 50 * sqrt(2), 0, 100 + 50 * sqrt(2), 50 * sqrt(2), 100 + 100 * sqrt(2), 50 * sqrt(2), 50 * sqrt(2), 50 * sqrt(2));
	tr3.draw_lines();
	tr3.set_color(Color(3));

	righttriangle tr4(100 + 100 * sqrt(2), 50 * sqrt(2), 100 + 100 * sqrt(2), 50 * sqrt(2) + 100, 50 + 100 * sqrt(2), 50 + 50 * sqrt(2), 50 * sqrt(2), 50 * sqrt(2));
	tr4.draw_lines();
	tr4.set_color(Color(4));

	righttriangle tr5(100 + 100 * sqrt(2), 50 * sqrt(2) + 100, 100 + 50 * sqrt(2), 50 * sqrt(2) + 100, 100 + 50 * sqrt(2), 100 * sqrt(2) + 100, 50 * sqrt(2), 50 * sqrt(2));
	tr5.draw_lines();
	tr5.set_color(Color(5));

	righttriangle tr6(100 + 50 * sqrt(2), 100 * sqrt(2) + 100, 50 * sqrt(2), 100 * sqrt(2) + 100, 50 + 50 * sqrt(2), 100 * sqrt(2) + 50, 50 * sqrt(2), 50 * sqrt(2));
	tr6.draw_lines();
	tr6.set_color(Color(6));

	righttriangle tr7(50 * sqrt(2), 100 * sqrt(2) + 100, 50 * sqrt(2), 50 * sqrt(2) + 100, 0, 100 + 50 * sqrt(2), 50 * sqrt(2), 50 * sqrt(2));
	tr7.draw_lines();
	tr7.set_color(Color(7));

	righttriangle tr8(0, 50 * sqrt(2), 0, 100 + 50 * sqrt(2), 50, 50 + 50 * sqrt(2), 50 * sqrt(2), 50 * sqrt(2));
	tr8.draw_lines();
	tr8.set_color(Color(8));

	win.attach(tr1);
	win.attach(tr2);
	win.attach(tr3);
	win.attach(tr4);
	win.attach(tr5);
	win.attach(tr6);
	win.attach(tr7);
	win.attach(tr8);
	win.wait_for_button();
