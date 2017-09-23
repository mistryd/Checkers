#include "checkers.h"
#include "board.h"

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void consolePlay() {
    string p1, p2;
    string selectionPieceToMove;
    string selectionWhereToMove;
    
    int originalRow, originalCol, finalRow, finalCol;
    
    Board board = getBoard(p1, p2);
    board.printBoard(cout);
    
    Result result = noResult;
    while (result != win) {
        if (board.playerToMove() == player1) {
            cout << p1 << " what piece would you like to move?: ";
            
        }
        if (board.playerToMove() == player2) {
            cout << p2 << " what piece would you like to move?: ";
            
        }
        
        cin >> selectionPieceToMove;
        cout << endl;
        
        originalCol = selectionPieceToMove[0] - 49;
        originalRow = selectionPieceToMove[1] - 97;
        
        
        if (board.playerToMove() == player1) {
            cout << p1 << " where would you like to move it?: ";
            
        }
        if (board.playerToMove() == player2) {
            cout << p2 << " where would you like to move it?: ";
            
        }
        
        cin >> selectionWhereToMove;
        cout << endl;
        
        finalCol = selectionWhereToMove[0] - 49;
        finalRow = selectionWhereToMove[1] - 97;
        
        result = board.makeMove(originalCol, originalRow, finalCol, finalRow);
        
        board.printBoard(cout);
    }
    
    
    
}

Board getBoard(string &p1, string &p2) {
    cout << "Player 1, enter your name: " << flush;
    getline(cin, p1);
    cout << endl << "Player 2, enter your name: " << flush;
    getline(cin, p2);
    
    
    return Board();
}
