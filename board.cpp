#include "board.h"

using namespace std;

Board::Board() {
    for (int i = 0; i < NUM_COLS; i++) {
        if (i % 2 == 0) {
            board[0][i] = black;
        } else {
            board[0][i] = nothing;
        }
    }
    
    for (int i = 0; i < NUM_COLS; i++) {
        if (i % 2 != 0) {
            board[1][i] = black;
        } else {
            board[1][i] = nothing;
        }
    }
    
    for (int i = 0; i < NUM_COLS; i++) {
        if (i % 2 == 0) {
            board[2][i] = black;
        } else {
            board[2][i] = nothing;
        }
    }
    
    
    for (int i = 0; i < NUM_COLS; i++) {
        if (i % 2 != 0) {
            board[5][i] = red;
        } else {
            board[5][i] = nothing;
        }
    }
    
    for (int i = 0; i < NUM_COLS; i++) {
        if (i % 2 == 0) {
            board[6][i] = red;
        } else {
            board[6][i] = nothing;
        }
    }
    
    for (int i = 0; i < NUM_COLS; i++) {
        if (i % 2 != 0) {
            board[7][i] = red;
        } else {
            board[7][i] = nothing;
        }
    }
    
    for (int i = 0; i < NUM_COLS; i++) {
        board[4][i] = nothing;
        board[3][i] = nothing;
    }
    
}

TokenType Board::typeAtLocation(int row, int col) {
    return board[row][col];
}

void Board::printBoard(ostream &os) const {
    os << endl;
    
    char rowID = 'h';
    for (int row = NUM_ROWS - 1; row >= 0; row--)  {
        os << "     +---+---+---+---+---+---+---+---+"
        << endl
        << "   ";
        
        os << rowID;

        for (int col = 0; col < NUM_COLS; col++)   {
            os << " | " ;
            if (board[row][col] == red)
                os << RED;
            else if (board[row][col] == kingRed)
                os << KINGRED;
            else if (board[row][col] == black) {
                os << BLACK;
            } else if (board[row][col] == kingBlack) {
                os << KINGBLACK;
            }
            else
                os << NOTHING;
        }
        os << " |" << endl;
        
        rowID--;
    }
    os << "     +---+---+---+---+---+---+---+---+" << endl
    <<"       1   2   3   4   5   6   7   8" << endl;
    return;
}

int Board::playerToMove() const {
    
    if (nextPlayer_to_move == player1) {
        return 1;
    } else if (nextPlayer_to_move == player2) {
        return 2;
    }
    
    return -1;
}

Result Board::makeMove(int originalCol, int originalRow, int finalRow, int finalCol){
	if (!inBounds(finalRow, finalCol)) {
		return illegalMove;
	}

	//if(playerToMove == player1 )
}
Players Board::updateToMove() {
    Players oldPlayer = nextPlayer_to_move;
    
    if (nextPlayer_to_move == player1) {
        nextPlayer_to_move = player2;
    } else if (nextPlayer_to_move == player2) {
        nextPlayer_to_move = player1;
    }
    
    return oldPlayer;
}

bool Board::inBounds(int row, int col) const {
    if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
        return true;
    }
    
    return false;
}



