#ifndef FIELD_H
#define FIELD_H

const unsigned int coord_y_scr = 0;
const unsigned int coord_x_scr = 25;

class Field
{
	static const unsigned int line = 22;
	static const unsigned int column = 22;
	int y_obj;
	int x_obj;
	char field[line][column];
public:
	Field();
	//~Field();
	int check_x_left(int);
	int check_x_right(int);
	
	int get_line_win();
	int get_column_win();
	int get_index(int);

	void key_left(WINDOW*);
	void key_right(WINDOW*);
	void key_up(WINDOW*);
	void key_down(WINDOW*);

	void print_obj(WINDOW*);
	void print_del_obj(WINDOW*);

	void print_info(int);
};

Field::Field()
{
	y_obj = 1;
	x_obj = 10;

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
}

int Field::check_x_right(int coord)
{
	if (coord == line - 2)
		return coord;
	return coord + 1;
}

int Field::check_x_left(int coord)
{
	if (coord == 1)
		return coord;
	return coord - 1;
}

int Field::get_line_win() {return line;}

int Field::get_column_win() {return column;}

int Field::get_index(int num_fig)
{
	return num_fig * 7 + num_fig;
}

void Field::key_left(WINDOW* win)
{
	print_del_obj(win);
	x_obj = check_x_left(x_obj);
}

void Field::key_right(WINDOW* win)
{
	print_del_obj(win);
	x_obj = check_x_right(x_obj);
}

void Field::key_up(WINDOW* win)
{
	print_del_obj(win);
	y_obj--;
}

void Field::key_down(WINDOW* win)
{
	print_del_obj(win);
	y_obj++;
}

void Field::print_obj(WINDOW* win)
{
	mvwprintw(win, y_obj, x_obj, "$");
}

void Field::print_del_obj(WINDOW* win)
{
	mvwprintw(win, y_obj, x_obj, " ");
}

void Field::print_info(int key)
{
	mvprintw(0, 0, "Key: %c %d", key, key);
	mvprintw(1, 0, "y, x: %d %d", y_obj, x_obj);
}

#endif