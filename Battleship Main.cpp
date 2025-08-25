//============================================================================
// Name        : Battleship.cpp
// Author      : Bilal Bilican
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Game.h"
using namespace std;

int main() {
	srand(time(0));
    Game game;
    game.start();
    return 0;
}
