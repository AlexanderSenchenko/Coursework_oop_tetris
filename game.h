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
	static const int time = 300000;
public:
	Game();
	~Game();
	void start_game();
	void render_window();
	void key_processing(int);
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
	//mvwprintw(win, 1, 1, "%d", time);
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

/*double Game::wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}*/

void Game::start_game()
{
	int time_down = clock();
	while ((key = getch()) != 27) {
		if ((clock() - time_down) >= (float)time) {
			time_down = clock();
			field.key_down(win);
		}

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

#endif