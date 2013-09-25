/*
 * ChessEngine
 *
 * file movements.c in Src/
 *
 * This file contains the movement function of each kind of piece.
 */

#include "chess.h"
#include "movesList.h"
#include "ia.h"

/*static int ia_negamax_(Board board, Color color, int depth, int *alpha, int *beta, MovesList *move, int srcX, int srcY, int dstX, int dstY, Piece myPiece)
{
  Piece oldPiece;

  board[ENPASSANT_INDEX(color)] = 0;
  oldPiece = bGet(board, dstX, dstY);
  bSet(board, dstX, dstY, myPiece);
  printBoard(board);
  bSet(board, dstX, dstY, oldPiece);
  return (RET_MOVE);
  }*/


int ia_moveKing(Board board, Color color, int depth, int srcX, int srcY, Mark *alpha, Mark *beta, MovesList *move)
{
	int hasMove = RET_NOMOVE;
	int dstX, dstY;
	Piece myPiece;
	Piece currentPiece;

	myPiece = bGet(board, srcX, srcY);
	bSet(board, srcX, srcY, 0);

	if (srcX + 1 < SIDE_SIZE)
	{
		// right
		dstX = srcX+1;
		dstY = srcY;
		currentPiece = bGet(board, dstX, dstY);
		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (srcY + 1 < SIDE_SIZE)
		{
			// right+up
			dstX = srcX+1;
			dstY = srcY+1;
			currentPiece = bGet(board, dstX, dstY);
			if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
			{
				hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
				if (hasMove & RET_STOP)
				{
					bSet(board, srcX, srcY, myPiece);
					return (RET_STOP);
				}
			}
		}

		if (srcY > 0)
		{
			// right+down
			dstX = srcX+1;
			dstY = srcY-1;
			currentPiece = bGet(board, dstX, dstY);
			if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
			{
				hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
				if (hasMove & RET_STOP)
				{
					bSet(board, srcX, srcY, myPiece);
					return (RET_STOP);
				}
			}
		}
	}

	if (srcX > 0)
	{
		// left
		dstX = srcX-1;
		dstY = srcY;
		currentPiece = bGet(board, dstX, dstY);
		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}

		if (srcY + 1 < SIDE_SIZE)
		{
			// left+up
			dstX = srcX-1;
			dstY = srcY+1;
			currentPiece = bGet(board, dstX, dstY);
			if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
			{
				hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
				if (hasMove & RET_STOP)
				{
					bSet(board, srcX, srcY, myPiece);
					return (RET_STOP);
				}
			}
		}

		if (srcY > 0)
		{
			// left+down
			dstX = srcX-1;
			dstY = srcY-1;
			currentPiece = bGet(board, dstX, dstY);
			if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
			{
				hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
				if (hasMove & RET_STOP)
				{
					bSet(board, srcX, srcY, myPiece);
					return (RET_STOP);
				}
			}
		}
	}

	if (srcY + 1 < SIDE_SIZE)
	{
		// up
		dstX = srcX;
		dstY = srcY+1;
		currentPiece = bGet(board, dstX, dstY);
		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}

	}

	if (srcY > 0)
	{
		//down
		dstX = srcX;
		dstY = srcY-1;
		currentPiece = bGet(board, dstX, dstY);
		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
	}

	bSet(board, srcX, srcY, myPiece);
	return hasMove;
}


int ia_moveQueen(Board board, Color color, int depth, int srcX, int srcY, Mark *alpha, Mark *beta, MovesList *move)
{
	int hasMove = RET_NOMOVE;
	int dstX, dstY;
	Piece myPiece;
	Piece currentPiece;

	myPiece = bGet(board, srcX, srcY);
	bSet(board, srcX, srcY, 0);

	// right
	dstX = srcX + 1;
	dstY = srcY;
	while (dstX < SIDE_SIZE)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}

		}
		if (currentPiece)
			break;
		dstX++;
	}

	// left
	dstX = srcX - 1;
	dstY = srcY;
	while (dstX >= 0)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstX--;
	}

	//up
	dstX = srcX;
	dstY = srcY + 1;
	while (dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstY++;
	}

	// down
	dstX = srcX ;
	dstY = srcY - 1;
	while (dstY >= 0)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstY--;
	}

	// up + right
	dstX = srcX + 1;
	dstY = srcY + 1;
	while (dstX < SIDE_SIZE && dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstX++;
		dstY++;
	}

	// up + left
	dstX = srcX - 1;
	dstY = srcY + 1;
	while (dstX >= 0 && dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstX--;
		dstY++;
	}

	// down + right
	dstX = srcX + 1;
	dstY = srcY - 1;
	while (dstX < SIDE_SIZE && dstY >= 0)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstX++;
		dstY--;
	}

	// down + left
	dstX = srcX - 1;
	dstY = srcY - 1;
	while (dstX >= 0 && dstY >= 0)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstX--;
		dstY--;
	}

	bSet(board, srcX, srcY, myPiece);
	return hasMove;
}


int ia_moveRock(Board board, Color color, int depth, int srcX, int srcY, Mark *alpha, Mark *beta, MovesList *move)
{
	int hasMove = RET_NOMOVE;
	int dstX, dstY;
	Piece myPiece;
	Piece currentPiece;

	myPiece = bGet(board, srcX, srcY);
	bSet(board, srcX, srcY, 0);

	// right
	dstX = srcX + 1;
	dstY = srcY;
	while (dstX < SIDE_SIZE)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstX++;
	}

	// left
	dstX = srcX - 1;
	dstY = srcY;
	while (dstX >= 0)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstX--;
	}

	//up
	dstX = srcX;
	dstY = srcY + 1;
	while (dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstY++;
	}

	// down
	dstX = srcX ;
	dstY = srcY - 1;
	while (dstY >= 0)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstY--;
	}

	bSet(board, srcX, srcY, myPiece);
	return hasMove;
}

int ia_moveBishop(Board board, Color color, int depth, int srcX, int srcY, Mark *alpha, Mark *beta, MovesList *move)
{
	int hasMove = RET_NOMOVE;
	int dstX, dstY;
	Piece myPiece;
	Piece currentPiece;

	myPiece = bGet(board, srcX, srcY);
	bSet(board, srcX, srcY, 0);

	// up + right
	dstX = srcX + 1;
	dstY = srcY + 1;
	while (dstX < SIDE_SIZE && dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstX++;
		dstY++;
	}

	// up + left
	dstX = srcX - 1;
	dstY = srcY + 1;
	while (dstX >= 0 && dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstX--;
		dstY++;
	}

	// down + right
	dstX = srcX + 1;
	dstY = srcY - 1;
	while (dstX < SIDE_SIZE && dstY >= 0)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstX++;
		dstY--;
	}

	// down + left
	dstX = srcX - 1;
	dstY = srcY - 1;
	while (dstX >= 0 && dstY >= 0)
	{
		currentPiece = bGet(board, dstX, dstY);

		if (!currentPiece || ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
		if (currentPiece)
			break;
		dstX--;
		dstY--;
	}

	bSet(board, srcX, srcY, myPiece);
	return hasMove;
}

int ia_movePawn(Board board, Color color, int depth, int srcX, int srcY, Mark *alpha, Mark *beta, MovesList *move)
{
	int hasMove = RET_NOMOVE;
	int dstX, dstY;
	Piece myPiece, currentPiece;
	int way;

	way = (color == white ? 1 : -1);

	myPiece = bGet(board, srcX, srcY);
	bSet(board, srcX, srcY, 0);

	dstY = srcY + way;
	if (dstY == 0 || dstY == SIDE_SIZE - 1)
		myPiece = queen | color;

	// front
	dstX = srcX;
	if (dstY >= 0 && dstY < SIDE_SIZE && bGet(board, dstX, dstY) == 0)
	{
		hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
		if (hasMove & RET_STOP)
		{
			bSet(board, srcX, srcY, pawn | color);
			return (RET_STOP);
		}

		// front * 2
		if ((color == white && srcY == 1) || (color == black && srcY == 6))
		{
			dstY = srcY + 2*way;
			if (dstY >= 0 && dstY < SIDE_SIZE && bGet(board, dstX, dstY) == 0)
			{
				board[ENPASSANT_INDEX(color)] |= (1 << srcX);
				hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
				board[ENPASSANT_INDEX(color)] &= ~(1 << srcX);
				if (hasMove & RET_STOP)
				{
					bSet(board, srcX, srcY, pawn | color);
					return (RET_STOP);
				}
			}
		}
	}

	dstY = srcY + way;
	// front + right
	dstX = srcX + 1;
	if (dstX < SIDE_SIZE && dstY >= 0 && dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, dstX, dstY);
		if (currentPiece && ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, pawn | color);
				return (RET_STOP);
			}
		}
		else if (((color == white && srcY == 4) || (color == black && srcY == 3)) && currentPiece && (board[ENPASSANT_INDEX(color ^ COLOR_ON)] & (1 << dstX)))
		{
			bSet(board, dstX, dstY - way, 0);
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, pawn | color);
				return (RET_STOP);
			}
			bSet(board, dstX, dstY - way, pawn | (color^COLOR_ON));
		}
	}

	// front + left
	dstX = srcX - 1;
	if (dstX >= 0 && dstY >= 0 && dstY < SIDE_SIZE)
	{
		currentPiece = bGet(board, dstX, dstY);
		if (currentPiece && ((currentPiece & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, pawn | color);
				return (RET_STOP);
			}
		}
		else if (((color == white && srcY == 4) || (color == black && srcY == 3)) && !currentPiece && (board[ENPASSANT_INDEX(color ^ COLOR_ON)] & (1 << dstX)))
		{
			bSet(board, dstX, dstY - way, 0);
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			bSet(board, dstX, dstY - way, pawn | (color^COLOR_ON));
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, pawn | color);
				return (RET_STOP);
			}
		}
	}

	bSet(board, srcX, srcY, pawn | color); // because 'myPiece' could be a promotion
	return hasMove;
}

int ia_moveKnight(Board board, Color color, int depth, int srcX, int srcY, Mark *alpha, Mark *beta, MovesList *move)
{
	int hasMove = RET_NOMOVE;
	int dstX, dstY;
	Piece myPiece;

	myPiece = bGet(board, srcX, srcY);
	bSet(board, srcX, srcY, 0);

	// up + right
	dstX = srcX + 1;
	dstY = srcY + 2;
	if (dstX < SIDE_SIZE && dstY < SIDE_SIZE)
	{
		if (bGet(board, dstX, dstY) == 0 || ((bGet(board, dstX, dstY) & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
	}

	// up + left
	dstX = srcX - 1;
	dstY = srcY + 2;
	if (dstX >= 0 && dstY < SIDE_SIZE)
	{
		if (bGet(board, dstX, dstY) == 0 || ((bGet(board, dstX, dstY) & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
	}

	// down + right
	dstX = srcX + 1;
	dstY = srcY - 2;
	if (dstX < SIDE_SIZE && dstY >= 0)
	{
		if (bGet(board, dstX, dstY) == 0 || ((bGet(board, dstX, dstY) & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
	}

	// down + left
	dstX = srcX - 1;
	dstY = srcY - 2;
	if (dstX >= 0 && dstY >= 0)
	{
		if (bGet(board, dstX, dstY) == 0 || ((bGet(board, dstX, dstY) & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
	}

	// 2right + up
	dstX = srcX + 2;
	dstY = srcY + 1;
	if (dstX < SIDE_SIZE && dstY < SIDE_SIZE)
	{
		if (bGet(board, dstX, dstY) == 0 || ((bGet(board, dstX, dstY) & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
	}

	// 2right + down
	dstX = srcX + 2;
	dstY = srcY - 1;
	if (dstX < SIDE_SIZE && dstY >= 0)
	{
		if (bGet(board, dstX, dstY) == 0 || ((bGet(board, dstX, dstY) & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
	}

	// 2left + up
	dstX = srcX - 2;
	dstY = srcY + 1;
	if (dstX >= 0 && dstY < SIDE_SIZE)
	{
		if (bGet(board, dstX, dstY) == 0 || ((bGet(board, dstX, dstY) & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
	}

	// 2left + down
	dstX = srcX - 2;
	dstY = srcY - 1;
	if (dstX >= 0 && dstY >= 0)
	{
		if (bGet(board, dstX, dstY) == 0 || ((bGet(board, dstX, dstY) & COLOR_MASK) ^ color))
		{
			hasMove |= ia_negamaxBack(board, color, depth, alpha, beta, move, srcX, srcY, dstX, dstY, myPiece);
			if (hasMove & RET_STOP)
			{
				bSet(board, srcX, srcY, myPiece);
				return (RET_STOP);
			}
		}
	}

	bSet(board, srcX, srcY, myPiece);
	return hasMove;
}
