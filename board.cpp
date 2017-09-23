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

Players Board::playerToMove() const {
    
    if (nextPlayer_to_move == player1) {
        return player1;
    } else {
        return player2;
    }
    
}

Result Board::makeMove(int originalCol, int originalRow, int finalCol, int finalRow) {
    vector<vector<int>> startingPointForJump;
    vector<vector<int>> possibilities = possibleMoves(originalCol, originalRow, startingPointForJump);
    
    vector<int> userInputOrig = {originalRow, originalCol};
    vector<int> userInputFinal = {finalRow, finalCol};
    
    for (int i = 0; i < possibilities.size(); i++) {
        if (userInputFinal == possibilities[i]) {
            TokenType originalPlayer = board[originalRow][originalCol];
            
            if (playerToMove() == player1) {
                if (startingPointForJump.size() > 0) {
                    for (int i = 0; i < startingPointForJump.size(); i++) {
                        if ((abs(finalRow - originalRow) == 2) && (startingPointForJump[i] ==   userInputOrig)) {
                            board[originalRow][originalCol] = nothing;
                            if (originalPlayer == kingBlack) {
                                board[finalRow][finalCol] = kingBlack;
                            } else {
                                board[finalRow][finalCol] = black;
                            }

                            board[(finalRow + originalRow) / 2][(finalCol + originalCol) / 2] = nothing;
                            
                            if (finalRow == 7) {
                                board[finalRow][finalCol] = kingBlack;
                            }
                            updateToMove();
                            return noResult;
                        }
                        
                    }
                    
                    return illegalMove;
                }
                
                board[originalRow][originalCol] = nothing;
                
                if (originalPlayer == kingBlack) {
                    board[finalRow][finalCol] = kingBlack;
                } else {
                    board[finalRow][finalCol] = black;
                }
                
                
                if (finalRow == 7) {
                    board[finalRow][finalCol] = kingBlack;
                }
                
                updateToMove();
                return noResult;
            } else {
                
                if (startingPointForJump.size() > 0) {
                    for (int i = 0; i < startingPointForJump.size(); i++) {
                        if ((abs(finalRow - originalRow) == 2) && (startingPointForJump[i] == userInputOrig)) {
                            
                            board[originalRow][originalCol] = nothing;
                            
                            if (originalPlayer == kingRed) {
                                board[finalRow][finalCol] = kingRed;
                            } else {
                                board[finalRow][finalCol] = red;
                            }
                            
                            board[(finalRow + originalRow) / 2][(finalCol + originalCol) / 2] = nothing;
                            
                            if (finalRow == 0) {
                                board[finalRow][finalCol] = kingRed;
                            }
                            
                            updateToMove();
                            return noResult;
                        }
                        
                    }
                    
                    return illegalMove;
                }
                
                board[originalRow][originalCol] = nothing;
                
                if (originalPlayer == kingRed) {
                    board[finalRow][finalCol] = kingRed;
                } else {
                    board[finalRow][finalCol] = red;
                }
                
                
                if (finalRow == 0) {
                    board[finalRow][finalCol] = kingRed;
                }
                
                
                updateToMove();

                return noResult;
            }
        }
    }
    
    
    return illegalMove;
    
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

vector<vector<int>> Board::possibleMoves(int col, int row, vector<vector<int>> &startingJumps) {
    vector<vector<int>> possible;
    vector<vector<int>> jumpsOnly;
    
    
    if (playerToMove() == player1) {
        if (board[row][col] == black || board[row][col] == kingBlack) {
            if (inBounds(row + 1, col + 1) && board[row + 1][col + 1] == nothing) {
                possible.push_back({row + 1, col + 1});
            }
            if (inBounds(row + 1, col - 1) && board[row + 1][col - 1] == nothing) {
                possible.push_back({row + 1, col - 1});
            }
            if (inBounds(row + 2, col + 2) && (board[row + 1][col + 1] == red || board[row + 1][col + 1] == kingRed) && board[row + 2][col + 2] == nothing) {
                possible.clear();
                possible.push_back({row + 2, col + 2});
            }
            if (inBounds(row + 2, col - 2) && (board[row + 1][col - 1] == red || board[row + 1][col - 1] == kingRed) && board[row + 2][col - 2] == nothing) {
                string move;
                possible.push_back({row + 2, col - 2});
            }
            
            if (board[row][col] == kingBlack) {
                if (inBounds(row - 1, col + 1) && board[row - 1][col + 1] == nothing) {
                    possible.push_back({row - 1, col + 1});
                }
                if (inBounds(row - 1, col - 1) && board[row - 1][col - 1] == nothing) {
                    possible.push_back({row - 1, col - 1});
                }
                if (inBounds(row - 2, col + 2) && (board[row - 1][col + 1] == red || board[row - 1][col + 1] == kingRed) && board[row - 2][col + 2] == nothing) {
                    possible.push_back({row - 2, col + 2});
                }
                if (inBounds(row - 2, col - 2) && (board[row - 1][col - 1] == red || board[row - 1][col - 1] == kingRed) && board[row - 2][col - 2] == nothing) {
                    possible.push_back({row - 2, col - 2});
                }

            }
            
            
            
            for (int i = 0; i < NUM_ROWS; i++) {
                for (int j = 0; j < NUM_COLS; j++) {
                    if (board[i][j] == black || board[i][j] == kingBlack) {
                        if (inBounds(i + 2, j + 2) && (board[i + 1][j + 1] == red || board[i + 1][j + 1] == kingRed) && board[i + 2][j + 2] == nothing) {
                            jumpsOnly.push_back({i + 2, j + 2});
                            startingJumps.push_back({i, j});
                        }
                        if (inBounds(i + 2, j - 2) && (board[i + 1][j - 1] == red || board[i + 1][j - 1] == kingRed) && board[i + 2][j - 2] == nothing) {
                            jumpsOnly.push_back({i + 2, j - 2});
                            startingJumps.push_back({i, j});
                        }
                        
                        
                        if (board[i][j] == kingBlack) {
                            if (inBounds(i - 2, j + 2) && (board[i - 1][j + 1] == red || board[i - 1][j + 1] == kingRed) && board[i - 2][j + 2] == nothing) {
                                jumpsOnly.push_back({i - 2, j + 2});
                                startingJumps.push_back({i, j});
                            }
                            if (inBounds(i - 2, j - 2) && (board[i - 1][j - 1] == red || board[i - 1][j - 1] == kingRed) && board[i - 2][j - 2] == nothing) {
                                jumpsOnly.push_back({i - 2, j - 2});
                                startingJumps.push_back({i, j});
                            }
                        }
                    }
                }
            }
            
            if (jumpsOnly.size() > 0) {
                return jumpsOnly;
            }
            
            
            return possible;
        }
        

    }
    
    if (playerToMove() == player2) {
        if (board[row][col] == red || board[row][col] == kingRed) {
            if (inBounds(row - 1, col + 1) && board[row - 1][col + 1] == nothing) {
                possible.push_back({row - 1, col + 1});
            }
            if (inBounds(row - 1, col - 1) && board[row - 1][col - 1] == nothing) {
                possible.push_back({row - 1, col - 1});
            }
            if (inBounds(row - 2, col + 2) && (board[row - 1][col + 1] == black || board[row - 1][col + 1] == kingBlack) && board[row - 2][col + 2] == nothing) {
                possible.push_back({row - 2, col + 2});
            }
            if (inBounds(row - 2, col - 2) && (board[row - 1][col - 1] == black || board[row - 1][col - 1] == kingBlack) && board[row - 2][col - 2] == nothing) {
                possible.push_back({row - 2, col - 2});
            }
            
            if (board[row][col] == kingRed) {
                if (inBounds(row + 1, col + 1) && board[row + 1][col + 1] == nothing) {
                    possible.push_back({row + 1, col + 1});
                }
                if (inBounds(row + 1, col - 1) && board[row + 1][col - 1] == nothing) {
                    possible.push_back({row + 1, col - 1});
                }
                if (inBounds(row + 2, col + 2) && (board[row + 1][col + 1] == black || board[row + 1][col + 1] == kingBlack) && board[row + 2][col + 2] == nothing) {
                    possible.push_back({row + 2, col + 2});
                }
                if (inBounds(row + 2, col - 2) && (board[row + 1][col - 1] == black || board[row + 1][col - 1] == kingBlack) && board[row + 2][col - 2] == nothing) {
                    possible.push_back({row + 2, col - 2});
                }
            }
            
            
            
            for (int i = 0; i < NUM_ROWS; i++) {
                for (int j = 0; j < NUM_COLS; j++) {
                    if (board[i][j] == red || board[i][j] == kingRed) {
                        if (inBounds(i - 2, j + 2) && (board[i - 1][j + 1] == black || board[i - 1][j + 1] == kingBlack) && board[i - 2][j + 2] == nothing) {
                            jumpsOnly.push_back({i - 2, j + 2});
                            startingJumps.push_back({i, j});
                        }
                        if (inBounds(i - 2, j - 2) && (board[i - 1][j - 1] == black || board[i - 1][j - 1] == kingBlack) && board[i - 2][j - 2] == nothing) {
                            jumpsOnly.push_back({i - 2, j - 2});
                            startingJumps.push_back({i, j});
                        }
                        
                        
                        if (board[i][j] == kingRed) {
                            if (inBounds(i + 2, j + 2) && (board[i + 1][j + 1] == black || board[i + 1][j + 1] == kingBlack) && board[i + 2][j + 2] == nothing) {
                                jumpsOnly.push_back({i + 2, j + 2});
                                startingJumps.push_back({i, j});
                            }
                            if (inBounds(i + 2, j - 2) && (board[i + 1][j - 1] == black || board[i + 1][j - 1] == kingBlack) && board[i + 2][j - 2] == nothing) {
                                jumpsOnly.push_back({i + 2, j - 2});
                                startingJumps.push_back({i, j});
                            }
                        }
                    }
                }
            }
            
            if (jumpsOnly.size() > 0) {
                return jumpsOnly;
            }
            
            
            return possible;
        }

    }
    
    return possible;
}

void Board::numTokensByColor(int &numBlack, int &numRed) {
    numBlack = 0, numRed = 0;
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (board[i][j] == black || board[i][j] == kingBlack) {
                numBlack++;
            } else if (board[i][j] == red || board[i][j] == kingRed) {
                numRed++;
            }
        }
    }
}



