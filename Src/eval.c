/*
 * ChessEngine
 *
 * file eval.c in Src/
 *
 * This file contains the evaluation function of the engine
 *
 */

#include "chess.h"
#include "ia.h"

#define MATERIAL_COEF 1
#define CENTER_CONTROL_COEF 1

/*
 * This table contains the material values of each kind of piece.
 * There are stored with the form "piece => value"
 *
 */
static Mark tableMaterialValues[] = {
		0,
		KING_VALUE,
		QUEEN_VALUE,
		ROCK_VALUE,
		BISHOP_VALUE,
		KNIGHT_VALUE,
		PAWN_VALUE
};

/*
 * Returns the material value of the parameter 'piece'
 *
 * TODO: differentiates positions and openings for different kind of piece
 */
static Mark materialValueOf(Piece piece)
{
	return tableMaterialValues[piece & PIECE_MASK];
}

/*
 * Returns the color sign of the parameter 'piece'
 * The sign is 1 if the piece color is the same than 'myColor', else it's -1
 */
static Mark colorSignOf(Piece piece, Color myColor)
{
	if ((piece & COLOR_MASK) ^ myColor)
	{
		return -1;
	}
	return 1;
}

/*
 * Returns the material evaluation of the board for the parameter 'color'
 */
static Mark evalMaterial(Board board, Color color)
{
	Mark mark = 0;
	Piece piece;
	int x, y;

	for (x = 0; x < SIDE_SIZE; x++)
	{
		for (y = 0; y < SIDE_SIZE; y++)
		{
			piece = bGet(board, x, y);
			mark += materialValueOf(piece & PIECE_MASK) * colorSignOf(piece, color);
		}
	}
	return mark;
}

/*
 * TODO: evaluating the center control
 * Returns the evaluation of the center control for the parameter 'color'
 */
static Mark evalCenterControl(Board board, Color color)
{
	(void)board;
	(void)color;
	return 0;
}

/*
 * The evaluation function of the engine
 *
 * Returns the evaluation of the board for the parameter 'color'
 */
Mark eval(Board board, Color color)
{
	Mark finalMark;
	Mark materialMark;
	Mark centerControlMark;

	materialMark = evalMaterial(board, color);
	centerControlMark = evalCenterControl(board, color);
	finalMark = MATERIAL_COEF * materialMark + centerControlMark * CENTER_CONTROL_COEF;

	return finalMark;
}
