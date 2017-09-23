#ifndef connect4_h__
#define connect4_h__

#include <string>
#include "board.h"

using namespace std;

// Goes through the game in console
void consolePlay();

// Creates the board and assigns player names
Board getBoard(string &p1, string &p2);



#endif
