/*
 * ChessEngine
 *
 * file main.c in Src/
 *
 * This file contain the main function of the project
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess.h"
#include "ia.h"
#include "piecesMovements.h"
#include "rand.h"

extern void printBoard(Board board);
extern void clearBoard(Board board);
extern void initBoard(Board board);

static void testPieceMovements(Board board, Piece piece, int srcX, int srcY)
{
	MovesList list;
	MoveLink *link;

	clearBoard(board);
	bSet(board, srcX, srcY, piece);

	list = newMovesList();

	makeMovesList(board, piece & COLOR_MASK, &list);
	for (link = list.head; link; link = link->next)
	{
		applyMovement(board, piece & COLOR_MASK, piece, link->move);
	}
	printBoard(board);
}

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
		ret = search(board, color, 4, &move);
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
		if (gameIsEnded(board))
		{
			printf("null\n");
			stop = 1;
		}
	}
}

int main(void)
{
	Board board;

	initSeed();
	gameSimultating(board);

	return 0;
}
