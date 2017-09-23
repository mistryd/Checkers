#include "board.h"

using namespace std;

Board::Board() {

	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {

			board[i][j] = empty;
		}
	}
}