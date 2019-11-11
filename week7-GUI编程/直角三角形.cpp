class righttriangle:public Graph_lib::Polygon
{
private:
	Point a, b, c;
	double len1, len2;
	bool check()
	{
		double len1 = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
		double len2 = (a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y);
		double len3 = (b.x - c.x) * (b.x - c.x) + (b.y - c.y) * (b.y - c.y);
		if (len1 + len2 == len3)
		{
			if(len1 == this->len1* this->len1 && len2 == this->len2 * this->len2 || len1 == this->len2 * this->len2  && len2 == this->len1 * this->len1)
			return true;
		else
			return false;
		}
		if (len1 + len3 == len2)
		{
			if (len1 == this->len1 * this->len1 && len3 == this->len2 * this->len2  || len1 == this->len2 * this->len2 && len3 == this->len1 * this->len1)
				return true;
			else
				return false;
		}
		if (len3 + len2 == len1)
		{
			if (len3 == this->len1 * this->len1 && len2 == this->len2 * this->len2 || len3 == this->len2 * this->len2 && len2 == this->len1 * this->len1)
				return true;
			else
				return false;
		}
		return false;
	}
public:
	righttriangle(Point& aa,Point& bb,Point&cc,double l1,double l2):a(aa),b(bb),c(cc),len1(l1),len2(l2)
	{
		/*if (!check())
		{
			cout << "This is not a righttriangle!";
			exit(-1);
		}*/
		add(a);
		add(b);
		add(c);
	}
	righttriangle(double ax, double ay, double bx, double by, double cx, double cy, double l1, double l2) :a(ax,ay), b(bx,by), c(cx,cy), len1(l1), len2(l2)
		
	{
		/*if (!check())
		{
			cout << "This is not a righttriangle!";
			exit(-1);
		}*/
		add(a);
		add(b);
		add(c);
	}
};

