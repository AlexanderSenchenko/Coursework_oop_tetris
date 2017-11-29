#ifndef GAME_H
#define GAME_H

#include <ctime> 
#include "field.h"

class Game
{
	Field field;
	int key;
	WINDOW *win;
	int time;
public:
	Game();
	Game(int);
	Game(const char*);
	Game(int, const char*);
	~Game();
	void init_option();
	void start_game();
	void render_window();
	int key_processing(int);
	void end();
};

Game::Game()
{
	init_option();
	time = 200000;
	move(1, 25);
	addstr("Hello stranger");
}

Game::Game(int user_time)
{
	init_option();
	time = user_time;
	move(1, 25);
	addstr("Hello stranger");
}

Game::Game(const char* name)
{
	init_option();
	time = 200000;
	move(1, 25);
	printw("Hello");
	move(1, 31);
	addstr(name);
}

Game::Game(int user_time, const char* name)
{
	init_option();
	time = user_time;
	move(1, 25);
	printw("Hello");
	move(1, 31);
	addstr(name);
}

Game::~Game()
{
	delwin(win);
	endwin();
}

void Game::init_option()
{
	initscr();
	curs_set(0);
	cbreak();
	keypad(stdscr, true);
	noecho();
	nodelay(stdscr, true);

	win = newwin(field.get_line_win(), field.get_column_win(), field.get_coord_y_scr(), field.get_coord_x_scr());
	refresh();
	field.print_field(win);
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
	field.print_new_obj(win);
	wrefresh(win);
}

void Game::render_window()
{
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
	field.print_obj(win);
	wrefresh(win);
}

void Game::start_game()
{
	int time_down = clock();
	while ((key = getch()) != 27) {
		if ((clock() - time_down) >= (float)time) {
			time_down = clock();
			if (field.move_down(win)) {
				mvprintw(5, 25, "Game over");
				render_window();
				return;
			}
		}

		if (key_processing(key))
			time_down -= 500000;

		render_window();
	}
}

int Game::key_processing(int key)
{
	switch(key)
	{
		case KEY_DOWN:
			return 1;
		case KEY_RIGHT:
			field.move_x(win, 1);
			break;
		case KEY_LEFT:
			field.move_x(win, -1);
			break;
		default:
			break;
	}
	return 0;
}

void Game::end()
{
	while((key = getch()) != 27) {
		mvprintw(10, 25, "Input Esc for exit");
		wrefresh(win);
	}
}

#endif