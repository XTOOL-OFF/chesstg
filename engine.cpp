#include "engine.h"

using namespace std;

// board and main engine

Board::Board() {
}

Debug::Debug() {
}
void Board::initBoard(int board[8][8]) {
	clearBoard(board);

	// kon,slon,ladia
	for (int i=0; i<3; i++) {
		board[0][i] = 11-i;
		board[0][7-i] = 11-i;
		board[7][i] = 5-i;
		board[7][7-i] = 5-i;
	}

	// korol/koroleva
	board[0][4] = 8;
	board[0][3] = 7;
	board[7][4] = 1;
	board[7][3] = 2;

	// peshka
	for (int i=0; i<8; i++) {
		board[1][i] = 12;
		board[6][i] = 6;
	}
}

void Board::clearBoard(int board[8][8]) {
	memset(board, 0, sizeof(int) * 64);
}

void Board::move(int board[8][8], int src[2], int dst[2]) {
	int piece = board[src[0]][src[1]];
	board[src[0]][src[1]] = 0;
	board[dst[0]][dst[1]] = piece;
}

bool Board::checkMove(int board[8][8], int src[2], int dst[2], bool firstmove, int piece) {
	if (piece == -1) {
		piece = board[src[0]][src[1]];
	}

	if (src[0] == dst[0] && src[1] == dst[1]) {
		return false;
	}

	bool empty = true;

	if (piece == 5 || piece == 11) {        // ladia move check
		if (src[0] != dst[0] && src[1] == dst[1]) {   // if move only in one direction[x]
			for (int i=src[0]+1; i<dst[0]; i++) {
				if (board[i][src[1]] != 0) {
					empty = false;      // not empty field
				}
			}
		} else if (src[0] == dst[0] && src[1] != dst[1]) {  // if move only in one direction[y]
			//printf("%i %i %i %i\n", src[0], src[1], dst[0], dst[1]);
			for (int i=src[1]+1; i<dst[1]; i++) {
				if (board[src[0]][i] != 0) {
					empty = false;      // not empty field
				}
			}
		} else {
			return false;
		}
		return empty;
	}
	if (piece == 4 || piece == 10) {
		if ((src[0] + 2 == dst[0] && src[1] - 1 == dst[1]) ||
			(src[0] + 2 == dst[0] && src[1] + 1 == dst[1]) ||
			(src[0] + 1 == dst[0] && src[1] - 2 == dst[1]) ||
			(src[0] + 1 == dst[0] && src[1] + 2 == dst[1]) ||     // kon logic
			(src[0] - 1 == dst[0] && src[1] + 2 == dst[1]) ||
			(src[0] - 1 == dst[0] && src[1] - 2 == dst[1]) ||
			(src[0] - 2 == dst[0] && src[1] + 1 == dst[1]) ||
			(src[0] - 2 == dst[0] && src[1] - 1 == dst[1])) {
			return true;
		}
		return false;
	}
	if (piece == 3 || piece == 9) {         // slon logic

		if (abs(src[0]-dst[0]) != abs(src[1]-dst[1])) {
			//printf("%i %i %i %i\n", src[0], src[1], dst[0], dst[1]);
			//printf("%i\n", abs(src[0]-dst[0]));
			//printf("%i\n", abs(src[1]-dst[1]));
			return false;
		}
		int temp = dst[0]-src[0];
		//printf("%i\n", temp);
		if (temp > 0) {
			for(int i=1; i<temp; i++) {
				if (board[i+src[0]][i+src[1]] != 0) {
					empty = false;
				}
			}
		} else {
			for(int i=-1; i>temp; i--) {
				if (board[i+src[0]][i+src[1]] != 0) {
					empty = false;
				}
			}
		}
		return empty;
	}

	if (piece == 6) {                                                       // peshka WHITE
		if ((src[0] - 1 == dst[0] && src[1] == dst[1]) ||
			(firstmove == true && src[0] - 2 == dst[0] && src[1] == dst[1]) ||
			(src[0] - 1 == dst[0] && src[1] + 1 == dst[1]) ||
			(src[0] - 1 == dst[0] && src[1] - 1 == dst[1])) {
			if (src[1] == dst[1]) {
				if (board[dst[0]][src[1]] == 0 && dst[0] + 2 == src[0] && firstmove == true) {
					return true;
				} else if (board[dst[0]][src[1]] == 0 && dst[0] + 1 == src[0]) {
					return true;
				} else {
					return false;
				}
			} else {
				if (board[dst[0]][dst[1]] != 0) {
					return true;
				} else {
					return false;
				}
			}
		}
	}
	if (piece == 12) {                                                        // peshka BLACK
			if ((src[0] + 1 == dst[0] && src[1] == dst[1]) ||
				(firstmove == true && src[0] + 2 == dst[0] && src[1] == dst[1]) ||
				(src[0] + 1 == dst[0] && src[1] + 1 == dst[1]) ||
				(src[0] + 1 == dst[0] && src[1] - 1 == dst[1])) {
				if (src[1] == dst[1]) {
					if (board[dst[0]][src[1]] == 0 && dst[0] - 2 == src[0] && firstmove == true) {
						return true;
					} else if (board[dst[0]][src[1]] == 0 && dst[0] - 1 == src[0]) {
						return true;
					} else {
						return false;
					}
				} else {
					if (board[dst[0]][dst[1]] != 0) {
						return true;
					} else {
						return false;
					}
				}
			}
		}

	if (piece == 1 || piece == 7) {
		if ((src[0] + 1 == dst[0] && src[1] == dst[1]) ||
			(src[0] - 1 == dst[0] && src[1] == dst[1]) ||
			(src[0] == dst[0] && src[1] + 1 == dst[1]) ||
			(src[0] == dst[0] && src[1] - 1 == dst[1])) {
			return true;
		}
	}

	if (piece == 2 || piece == 8) {
		Board *b = new Board();
		if (b->checkMove(board, src, dst, false, 5) ||
			b->checkMove(board, src, dst, false, 3)) {
			return true;
		}
	}

	return false;
}

// debug funcs

void Debug::showBoard(int board[8][8]) {
	printf("\n");
	for (int i=0; i<8; i++) {
		for (int j=0; j<8; j++) {
			printf("%i ", board[i][j]);
		}
		printf("\n");
	}
}

void Debug::namesMap() {
	Board *b = new Board();
	int len = sizeof(b->names)/sizeof(b->names[0]);
	for (int i=0; i<len; i++) {
		printf("%i %s | ", i, b->names[i].c_str());
	}
}

