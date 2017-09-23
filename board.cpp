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
    
}

TokenType Board::typeAtLocation(int row, int col) {
    return board[row][col];
}

