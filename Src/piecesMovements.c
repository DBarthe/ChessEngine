/*
 * ChessEngine
 *
 * file piecesMovements.c in Src/
 *
 * This file contains the movement function of each kind of piece.
 */

#include "chess.h"
#include "movesList.h"
#include "ia.h"
#include "piecesMovements.h"

/*
 * Table of function pointers defined in Src/tableMovements.c
 */
extern MovementFunction tableMovements[];

/*
 * apply a movement on a board
 */
void applyMovement(Board board, Color color, Piece piece, Move move)
{
	bSet(board, move.srcX, move.srcY, 0);
	bSet(board, move.dstX, move.dstY, piece);

	switch (piece & PIECE_MASK)
	{
	case king:
		if ((board[ROCK_INDEX] & KING_BIT(color)) == 0)
		{
			if ((move.dstY == 0 && color == white) || (move.dstY == 7 && color == black))
			{
				if (move.dstY == 2)
				{
					bSet(board, 3, move.dstY, rock | color);
					bSet(board, 0, move.dstY, 0);
					board[ROCK_INDEX] |= LEFT_ROCK_BIT(color);
				}
				else if (move.dstY == 6)
				{
					bSet(board, 5, move.dstY, rock | color);
					bSet(board, 7, move.dstY, 0);
					board[ROCK_INDEX] |= RIGHT_ROCK_BIT(color);
				}
			}
			board[ROCK_INDEX] |= KING_BIT(color);
		}
		break;
	case rock:
		if ((move.srcY == 0 && color == white) || (move.srcY == 7 && color == black))
		{
			if (move.srcX == 0)
			{
				board[ROCK_INDEX] |= LEFT_ROCK_BIT(color);
			}
			else if (move.srcX == 7)
			{
				board[ROCK_INDEX] |= RIGHT_ROCK_BIT(color);
			}
		}
		break;
	case pawn:
		if (move.enpassant == ENPASSANT_DANGER)
			board[ENPASSANT_INDEX(color)] |= (1 << move.srcX);
		else if (move.enpassant == ENPASSANT_EAT)
			bSet(board, move.dstX, move.srcY, 0);
		else if (move.promotion)
			bSet(board, move.dstX, move.dstY, queen | color);
		break;
	default: break;
	}
}

/*
 * This function fills movesList with all movements the player can do
 */
MovesList *makeMovesList(Board board, Color color, MovesList *movesList)
{
	Case currentCase;
	int i, j;

	for (i = 0; i < SIDE_SIZE; i++)
	{
		for (j = 0; j < SIDE_SIZE; j++)
		{
			currentCase = bGet(board, i, j);
			if (currentCase && (currentCase & COLOR_MASK) == color)
			{
				(void)tableMovements[currentCase & PIECE_MASK](board, color, i, j, movesList);
			}
		}
	}
	return movesList;
}

/*
 * It's a routine for add*MovesToList() functions
 */
static inline void treatMove(Board board, Color color, MovesList *movesList, Move move)
{
	Piece currentPiece;

	currentPiece = bGet(board, move.dstX, move.dstY);
	if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
	{
		addMoveLink(movesList, move);
	}
}

/*
 * Adds movements, that the king in [srcX;srcY] can do, to movesList
 */
MovesList *addKingMovesToList(Board board, Color color, int srcX, int srcY, MovesList *movesList)
{
	Move move;

	/* set source position of move */
	move.srcX = srcX;
	move.srcY = srcY;
	move.promotion = 0;
	move.enpassant = 0;

	/* is the piece on the right side ? */
	move.dstX = srcX + 1;
	if (move.dstX < SIDE_SIZE)
	{
		/* right move */
		move.dstY = srcY;
		treatMove(board, color, movesList, move);

		/* right+up move*/
		move.dstY = srcY + 1;
		if (move.dstY < SIDE_SIZE)
		{
			treatMove(board, color, movesList, move);
		}

		/* right+down move*/
		if (srcY > 0)
		{
			move.dstY = srcY - 1;
			treatMove(board, color, movesList, move);
		}
	}

	/* is the piece on the left side ? */
	if (srcX > 0)
	{
		/* left move */
		move.dstX = srcX - 1;
		move.dstY = srcY;
		treatMove(board, color, movesList, move);

		/* left+up move */
		move.dstY = srcY + 1;
		if (move.dstY < SIDE_SIZE)
		{
			treatMove(board, color, movesList, move);
		}

		/* left+down move */
		if (srcY > 0)
		{
			move.dstY = srcY - 1;
			treatMove(board, color, movesList, move);
		}
	}

	/* up move */
	move.dstY = srcY + 1;
	if (move.dstY < SIDE_SIZE)
	{
		move.dstX = srcX;
		treatMove(board, color, movesList, move);
	}

	/* down move */
	move.dstY = srcY - 1;
	if (srcY > 0)
	{
		move.dstX = srcX;
		treatMove(board, color, movesList, move);
	}

	return movesList;
}

MovesList *addQueenMovesToList(Board board, Color color, int srcX, int srcY, MovesList *movesList)
{
	Move move;
	Piece currentPiece;

	/* set source position of move */
	move.srcX = srcX;
	move.srcY = srcY;
	move.promotion = 0;
	move.enpassant = 0;

	/* right moves */
	move.dstX = srcX + 1;
	move.dstY = srcY;
	while (move.dstX < SIDE_SIZE)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstX++;
	}

	/* left moves */
	move.dstX = srcX - 1;
	move.dstY = srcY;
	while (move.dstX >= 0)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstX--;
	}

	/* up moves */
	move.dstX = srcX;
	move.dstY = srcY + 1;
	while (move.dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstY++;
	}

	/* down moves */
	move.dstX = srcX ;
	move.dstY = srcY - 1;
	while (move.dstY >= 0)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstY--;
	}

	/* up + right moves */
	move.dstX = srcX + 1;
	move.dstY = srcY + 1;
	while (move.dstX < SIDE_SIZE && move.dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstX++;
		move.dstY++;
	}

	/* up + left moves */
	move.dstX = srcX - 1;
	move.dstY = srcY + 1;
	while (move.dstX >= 0 && move.dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstX--;
		move.dstY++;
	}

	/* down + right moves */
	move.dstX = srcX + 1;
	move.dstY = srcY - 1;
	while (move.dstX < SIDE_SIZE && move.dstY >= 0)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstX++;
		move.dstY--;
	}

	/* down + left moves */
	move.dstX = srcX - 1;
	move.dstY = srcY - 1;
	while (move.dstX >= 0 && move.dstY >= 0)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstX--;
		move.dstY--;
	}

	return movesList;
}

MovesList *addRockMovesToList(Board board, Color color, int srcX, int srcY, MovesList *movesList)
{
	Move move;
	Piece currentPiece;

	/* set source position of move */
	move.srcX = srcX;
	move.srcY = srcY;
	move.promotion = 0;
	move.enpassant = 0;

	// right
	move.dstX = srcX + 1;
	move.dstY = srcY;
	while (move.dstX < SIDE_SIZE)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstX++;
	}

	// left
	move.dstX = srcX - 1;
	move.dstY = srcY;
	while (move.dstX >= 0)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstX--;
	}

	//up
	move.dstX = srcX;
	move.dstY = srcY + 1;
	while (move.dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstY++;
	}

	// down
	move.dstX = srcX ;
	move.dstY = srcY - 1;
	while (move.dstY >= 0)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstY--;
	}

	return movesList;
}


MovesList *addBishopMovesToList(Board board, Color color, int srcX, int srcY, MovesList *movesList)
{
	Move move;
	Piece currentPiece;

	/* set source position of move */
	move.srcX = srcX;
	move.srcY = srcY;
	move.promotion = 0;
	move.enpassant = 0;

	// up + right
	move.dstX = srcX + 1;
	move.dstY = srcY + 1;
	while (move.dstX < SIDE_SIZE && move.dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstX++;
		move.dstY++;
	}

	// up + left
	move.dstX = srcX - 1;
	move.dstY = srcY + 1;
	while (move.dstX >= 0 && move.dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstX--;
		move.dstY++;
	}

	// down + right
	move.dstX = srcX + 1;
	move.dstY = srcY - 1;
	while (move.dstX < SIDE_SIZE && move.dstY >= 0)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstX++;
		move.dstY--;
	}

	// down + left
	move.dstX = srcX - 1;
	move.dstY = srcY - 1;
	while (move.dstX >= 0 && move.dstY >= 0)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		treatMove(board, color, movesList, move);
		if (currentPiece)
			break;
		move.dstX--;
		move.dstY--;
	}

	return movesList;
}

MovesList *addKnightMovesToList(Board board, Color color, int srcX, int srcY, MovesList *movesList)
{
	Move move;

	/* set source position of move */
	move.srcX = srcX;
	move.srcY = srcY;
	move.promotion = 0;
	move.enpassant = 0;

	// up + right
	move.dstX = srcX + 1;
	move.dstY = srcY + 2;
	if (move.dstX < SIDE_SIZE && move.dstY < SIDE_SIZE)
	{
		treatMove(board, color, movesList, move);
	}

	// up + left
	move.dstX = srcX - 1;
	move.dstY = srcY + 2;
	if (move.dstX >= 0 && move.dstY < SIDE_SIZE)
	{
		treatMove(board, color, movesList, move);
	}

	// down + right
	move.dstX = srcX + 1;
	move.dstY = srcY - 2;
	if (move.dstX < SIDE_SIZE && move.dstY >= 0)
	{
		treatMove(board, color, movesList, move);
	}

	// down + left
	move.dstX = srcX - 1;
	move.dstY = srcY - 2;
	if (move.dstX >= 0 && move.dstY >= 0)
	{
		treatMove(board, color, movesList, move);
	}

	// 2right + up
	move.dstX = srcX + 2;
	move.dstY = srcY + 1;
	if (move.dstX < SIDE_SIZE && move.dstY < SIDE_SIZE)
	{
		treatMove(board, color, movesList, move);
	}

	// 2right + down
	move.dstX = srcX + 2;
	move.dstY = srcY - 1;
	if (move.dstX < SIDE_SIZE && move.dstY >= 0)
	{
		treatMove(board, color, movesList, move);
	}

	// 2left + up
	move.dstX = srcX - 2;
	move.dstY = srcY + 1;
	if (move.dstX >= 0 && move.dstY < SIDE_SIZE)
	{
		treatMove(board, color, movesList, move);
	}

	// 2left + down
	move.dstX = srcX - 2;
	move.dstY = srcY - 1;
	if (move.dstX >= 0 && move.dstY >= 0)
	{
		treatMove(board, color, movesList, move);
	}

	return movesList;
}

MovesList *addPawnMovesToList(Board board, Color color, int srcX, int srcY, MovesList *movesList)
{
	Move move;
	Piece currentPiece;
	int way;

	/* set source position of move */
	move.srcX = srcX;
	move.srcY = srcY;
	move.promotion = 0;
	move.enpassant = 0;

	way = (color == white ? 1 : -1);

	move.dstY = srcY + way;
	if (move.dstY == 0 || move.dstY == SIDE_SIZE - 1)
		move.promotion = 1;

	// front
	move.dstX = srcX;
	if (move.dstY >= 0 && move.dstY < SIDE_SIZE && bGet(board, move.dstX, move.dstY) == 0)
	{
		addMoveLink(movesList, move);

		// front * 2
		if ((color == white && srcY == 1) || (color == black && srcY == 6))
		{
			move.dstY = srcY + 2*way;
			if (move.dstY >= 0 && move.dstY < SIDE_SIZE && bGet(board, move.dstX, move.dstY) == 0)
			{
				move.enpassant = ENPASSANT_DANGER;
				addMoveLink(movesList, move);
				move.enpassant = 0;
			}
		}
	}

	move.dstY = srcY + way;
	// front + right
	move.dstX = srcX + 1;
	if (move.dstX < SIDE_SIZE && move.dstY >= 0 && move.dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		if (currentPiece)
			treatMove(board, color, movesList, move);

		/* prise enpassant */
		if (((color == white && srcY == 4) || (color == black && srcY == 3)) && currentPiece && (board[ENPASSANT_INDEX(color ^ COLOR_ON)] & (1 << move.dstX)))
		{
			move.enpassant = ENPASSANT_EAT;
			addMoveLink(movesList, move);
			move.enpassant = 0;
		}
	}

	// front + left
	move.dstX = srcX - 1;
	if (move.dstX >= 0 && move.dstY >= 0 && move.dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, move.dstX, move.dstY);
		if (currentPiece)
			treatMove(board, color, movesList, move);

		/* prise en passant */
		if (((color == white && srcY == 4) || (color == black && srcY == 3)) && !currentPiece && (board[ENPASSANT_INDEX(color ^ COLOR_ON)] & (1 << move.dstX)))
		{
			move.enpassant = ENPASSANT_EAT;
			addMoveLink(movesList, move);
			move.enpassant = 0;
		}
	}

	return movesList;
}
