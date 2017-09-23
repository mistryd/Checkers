#include "checkers.h"

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void consolePlay() {
    string p1, p2;
    Board board = getBoard(p1, p2);
    board.printBoard(cout);
    
    
    
    
    
}

Board getBoard(string &p1, string &p2) {
    cout << "Player 1, enter your name: " << flush;
    getline(cin, p1);
    cout << endl << "Player 2, enter your name: " << flush;
    getline(cin, p2);
    
    
    return Board();
}
