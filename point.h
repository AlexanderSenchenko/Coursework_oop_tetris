#ifndef Point_H
#define Point_H

#include <cstdlib>

using namespace std;

class Point
{
protected:
	struct point
	{
		int x;
		int y;
	} p[4];
public:
	int get_x();
	int get_y();
};

int Point::get_x() {return p->x;}

int Point::get_y() {return p->y;}

#endif