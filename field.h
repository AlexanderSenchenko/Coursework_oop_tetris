#ifndef FIELD_H
#define FIELD_H

#include "figure.h"
#include <string>

using namespace std;

const unsigned int coord_y_scr = 2;
const unsigned int coord_x_scr = 25;
const int start_y_obj = 1;
const int start_x_obj = 10;

class Field
{
	static const unsigned int line = 22;
	static const unsigned int column = 22;
	int y_obj;
	int x_obj;
	char field[line][column];
	Figure figure;
public:
	Field();
	int check_x_left();
	int check_x_right();
	int check_y_down(WINDOW*);

	int get_line_win();
	int get_column_win();
	int get_index(int);

	void key_left(WINDOW*);
	void key_right(WINDOW*);
	void key_up(WINDOW*);
	int move_down(WINDOW*);

	void print_obj(WINDOW*);
	void print_del_obj(WINDOW*);
	void print_field(WINDOW* win);
	void print_new_obj(WINDOW*);

	void get_figure();

};

Field::Field()
{
	y_obj = start_y_obj;
	x_obj = start_x_obj;

	for (unsigned int i = 0; i < line; i++)
	{
		if (i == 0 || i == line - 1) {
			for (int j = 0; j < 22; j++)
			{
				field[i][j] = '#';
			}
			continue;
		}

		for (int j = 0; j < 22; j++)
		{
			if (j == 0 || j == 21) {
				field[i][j] = '#';
				continue;
			}
			field[i][j] = ' ';
		}
	}

	field[x_obj][y_obj] = '$';
}

int Field::get_line_win() {return line;}

int Field::get_column_win() {return column;}

void Field::key_right(WINDOW* win)
{
	print_del_obj(win);
	if (!check_x_right())
		figure.move_x(win, 1);
		//x_obj++;
}

int Field::check_x_right()
{
	for (int i = 0; i < 4; i++)
	{
		int y = figure.get_y(i);
		int x = figure.get_x(i);
		if (field[x + 1][y] != ' ')
			return 1;
	}
	return 0;
}

void Field::key_left(WINDOW* win)
{
	print_del_obj(win);
	if (!check_x_left())
		figure.move_x(win, -1);
		//x_obj--;
}

int Field::check_x_left()
{
	for (int i = 0; i < 4; i++)
	{
		int y = figure.get_y(i);
		int x = figure.get_x(i);
		if (field[x - 1][y] != ' ')
			return 1;
	}
	return 0;
}

int Field::move_down(WINDOW* win)
{
	int w;
	print_del_obj(win);
	mvprintw(0, 25, "y_obj:%d x_obj%d", y_obj, x_obj);
	mvprintw(1, 25, "%c", field[x_obj][y_obj - 2]);
	if ((w = check_y_down(win)) == 0) {
		//y_obj++;
		figure.move_y(win, 1);
		//return 0;
	} else if (w == 2) {
		//print_new_obj(win);
		for (int i = 0; i < 4; i++)
		{
			int x = figure.get_x(i);
			int y = figure.get_y(i);
			field[x][y] = '$';
			//y_obj = start_y_obj;
			//x_obj = start_x_obj;
		}
		print_new_obj(win);
		print_field(win);
	} else {
		return 1;
	}

	return 0;
}

int Field::check_y_down(WINDOW* win)
{
	/*if (field[x_obj][y_obj - 2] == '#' && field[x_obj][y_obj + 1] == '$') {
		return 1;
	} else if (field[x_obj][y_obj + 1] != ' ') {
		field[start_x_obj][start_y_obj] = ' ';
		field[x_obj][y_obj] = '$';
		y_obj = start_y_obj;
		x_obj = start_x_obj;
		print_field(win);
	}*/
	for (int i = 0; i < 4; i++)
	{
		int y = figure.get_y(i);
		int x = figure.get_x(i);
		if (field[x][y + 1] != ' ') {
			return 2;
		}
	}
	//figure.check_border_y();
	return 0;
}

void Field::key_up(WINDOW* win)
{
	print_del_obj(win);
	y_obj--;
}

void Field::print_field(WINDOW* win)
{
	unsigned int y_matr = coord_y_scr, x_matr = 0;
	string test;
	for (unsigned int i = 1; i < line - 1; i++)
	{
		for (unsigned int j = 1; j < column - 1; j++)
		{
			mvprintw(j + y_matr, i + x_matr, "%c", field[i][j]);
			test = field[i][j];
			mvwprintw(win, j, i, &test[0]);
		}
	}
}

void Field::print_obj(WINDOW* win)
{
	//mvwprintw(win, y_obj, x_obj, "$");
	//figure.get_figure(win);
	figure.print_figure(win);
}

void Field::print_new_obj(WINDOW* win)
{
	//mvwprintw(win, y_obj, x_obj, "$");
	figure.get_figure(win);
	//figure.print_figure(win);
}

void Field::print_del_obj(WINDOW* win)
{
	//mvwprintw(win, y_obj, x_obj, " ");
	//field[x_obj][y_obj] = ' ';
	figure.delete_fig(win);
}

#endif