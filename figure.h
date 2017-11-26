#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <cstdlib>
//#include "Point.h"

using namespace std;

class Figure
{
	int obj[7 * 4 * 2] =
	{
		0, 0, 1, 0, 2, 0, 3, 0,
		0, 1, 0, 0, 1, 0, 2, 0,
		0, 0, 0, 1, 1, 1, 2, 1,
		0, 0, 1, 0, 1, 1, 2, 0,
		0, 0, 0, 1, 1, 1, 1, 2,
		0, 2, 1, 1, 0, 1, 1, 0,
		0, 0, 1, 0, 0, 1, 1, 1
	};
	//Point arr_point[4];
public:
	//void set_obj();
	int* get_obj();

};

/*
void Figure::set_obj()
{
	for (int i = 0; i < 4; i++)
	{
		arr_point[i].set_point(i + 1, i + 1);
	}
}
*/

int* Figure::get_obj()
{
	return obj;
}

#endif