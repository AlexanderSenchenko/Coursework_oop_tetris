#ifndef Point_H
#define Point_H

#include <iostream>
#include <cstdlib>

using namespace std;

class Point
{
	struct point
	{
		int x;
		int y;
	};
	point *p;
public:
	void set_point(int, int);
	int get_x();
	int get_y();
};

void Point::set_point(int x_fig, int y_fig)
{
	p->x = x_fig;
	p->y = y_fig;
}

int Point::get_x() {return p->x;}

int Point::get_y() {return p->y;}

#endif