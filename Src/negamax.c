/*
 * ChessEngine
 *
 * file negamax.c in Src/
 *
 * This file contains the main algorithm of the engine.
 */

#include <stdlib.h>
#include "chess.h"
#include "macros.h"
#include "ia.h"
#include "piecesMovements.h"

/*
 * Returns the mark of the node (board) applying
 * a search with a depth passed in parameter.
 * It's the main algorithm of the engine
 */
Mark negamax(Board board, Color color, int depth, Mark alpha, Mark beta)
{
	MovesList movesList;
	MoveLink *moveLink;
	Mark tmp;
	int hasMove;
	Case enpassant;
	Piece oldPiece, myPiece;
	Move move;
	Case rocksInfoSave;

	if (depth < 1)
	{
		return (eval(board, color));
	}
	else
	{
		movesList = newMovesList();
		setMovesListEmpty(&movesList);
		hasMove = RET_NOMOVE;
		enpassant = board[ENPASSANT_INDEX(color)];
		board[ENPASSANT_INDEX(color)] = 0;

		makeMovesList(board, color, &movesList);
		for (moveLink = movesList.head; moveLink != NULL; moveLink = moveLink->next)
		{
			move = moveLink->move;
			myPiece = bGet(board, move.srcX, move.srcY);
			oldPiece = bGet(board, move.dstX, move.dstY);

			//printf("move src={%d;%d} dst={%d;%d}\n", move.srcX, move.srcY, move.dstX, move.dstY);

			if ((oldPiece & PIECE_MASK) == king)
			{
				//printf("eat king\n");
				board[ENPASSANT_INDEX(color)] = enpassant;
				setMovesListEmpty(&movesList);
				return MARK_MAX;
			}

			rocksInfoSave = board[ROCK_INDEX];
			applyMovement(board, color, myPiece, move);

			tmp = -negamax(board, color^COLOR_ON, depth-1, -beta, -alpha);

			bSet(board, move.srcX, move.srcY, myPiece);
			bSet(board, move.dstX, move.dstY, oldPiece);
			if (move.enpassant == ENPASSANT_DANGER)
				board[ENPASSANT_INDEX(color)] &= ~(1 << move.srcX);
			else if (move.enpassant == ENPASSANT_EAT)
				bSet(board, move.dstX, move.srcY, pawn | (color ^ COLOR_ON));
			board[ROCK_INDEX] = rocksInfoSave;

			if (tmp > alpha)
			{
				hasMove = RET_MOVE;
				alpha = tmp;
			}

			if (alpha > beta)
			{
				board[ENPASSANT_INDEX(color)] = enpassant;
				setMovesListEmpty(&movesList);
				return alpha;
			}
		}

	}

	if (hasMove == RET_NOMOVE && alpha == MARK_MIN)
	{
		if (-negamax(board, color^COLOR_ON, 1, MARK_MIN, MARK_MAX) == MARK_MIN)
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

	board[ENPASSANT_INDEX(color)] = enpassant;
	setMovesListEmpty(&movesList);

	return alpha;
}
