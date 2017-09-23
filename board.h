#ifndef BOARD_H__
#define BOARD_H__

#include <ostream>
#include <string>
#include <vector>
using namespace std;


enum Result {
    noResult, jump, king, illegalMove, win
};

enum TokenType {
    black, red, kingBlack, kingRed, nothing
};

enum Players {
    player1, player2
};

const int NUM_ROWS = 8, NUM_COLS = 8;

const char BLACK = 'b', KINGBLACK = 'B', KINGRED = 'R', RED = 'r', NOTHING = ' ';


class Board {
    
public:
    
    // Creates an empty board
    Board();
    
    // Prints board
    void printBoard(std::ostream &os) const;
    
    // Returns piece type at a given location
    TokenType typeAtLocation(int row, int col);
    
    // Returns player to move (1 for player 1, 2 for player 2)
    Players playerToMove() const;
    
    // Makes move and returns result
	Result makeMove(int originalCol, int originalRow, int finalCol, int finalRow);
    
    void numTokensByColor(int &numBlack, int &numRed);
    
    void assignOldGraphics(int row, int col);

    void assignFinalGraphics(int row, int col);
    
    bool isOldAndNewAssignedGraphics();
    
private:
    
    // Switches whos turn it is
    Players updateToMove();
    
    // Checks to see if row/col are in bounds of gameboard
    bool inBounds(int row, int col) const;
    
    // The board as an array of piece types
    TokenType board[NUM_ROWS][NUM_COLS];
    
    // Variable to keep track of whose turn it is
    Players nextPlayer_to_move;
    
    vector<vector<int>> possibleMoves(int col, int row, vector<vector<int>> &startingJumps);
    
};

#endif
