#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <cstdlib>
//#include "point.h"

using namespace std;

class Figure
{
	int obj[7][4][4][2] =
	{
		{
			{{0, 0}, {0, 1}, {0, 2}, {0, 3}},
			{{-1, 1}, {0, 1}, {1, 1}, {2, 1}},
			{{0, 0}, {0, 1}, {0, 2}, {0, 3}},
			{{-1, 1}, {0, 1}, {1, 1}, {2, 1}}
		},//I!
		{
			{{1, 0}, {0, 0}, {0, 1}, {0, 2}},
			{{-1, 0}, {-1, 1}, {0, 1}, {1, 1}},
			{{-1, 2}, {0, 2}, {0, 1}, {0, 0}},
			{{1, 2}, {1, 1}, {0, 1}, {-1, 1}}
		},//L!
		{
			{{-1, 0}, {0, 0}, {0, 1}, {0, 2}},
			{{-1, 2}, {-1, 1}, {0, 1}, {1, 1}},
			{{1, 2}, {0, 2}, {0, 1}, {0, 0}},
			{{1, 0}, {1, 1}, {0, 1}, {-1, 1}}
		},//L
		{
			{{-1, 1}, {0, 0}, {0, 1}, {1, 1}},
			{{0, 2}, {-1, 1}, {0, 1}, {0, 0}},
			{{1, 1}, {0, 2}, {0, 1}, {-1, 1}},
			{{0, 0}, {1, 1}, {0, 1}, {0, 2}}
		},//T!
		{
			{{1, 0}, {0, 0}, {0, 1}, {-1, 1}},
			{{0, 2}, {-1, 0}, {0, 1}, {-1, 1}},
			{{1, 0}, {0, 0}, {0, 1}, {-1, 1}},
			{{0, 2}, {-1, 0}, {0, 1}, {-1, 1}}
		},//Z!
		{
			{{-1, 0}, {0, 0}, {0, 1}, {1, 1}},
			{{1, 0}, {1, 1}, {0, 1}, {0, 2}},
			{{-1, 0}, {0, 0}, {0, 1}, {1, 1}},
			{{1, 0}, {1, 1}, {0, 1}, {0, 2}}
		},//Z!
		{
			{{0, 0}, {1, 0}, {0, 1}, {1, 1}},
			{{0, 0}, {1, 0}, {0, 1}, {1, 1}},
			{{0, 0}, {1, 0}, {0, 1}, {1, 1}},
			{{0, 0}, {1, 0}, {0, 1}, {1, 1}}
		}//O!
	};
	struct point
	{
		int x;
		int y;
	} p[4];
public:
	void get_figure(WINDOW*);
	//int get_index(int);

	void move_x(WINDOW*, int);
	void move_y(WINDOW*, int);
	void rotate(WINDOW*);

	void print_figure(WINDOW*);
	void delete_fig(WINDOW*);

	int get_y(int);
	int get_x(int);
};

void Figure::get_figure(WINDOW *win)
{
	srand(time(0));
	int num = rand() % 7;
	int pol = rand() % 4;

	/*for (int i = 0; i < 4; i++, num += 2)
	{
		p[i].x = obj[num] + 10;
		p[i].y = obj[num + 1] + 1;
		mvwaddch(win, p[i].y, p[i].x, '$');
	}*/
	for (int i = 0; i < 4; i++)
	{
		p[i].x = obj[num][pol][i][0] + 10;
		p[i].y = obj[num][pol][i][1] + 1;
		mvwaddch(win, p[i].y, p[i].x, '$');
	}
}

int Figure::get_y(int num_point) {return p[num_point].y;}

int Figure::get_x(int num_point) {return p[num_point].x;}

//int Figure::get_index(int num_fig) {return num_fig * 7 + num_fig;}

void Figure::move_x(WINDOW* win, int x)
{
	for (int i = 0; i < 4; i++) {
		p[i].x += x;
		mvwaddch(win, p[i].y, p[i].x, '$');
	}
}

void Figure::move_y(WINDOW* win, int y)
{
	for (int i = 0; i < 4; i++) {
		p[i].y += y;
		mvwaddch(win, p[i].y, p[i].x, '$');
	}
}

/*void Figure::rotate()
{

}*/











void Figure::print_figure(WINDOW *win)
{
	for (int i = 0; i < 4; i++)
	{
		move(i, 0);
		printw("x%d, y%d", p[i].x, p[i].y);
		mvwaddch(win, p[i].y, p[i].x, '$');
	}
}

void Figure::delete_fig(WINDOW* win)
{
	for (int i = 0; i < 4; i++) {
		mvwaddch(win, p[i].y, p[i].x, ' ');
	}
}

#endif