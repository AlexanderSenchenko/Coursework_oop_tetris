#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include "field.h"

class Game
{
	Field field;
	int key;
	WINDOW *win;
public:
	Game();
	~Game();
	void start_game();
	void render_window();
	void key_processing(int);
};

Game::Game()
{
	initscr();
	curs_set(0);
	cbreak();
	keypad(stdscr, true);
	noecho();

	win = newwin(field.get_line_win(), field.get_column_win(), coord_y_scr, coord_x_scr);
	refresh();
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
	while ((key = getch()) != 27) {
		
		key_processing(key);

		render_window();

		field.print_info(key);
	}
}

void Game::key_processing(int key)
{
	switch(key)
	{
		case KEY_UP:
			field.key_up(win);
			break;
		case KEY_DOWN:
			field.key_down(win);
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

#endif