virtual void draw1()
	{
		for (int i = 0; i < cent.size(); ++i)
		{
				fl_arc(cent[i].x, cent[i].y, r + r, r + r, 0, 360);
		}
		for (int i = 0; i < cent.size(); ++i)
		{
			if (2 * i + 1 < cent.size())
			{
				Graph_lib::Lines::add(cent[i],cent[2 * i + 1]);
			}
			if (2 * i + 2 < cent.size())
			{
				Graph_lib::Lines::add(cent[i], cent[2 * i + 2]);
			}
		}
		Graph_lib::Lines::draw_lines();
		Graph_lib::Lines::set_color(Graph_lib::Color(1));
		for (int i = 0; i < number_of_points(); ++i)
		{
			if (color().visibility())
				fl_arc(point(i).x, point(i).y, r + r, r + r, 0, 360);
		}
	}