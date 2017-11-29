#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <ctime> 
#include "field.h"

using namespace std;

class Game
{
	Field field;
	int key;
	WINDOW *win;
	static const int time = 200000;
public:
	Game();
	~Game();
	void start_game();
	void test();
	void render_window();
	int key_processing(int);
	double wtime();
};

Game::Game()
{
	initscr();
	curs_set(0);
	cbreak();
	keypad(stdscr, true);
	noecho();
	nodelay(stdscr, true);

	win = newwin(field.get_line_win(), field.get_column_win(), coord_y_scr, coord_x_scr);
	refresh();
	field.print_field(win);
	//render_window();
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
	field.print_new_obj(win);
	wrefresh(win);
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
			if (field.move_down(win)) {
				mvwprintw(win, field.get_column_win() / 2, 6, "Game over");
				render_window();
				return;
			}
			//field.move_down(win);
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
		case KEY_UP:
			break;
		case KEY_DOWN:
			return 1;
		case KEY_RIGHT:
			field.key_right(win);
			break;
		case KEY_LEFT:
			field.key_left(win);
			break;
		default:
			break;
	}
	return 0;
}

void Game::test()
{
	while((key = getch()) != 27) {
		mvprintw(0, 0, "Input Esc for exit");
		wrefresh(win);
	}
}

#endif