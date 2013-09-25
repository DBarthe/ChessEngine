/*
 * ChessEngine
 *
 * file negamax.c in Src/
 *
 * This file contains the main algorithm of the engine.
 * The function ia_negamax(), called first,
 * moves each 'color' piece in each position they can go,
 * calling movements functions(defined in 'movements.c).
 * Then, movements functions call back ia_negamaxBack().
 */

#include <stdlib.h>
#include "chess.h"
#include "macros.h"
#include "ia.h"

/*
 * Table of function pointers defined in Src/tableMovements.c
 */
extern MovementFunction tableMovements[];

/*
 * This function is a sub routine of the main negamax algorithm.
 * It's called back by movements function after moving a piece.
 * Returns an integer which informing on the piece movement.
 * 	values: RET_MOVE,
 * 			RET_NOMOVE,
 * 		 or RET_STOP if the target position contains a king or if alpha >= beta
 */
int ia_negamaxBack(Board board, Color color, int depth,
		Mark *alpha, Mark *beta, MovesList *move,
		int srcX, int srcY, int dstX, int dstY,
		Piece myPiece)
{
	Piece oldPiece;
	Mark tmp;
	int hasMove = RET_NOMOVE;

	IFDEBUG(printf("negamaxBack: color=%d depth=%d alpha=%d beta=%d | src(%d;%d) dst(%d:%d)\n", color, depth, *alpha, *beta, srcX, srcY, dstX, dstY));

	oldPiece = bGet(board, dstX, dstY);
	if ((oldPiece & PIECE_MASK) == king)
	{
		IFDEBUG_PRINT("negamaxBack: KING EATEN");
		*alpha = MARK_MAX;
		return RET_STOP;
	}

	bSet(board, dstX, dstY, myPiece);

	IFDEBUG(printBoard(board));

	tmp = -ia_negamax(board, color^COLOR_ON, depth-1, -(*beta), -(*alpha));

	if (tmp >= *alpha) // AND IMPLICITLY KING NOT EATEN
	{
		if (tmp > *alpha)
		{
			setMovesListEmpty(move);
		}
		hasMove = RET_MOVE;
		*alpha = tmp;
		if (move)
		{
			addMoveLink(move, (Move){srcX, srcY, dstX, dstY, 0});
		}
	}IFDEBUG(else { printf("negamaxBack: no move !(tmp(%d) > alpha(%d))\n", tmp, *alpha); })

	bSet(board, dstX, dstY, oldPiece);

	if (*alpha >= *beta)
	{
		IFDEBUG(printf("negamaxBack: alpha(%d) >= beta(%d) (return stop)\n", *alpha, *beta));
		return RET_STOP;
	}
	return hasMove;
}

/*
 * Returns the mark of the node (board) applying
 * a search with a depth passed in parameter.
 */
Mark ia_negamax(Board board, Color color, int depth, Mark alpha, Mark beta)
{
	int i, j;
	Case currentCase;
	int move_ret = 0;
	Case enpassant;

	IFDEBUG(printf("negamax: color=%d depth=%d alpha=%d beta=%d\n", color, depth, alpha, beta));

	enpassant = board[ENPASSANT_INDEX(color)];
	board[ENPASSANT_INDEX(color)] = RET_NOMOVE;


	if (depth < 1)
	{
		Mark mark;
		mark = ia_eval(board, color);
		IFDEBUG(printf("return color=%d eval=%d\n", color, mark));
		return mark;
		//return (ia_eval(board, color));
	}
	else
	{
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
							               (board, color, depth, i, j, &alpha, &beta, NULL)) & RET_STOP)
					{
						IFDEBUG(printf("negamax: move function returns RET_STOP\n"));
						board[ENPASSANT_INDEX(color)] = enpassant;
						return alpha;
					}
				}
			}
		}
	}

	if (move_ret == RET_NOMOVE && alpha == MARK_MIN)
	{
		IFDEBUG(printf("negamax: can't move anywhere (and alpha == MARK_MIN) ..."));
		if (-ia_negamax(board, color^COLOR_ON, 1, -beta, -alpha) == MARK_MIN)
		{
			IFDEBUG_PRINT("MAT");
			alpha = MARK_MAT_LOSE;
		}
		else
		{
			IFDEBUG_PRINT("PAT");
			alpha = MARK_PAT;
		}
	}
	IFDEBUG(printf("negamax: natural return, alpha=%d beta=%d\n", alpha, beta));
	board[ENPASSANT_INDEX(color)] = enpassant;
	return alpha;
}
