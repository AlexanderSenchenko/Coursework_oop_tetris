#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include <ctime> 
//#include <sys/time.h>
#include "field.h"

using namespace std;

class Game
{
	Field field;
	int key;
	WINDOW *win;
	static const int time = 50000;
public:
	Game();
	~Game();
	void start_game();
	void test();
	void render_window();
	void key_processing(int);
	double wtime();
};

Game::Game()
{
	initscr();
	//curs_set(0);
	cbreak();
	keypad(stdscr, true);
	noecho();
	nodelay(stdscr, true);

	win = newwin(field.get_line_win(), field.get_column_win(), coord_y_scr, coord_x_scr);
	refresh();
	field.print_field(win);
	render_window();
}

Game::~Game()
{
	delwin(win);
	endwin();
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
			if (field.key_down(win))
				return;
		}

		key_processing(key);

		render_window();
	}
}

void Game::key_processing(int key)
{
	switch(key)
	{
		case KEY_UP:
			//field.key_up(win);
			break;
		case KEY_DOWN:
			//field.key_down(win);
			break;
		case KEY_RIGHT:
			field.key_right(win);
			break;
		case KEY_LEFT:
			field.key_left(win);
			break;
		default:
			break;
	}
}

void Game::test()
{
	while(1) {
		mvprintw(0, 0, "End");
	}
}

#endif