/*
 * ChessEngine
 *
 * file ia.c in Src/
 */

#include "macros.h"
#include "chess.h"
#include "movesList.h"
#include "ia.h"
#include "movements.h"

/*
 * Table of function pointers defined in Src/tableMovements.c
 */
extern MovementFunction tableMovements[];

int ia_search(Board board, Color color, int depth)
{
	Mark alpha = MARK_MIN;
	Mark beta = MARK_MAX;
	int i, j;
	int move_ret = RET_NOMOVE;
	Case currentCase;
	Case enpassant;
	MovesList movesList;
	Move move;

	movesList = newMovesList();

	IFDEBUG(printf("search: color=%d depth=%d alpha=%d beta=%d\n", color, depth, alpha, beta));

	enpassant = board[ENPASSANT_INDEX(color)];
	board[ENPASSANT_INDEX(color)] = 0;

	for (j = 0; j < SIDE_SIZE; j++)
	{
		for (i = 0; i < SIDE_SIZE; i++)
		{
			currentCase = bGet(board, i, j);
			if (currentCase && (currentCase & COLOR_MASK) == color)
			{
				IFDEBUG(printf("negamax: move piece (%d;%d)\n", i, j));
				if ((move_ret |=
						tableMovements[currentCase & PIECE_MASK]
						               (board, color, depth, i, j, &alpha, &beta, &movesList)) & RET_STOP)
				{
					IFDEBUG(printf("negamax: move function returns RET_STOP\n"));
					board[ENPASSANT_INDEX(color)] = enpassant;
					return 3;
				}
			}
		}
	}

	if ((move_ret == RET_NOMOVE) && alpha == MARK_MIN)
	{
		if (-ia_negamax(board, color^COLOR_ON, 1, -beta, -alpha) == MARK_MIN)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}

	IFDEBUG(printf("negamax: natural return, alpha=%d beta=%d\n", alpha, beta));
	board[ENPASSANT_INDEX(color)] = enpassant;

	move = getRandomMove(&movesList);
	setMovesListEmpty(&movesList);
	bSet(board, move.dstX, move.dstY, move.promotion ? (queen | color) : bGet(board, move.srcX, move.srcY));
	bSet(board, move.srcX, move.srcY, 0);

	printf("movement: (%d;%d)=>(%d;%d)\n", move.srcX, move.srcY, move.dstX, move.dstY);

	return 0;
}

