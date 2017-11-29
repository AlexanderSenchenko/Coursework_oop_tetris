#ifndef FIELD_H
#define FIELD_H

#include "figure.h"



class Field
{
	static const int line = 22;
	static const int column = 22;
	static const int start_y_obj = 1;
	static const int start_x_obj = 10;
	static const int coord_y_scr = 1;
	static const int coord_x_scr = 0;
	char field[line][column];
	Figure figure;
public:
	Field();

	int get_line_win();
	int get_column_win();
	int get_coord_y_scr();
	int get_coord_x_scr();

	void move_x(WINDOW*, int);
	int check_move_x(int);

	int move_down(WINDOW*);
	int check_down(WINDOW*);

	void check_all_line_matrix();
	int check_line(int);
	void delete_line(int);
	void swap_all_line(int);
	int swap_line(int);
	void swap_elem(int, int);

	void print_obj(WINDOW*);
	void print_del_obj(WINDOW*);
	void print_field(WINDOW*);
	int print_new_obj(WINDOW*);
};

Field::Field()
{
	for (int i = 0; i < line; i++)
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
}

int Field::get_line_win() {return line;}
int Field::get_column_win() {return column;}
int Field::get_coord_x_scr() {return coord_x_scr;}
int Field::get_coord_y_scr() {return coord_y_scr;}

void Field::move_x(WINDOW* win, int ind)
{
	print_del_obj(win);
	if (!check_move_x(ind))
		figure.move_x(win, ind);
}

int Field::check_move_x(int ind)
{
	int x, y;
	for (int i = 0; i < 4; i++)
	{
		y = figure.get_y(i);
		x = figure.get_x(i);
		if (field[y][x + ind] != ' ')
			return 1;
	}
	return 0;
}

int Field::move_down(WINDOW* win)
{
	print_del_obj(win);

	if (!check_down(win)) {
		figure.move_y(win, 1);
	} else {
		int x, y;
		for (int i = 0; i < 4; i++)
		{
			x = figure.get_x(i);
			y = figure.get_y(i);
			field[y][x] = '$';
		}
		check_all_line_matrix();
		if (print_new_obj(win))
			return 1;
		print_field(win);
	}

	return 0;
}

int Field::check_down(WINDOW* win)
{
	int x, y;
	for (int i = 0; i < 4; i++)
	{
		y = figure.get_y(i);
		x = figure.get_x(i);
		if (field[y + 1][x] != ' ') {
			return 1;
		}
	}
	return 0;
}

void Field::check_all_line_matrix()
{
	for (int i = 20; i > 0; i--)
	{
		if (check_line(i))
			i++;
	}
	return;
}

int Field::check_line(int y_line)
{
	for (int x_column = 1; x_column < column - 1; x_column++)
	{
		if (field[y_line][x_column] == ' ')
			return 0;
	}
	delete_line(y_line);
	swap_all_line(y_line);
	return 1;
}

void Field::swap_all_line(int y_line)
{
	for (int y_str = y_line; y_str > 0; y_str--) {
		swap_line(y_str);
	}
	return;
}

int Field::swap_line(int y_line)
{
	for (int x_column = 1; x_column < column - 1; x_column++)
	{
		swap_elem(y_line, x_column);
	}
	return 0;
}

void Field::delete_line(int y_line)
{
	for (int x_column = 1; x_column < column - 1; x_column++)
	{
		field[y_line][x_column] = ' ';
	}
	return;
}

void Field::swap_elem(int y_line, int x_column)
{
	char a = field[y_line][x_column];
	field[y_line][x_column] = field[y_line - 1][x_column];
	field[y_line - 1][x_column] = a;
	return;
}

void Field::print_field(WINDOW* win)
{
	//int y_matr = coord_y_scr, x_matr = 0;
	for (int i = 1; i < line - 1; i++)
	{
		for (int j = 1; j < column - 1; j++)
		{
			//move(i + y_matr, j + x_matr);
			//printw("%c", field[i][j]);
			mvwaddch(win, i, j, field[i][j]);
		}
	}
}

void Field::print_obj(WINDOW* win)
{
	figure.print_figure(win);
}

int Field::print_new_obj(WINDOW* win)
{
	int x, y;
	figure.get_new_figure(win);
	for (int i = 0; i < 4; i++) {
		y = figure.get_y(i);
		x = figure.get_x(i);
		if (field[y][x] != ' ') {
			return 1;
		}
	}
	return 0;
}

void Field::print_del_obj(WINDOW* win)
{
	figure.delete_figure(win);
}

#endif