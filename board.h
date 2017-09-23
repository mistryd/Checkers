#ifndef BOARD_H__
#define BOARD_H__

#include <ostream>
using namespace std;


enum Result {
    noResult, jump, king, illegalMove, win
};

enum TokenType {
    black, red, kingBlack, kingRed, nothing
};

const int NUM_ROWS = 8, NUM_COLS = 8;

const char BLACK = 'b', KINGBLACK = 'B', KINGRED = 'R', RED = 'r', EMPTY = ' ';


class Board {
    
public:
    
    // Creates an empty board
    Board();
    
    // Prints board
    void printBoard(std::ostream &os) const;
    
    // Returns piece type at a given location
    TokenType typeAtLocation(int row, int col);
    
    // Returns player to move (1 for player 1, 2 for player 2)
    int playerToMove() const;
    
    // Makes move and returns result
    Result makeMove(int col);
    
private:
    
    // Switches whos turn it is
    TokenType updateToMove();
    
    // Checks to see if row/col are in bounds of gameboard
    bool inBounds(int row, int col) const;
    
    // The board as an array of piece types
    TokenType board[NUM_ROWS][NUM_COLS];
    
    // Variable to keep track of whose turn it is
    TokenType nextPlayer_to_move;
};

#endif
