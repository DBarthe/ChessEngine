/*
 * ChessEngine
 *
 * file chess.c in Src/
 *
 * Contains generals functions about the chess game
 */

#include "chess.h"

/*
 *	Returns 1 if the game is ended
 *
 *	The game is considerate as ended when
 *	pieces are insufficient to result in mat or pat
 */
int gameIsEnded(Board board)
{
	int i, j;
	int oneHead;

	oneHead = 0;
	for (i = 0; i < SIDE_SIZE; i++)
	{
		for (j = 0; j < SIDE_SIZE; j++)
		{
			switch (bGet(board, i, j) & PIECE_MASK)
			{
			case knight:
			case bishop:
				if (oneHead)
					return 0;
				oneHead = 1;
				break;
			case noPiece:
			case king:
				break;
			default:
				return 0;
			}
		}
	}

	return 1;
}
