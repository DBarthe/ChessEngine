/*
 * ChessEngine
 *
 * file ia.c in Src/
 */

#include <stdlib.h>
#include <stdio.h>
#include "macros.h"
#include "chess.h"
#include "movesList.h"
#include "ia.h"
#include "piecesMovements.h"

/*
 * Starts a search. Depth is passed in parameter.
 * The select move is store in the 'Move *moveBuffer'
 * The parameter 'color' indicates the player on move.
 *
 * Returns integer defined as macros in Includes/ia.h
 * 		- SEARCH_OK		in a normal case (a move has been select)
 *		- SEARCH_MAT	if the player on move is mat
 *		- SEARCH_PAT	if the player on move can't play (and is not mat)
 *		- SEARCH_ERROR	if the board is invalid (example: the opposing king is edible)
 *
 */
int search(Board board, Color color, int depth, Move *moveBuffer)
{
	MovesList movesList, resultsList;
	MoveLink *moveLink;
	Mark alpha,tmp;
	int hasMove;
	Case enpassant;
	Piece oldPiece, myPiece;
	Move move;
	int retValue;
	Case rocksInfoSave;

	movesList = newMovesList();
	resultsList = newMovesList();

	alpha = MARK_MIN;
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

		if ((oldPiece & PIECE_MASK) == king)
		{
			board[ENPASSANT_INDEX(color)] = enpassant;
			setMovesListEmpty(&resultsList);
			setMovesListEmpty(&movesList);
			return SEARCH_ERROR;
		}

		rocksInfoSave = board[ROCK_INDEX];
		applyMovement(board, color, myPiece, move);
		tmp = -negamax(board, color^COLOR_ON, depth-1, MARK_MIN, -alpha);
		undoMovement(board, color, move, myPiece, oldPiece, rocksInfoSave);

		if (tmp > alpha || (alpha == tmp && alpha > MARK_MIN))
		{
			if (tmp != alpha)
			{
				setMovesListEmpty(&resultsList);
				alpha = tmp;
			}
			addMoveLink(&resultsList, move);
			hasMove = RET_MOVE;
		}
	}

	if (hasMove == RET_NOMOVE)
	{
		if (-negamax(board, color^COLOR_ON, 1, MARK_MIN, MARK_MAX) == MARK_MIN)
			retValue = SEARCH_MAT;
		else
			retValue = SEARCH_PAT;
	}
	else
	{
		if (moveBuffer)
			*moveBuffer = getRandomMove(&resultsList);
		retValue = SEARCH_OK;
	}

	board[ENPASSANT_INDEX(color)] = enpassant;
	setMovesListEmpty(&resultsList);
	setMovesListEmpty(&movesList);

	return retValue;
}
