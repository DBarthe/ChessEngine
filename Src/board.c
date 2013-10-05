/*
 * ChessEngine
 *
 * file board.c in Src/
 *
 * This file contains some useful functions to manipulate boards
 */

#include <stdio.h>
#include <string.h>
#include "chess.h"

/*
 * Clears board (fills it with zeros)
 */
void clearBoard(Board board)
{
	memset(board, 0, BOARD_SIZE * sizeof(Piece));
}

/*
 * Initializes a new game on the board,
 * sets pieces to starting position.
 */
void initBoard(Board board)
{
	clearBoard(board);

	bSet(board, _A , _1, rock | white);
	bSet(board, _B , _1, knight | white);
	bSet(board, _C , _1, bishop | white);
	bSet(board, _D , _1, queen | white);
	bSet(board, _E , _1, king | white);
	bSet(board, _F , _1, bishop | white);
	bSet(board, _G , _1, knight | white);
	bSet(board, _H , _1, rock | white);

	bSet(board, _A , _2, pawn | white);
	bSet(board, _B , _2, pawn | white);
	bSet(board, _C , _2, pawn | white);
	bSet(board, _D , _2, pawn | white);
	bSet(board, _E , _2, pawn | white);
	bSet(board, _F , _2, pawn | white);
	bSet(board, _G , _2, pawn | white);
	bSet(board, _H , _2, pawn | white);

	bSet(board, _A , _8, rock | black);
	bSet(board, _B , _8, knight | black);
	bSet(board, _C , _8, bishop | black);
	bSet(board, _D , _8, queen | black);
	bSet(board, _E , _8, king | black);
	bSet(board, _F , _8, bishop | black);
	bSet(board, _G , _8, knight | black);
	bSet(board, _H , _8, rock | black);

	bSet(board, _A , _7, pawn | black);
	bSet(board, _B , _7, pawn | black);
	bSet(board, _C , _7, pawn | black);
	bSet(board, _D , _7, pawn | black);
	bSet(board, _E , _7, pawn | black);
	bSet(board, _F , _7, pawn | black);
	bSet(board, _G , _7, pawn | black);
	bSet(board, _H , _7, pawn | black);
}

/*
 * Displays a piece. ("[color]piece")
 */
static void printPiece(Piece piece)
{
	if (piece == noPiece)
	{
		printf("    ");
	}
	else
	{
		switch (piece & COLOR_MASK)
		{
		case white: printf("[W]"); break;
		case black: printf("[B]"); break;
		}

		switch (piece & PIECE_MASK)
		{
		case king: printf("K"); break;
		case queen: printf("Q"); break;
		case rock: printf("R"); break;
		case bishop: printf("B"); break;
		case knight: printf("N"); break;
		case pawn: printf("P"); break;
		}
	}
}

#define DELIM '|'

/*
 * Displays a board.
 */
void printBoard(Board board)
{
	int i, j;

	printf("------------------------------------------\n");
	printf(" | a0 | b1 | c2 | d3 | e4| f5 | g6 | h7 |\n");
	for (j = SIDE_SIZE - 1; j >= 0; j--)
	{
		printf("%i", j);
		printf("%c", DELIM);
		for (i = 0; i < SIDE_SIZE; i++)
		{
			printPiece(bGet(board, i, j));
			printf("%c", DELIM);
		}
		printf("%i", j);
		printf("\n");
	}
	printf(" | a0 | b1 | c2 | d3 | e4 | f5 | g6 | h7 |\n");
	printf("------------------------------------------\n");
}
