#ifndef FIELD_H
#define FIELD_H

#include "figure.h"
#include <string>

using namespace std;

const int coord_y_scr = 2;
const int coord_x_scr = 25;

const int start_y_obj = 1;
const int start_x_obj = 10;

class Field
{
	static const int line = 22;
	static const int column = 22;
	int y_obj;
	int x_obj;
	char field[line][column];
	Figure figure;
public:
	Field();

	int get_line_win();
	int get_column_win();

	void key_left(WINDOW*);
	int check_left();

	void key_right(WINDOW*);
	int check_right();

	void key_up(WINDOW*);

	int move_down(WINDOW*);
	int check_down(WINDOW*);

	void check_all_line_matrix();
	int check_line(int);
	int swap_line(int);
	void delete_line(int);
	void swap_elem(int, int);

	void print_obj(WINDOW*);
	void print_del_obj(WINDOW*);
	void print_field(WINDOW* win);
	int print_new_obj(WINDOW*);
};

Field::Field()
{
	y_obj = start_y_obj;
	x_obj = start_x_obj;

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

	//field[x_obj][y_obj] = '$';
}

int Field::get_line_win() {return line;}

int Field::get_column_win() {return column;}

void Field::key_left(WINDOW* win)
{
	print_del_obj(win);
	if (!check_left())
		figure.move_x(win, -1);
		//x_obj--;
}

int Field::check_left()
{
	for (int i = 0; i < 4; i++)
	{
		int y = figure.get_y(i);
		int x = figure.get_x(i);
		if (field[y][x - 1] != ' ')
			return 1;
	}
	return 0;
}

void Field::key_right(WINDOW* win)
{
	print_del_obj(win);
	if (!check_right())
		figure.move_x(win, 1);
		//x_obj++;
}

int Field::check_right()
{
	for (int i = 0; i < 4; i++)
	{
		int y = figure.get_y(i);
		int x = figure.get_x(i);
		if (field[y][x + 1] != ' ')
			return 1;
	}
	return 0;
}

int Field::move_down(WINDOW* win)
{
	print_del_obj(win);

	move(0, 25);
	printw("y_obj:%d x_obj%d", y_obj, x_obj);
	//move(1, 25);
	//printw("%c", field[x_obj][y_obj - 2]);

	if (!check_down(win)) {
		//y_obj++;
		figure.move_y(win, 1);
		//return 0;
	} else {
		//print_new_obj(win);
		for (int i = 0; i < 4; i++)
		{
			int x = figure.get_x(i);
			int y = figure.get_y(i);
			field[y][x] = '$';
			//y_obj = start_y_obj;
			//x_obj = start_x_obj;
		}
		//check_all_line_matrix();
		delete_line(20);
		if (print_new_obj(win))
			return 1;
		print_field(win);
	}

	return 0;
}

int Field::check_down(WINDOW* win)
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
		if (field[y + 1][x] != ' ') {
			return 1;
		} /*else if (field[x][y] == '$') {
			return 1;
		}*/
	}
	//figure.check_border_y();
	return 0;
}

void Field::check_all_line_matrix()
{
	int check = 0;
	for (int i = 20; i > 0; i--)
	{
		//move(1, 10);
		//printw("Test %d", i);
		//delete_line(i);
		for (int j = 1; j < column - 1; j++)
		{
			//delete_line(i);
			//move(2, 10);
			//printw("Test %d", j);
			/*if (field[i][j] == ' 'j == column - 2) {
				//delete_line(i);
				//swap_line(i);
				//j = column - 1;
				//i++;
				check = 1;
				//move(0, 10);
				//printw("Test %d", check);
			}
			*/
			// /check_line(i);
		}
		move(1, 25);
		printw("Check %d", check);
		//if (check == 1) {
		//	delete_line(i);
			//swap_line(i);
			//i--;
		//}
		check = 0;
	}
	//delete_line(20);

	return;
}
/*
int Field::check_line(int y_line)
{
	for (int i = 1; i < 21; i++)
	{

	}
}*/

int Field::swap_line(int y_line)
{
	delete_line(y_line);
	for (int i = 1; i < column - 1; i++)
	{
		swap_elem(i, y_line);
	}
	if (y_line != 0) {
		swap_line(y_line - 1);
	}
	return 0;
}

void Field::delete_line(int y_line)
{
	for (int i = 1; i < column - 1; i++)
	{
		field[y_line][i] = ' ';
	}
	return;
}

void Field::swap_elem(int x_column, int y_line)
{
	char a = field[x_column][y_line];
	field[x_column][y_line] = field[x_column][y_line - 1];
	field[x_column][y_line - 1] = a;
	return;
}













void Field::key_up(WINDOW* win)
{
	print_del_obj(win);
	y_obj--;
}

void Field::print_field(WINDOW* win)
{
	int y_matr = coord_y_scr, x_matr = 0;
	//string test;
	for (int i = 1; i < line - 1; i++)
	{
		for (int j = 1; j < column - 1; j++)
		{
			move(i + y_matr, j + x_matr);
			printw("%c", field[i][j]);
			//test = field[i][j];
			mvwaddch(win, i, j, field[i][j]);
		}
	}
}

void Field::print_obj(WINDOW* win)
{
	//mvwprintw(win, y_obj, x_obj, "$");
	//figure.get_figure(win);
	figure.print_figure(win);
}

int Field::print_new_obj(WINDOW* win)
{
	//mvwprintw(win, y_obj, x_obj, "$");
	figure.get_figure(win);
	for (int i = 0; i < 4; i++) {
		int y = figure.get_y(i);
		int x = figure.get_x(i);
		//проверить координаты на оборот
		if (field[y][x] != ' ') {
			return 1;
		}
	}
	return 0;
	//figure.print_figure(win);
}

void Field::print_del_obj(WINDOW* win)
{
	//mvwprintw(win, y_obj, x_obj, " ");
	//field[x_obj][y_obj] = ' ';
	figure.delete_fig(win);
}

#endif