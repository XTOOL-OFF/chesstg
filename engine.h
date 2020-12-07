#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <string.h>

using namespace std;

class Board {

public:
	Board();
	const string names[14] = {"\u2b1b", "\u2b1c", "\u2654", "\u2655", "\u2657", "\u2658", "\u2656", "\u2659",
						"\u265A", "\u265B", "\u265D", "\u265E", "\u265C", "\u265F"}; //parasha 2
	void initBoard(int board[8][8]);
	void move(int board[8][8], int src[2], int dst[2]);
	bool checkMove(int board[8][8], int src[2], int dst[2], int piece=-1);
	void clearBoard(int board[8][8]);

private:
	bool isEmpty(int piece);
};

class Debug {

public:
	Debug();
	void showBoard(int board[8][8]);
	void namesMap();
};

#endif /* ENGINE_H_ */
