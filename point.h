#ifndef Point_H
#define Point_H

class Point
{
	struct point
	{
		int x;
		int y;
	};
protected:
	point p[4];
public:
	virtual int get_x(int) = 0;
	virtual int get_y(int) = 0;
};

#endif