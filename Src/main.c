#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess.h"
#include "ia.h"
#include "piecesMovements.h"

extern void printBoard(Board board);
extern void clearBoard(Board board);
extern void initBoard(Board board);

static void gameSimultating(Board board)
{
	int ret;
	int stop = 0;
	Color color;
	Move move;

	initBoard(board);
	printBoard(board);

	color = white;
	while (!stop)
	{
		ret = search(board, color, color == white ? 4 : 4, &move);
		switch (ret)
		{
		case SEARCH_OK:
			applyMovement(board, color, bGet(board, move.srcX, move.srcY), move);
			break;
		case SEARCH_MAT: stop = 1; printf("%d win\n", color^COLOR_ON); break;
		case SEARCH_PAT: ; stop = 1; printf("null\n"); break;
		case SEARCH_ERROR: stop = 1; printf("strange\n"); break;
		}
		if (stop)
			break;
		printf("color = %d: src{%d;%d} dst{%d;%d}\n", color, move.srcX, move.srcY, move.dstX, move.dstY);
		printBoard(board);
		color ^= COLOR_ON;
		//sleep(1);
	}
}

int main(void)
{
	Board board;

	gameSimultating(board);
	/*
  initBoard(board);
  printBoard(board);
  //ia_negamax(board, black, 1, MARK_MIN, MARK_MAX);
  ia_search(board, white, 9);
  printf("------------------------------\nchoice = \n");
  printBoard(board);
	 */
	return 0;
}
