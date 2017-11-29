#include "game.h"
#include <iostream>

using namespace std;

int main()
{
	Game game = {200000, "Name"};
	game.start_game();
	game.end();

	return 0;
}