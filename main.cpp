#include "engine.h"

using namespace std;
int main() { // ne svetis suka (eclipse xuita) 2
	int board[8][8];
	int dbgboard[8][8];

	Board *b = new Board();
	Debug *dbg = new Debug();
	b ->clearBoard(board);
	b->initBoard(board);

	int src[2] = {2,1};
	board[src[0]][src[1]] = 7;

	memcpy(dbgboard, board, 64*sizeof(int));

	for (int i=0; i<8; i++) {
		for (int j=0; j<8; j++) {
			int dst[2] = {i, j};
			if (b->checkMove(board, src, dst, false) == true) {
				dbgboard[dst[0]][dst[1]] = 3;
			} else {
				//printf("0 ");
			}
		}
		//printf("\n");
	}


//	//printf("%i\n", b->checkMove(board, src, dst));
	dbg->showBoard(dbgboard);
	dbg->namesMap();
}
