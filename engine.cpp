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
		board[0][i] = 12-i;
		board[0][7-i] = 12-i;
		board[7][i] = 6-i;
		board[7][7-i] = 6-i;
	}

	// korol/koroleva
	board[0][4] = 8;
	board[0][3] = 9;
	board[7][4] = 2;
	board[7][3] = 3;

	// peshka
	for (int i=0; i<8; i++) {
		board[1][i] = 13;
		board[6][i] = 7;
	}
}

void Board::clearBoard(int board[8][8]) {
	int b = 0, w = 1;

	for (int i=0; i<8; i++) {
		for (int j=0; j<8; j++) {
			if (j % 2 == 0)
				board[i][j] = w;     // white square
			else
				board[i][j] = b;     // black square
		}
		b = !b;
		w = !w;
	}
}

void Board::move(int board[8][8], int src[2], int dst[2]) {
	int piece = board[src[0]][src[1]];
	if ((src[0] + src[1]) % 2 == 0)
		board[src[0]][src[1]] = 1;
	else
		board[src[0]][src[1]] = 0;
	board[dst[0]][dst[1]] = piece;
}

bool Board::checkMove(int board[8][8], int src[2], int dst[2], int piece) {
	if (piece == -1) {
		piece = board[src[0]][src[1]];
	}

	int dstpiece = board[dst[0]][dst[1]];

	if (src[0] == dst[0] && src[1] == dst[1]) {
		return false;
	}

	bool empty = true;

	if (piece == 6 || piece == 12) {        // ladia move check
		if (src[0] != dst[0] && src[1] == dst[1]) {   // if move only in one direction[x]
			for (int i=src[0]+1; i<dst[0]; i++) {
				if (board[i][src[1]] != 0 && board[i][src[1]] != 1) {
					empty = false;      // not empty field
				}
			}
		} else if (src[0] == dst[0] && src[1] != dst[1]) {  // if move only in one direction[y]
			//printf("%i %i %i %i\n", src[0], src[1], dst[0], dst[1]);
			for (int i=src[1]+1; i<dst[1]; i++) {
				if (board[src[0]][i] != 0 && board[src[0]][i] != 1) {
					empty = false;      // not empty field
				}
			}
		} else {
			return false;
		}
		return empty;
	}
	if (piece == 5 || piece == 11) {    //kon logic
		int x = abs(src[0] - dst[0]);
        int y = abs(src[1] - dst[1]);

		if ((x == 1 && y == 2) ||
			(x == 2 && y == 1)) {
			return true;
		}
		return false;
	}
	if (piece == 4 || piece == 10) {         // slon logic

		if (abs(src[0]-dst[0]) != abs(src[1]-dst[1]))
			return false;

		int temp = dst[0]-src[0];
		//printf("%i\n", temp);
		if (temp > 0) {
			for(int i=1; i<temp; i++) {
				empty = isEmpty(board[i+src[0]][i+src[1]]);
			}
		} else {
			for(int i=-1; i>temp; i--) {
				empty = isEmpty(board[i+src[0]][i+src[1]]);
			}
		}
		return empty;
	}

	if (piece == 7 || piece == 13) {  // peshki

		int c;
		if (piece == 7) // black
			c = 1;
		else
			c = -1; // white

		if (src[0] + (2*c) == dst[0] && src[1] == dst[1]) { // starting
			if (src[0] == 1 || src[0] == 6)
				return true;
		}

		if (src[0] + c == dst[0] && src[1] == dst[1]) {
			return isEmpty(dstpiece);
		}

		if (src[0] + c == dst[0] && src[1] - c == dst[1]) { // diagonal
			return !isEmpty(dstpiece);
		}
	}

	if (piece == 2 || piece == 8) { // korol

		int x = src[0] - dst[0];
		int y = src[1] - dst[1];

		if ((abs(x) == 1 && y == 0) ||
			(x == 0 && abs(y) == 1) ||
			(abs(x) == 1 && abs(y) == 1)) {

			return true;
		}
	}

	if (piece == 3 || piece == 9) { // koroleva
		//Board *b = new Board();
		if (checkMove(board, src, dst, 5) ||
			checkMove(board, src, dst, 3)) {
			return true;
		}
	}

	return false;
}

bool Board::isEmpty(int piece) {
	return (piece == 0 || piece == 1);
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

