#include "engine.h"
#include "user.h"

using namespace std;

int main() { // ne svetis suka (eclipse xuita) 2
	int board[8][8];
	int dbgboard[8][8];

	ChessUser *u = new ChessUser();

	Board *b = new Board();
	Debug *dbg = new Debug();
	b->clearBoard(board);
	//b->initBoard(board);

	dbg->namesMap();

	int src[2] = {4,4};
	board[src[0]][src[1]] = 2;

	//memcpy(dbgboard, board, 64*sizeof(int));
	memset(dbgboard, 0, 64*sizeof(int));
	dbgboard[src[0]][src[1]] = 2;

	for (int i=0; i<8; i++) {
		for (int j=0; j<8; j++) {
			int dst[2] = {i, j};
			if (b->checkMove(board, src, dst) == true) {
				dbgboard[i][j] = 1;
			} else {
				//printf("0 ");
			}
		}
		//printf("\n");
	}


//	//printf("%i\n", b->checkMove(board, src, dst));
	dbg->showBoard(dbgboard);

	try {

	TgBot::TgLongPoll poll(*u->bot);
	while (1) {
		poll.start();
	}

	} catch (TgBot::TgException& e) {
		printf("Error: %s\n", e.what());
		return -1;
	}
}
