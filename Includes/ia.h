/*
 * ChessEngine
 *
 * file ia.h in Includes/
 *
 */

#ifndef IA_H_
# define IA_H_

# include "chess.h"
# include "movesList.h"



# define RET_MOVE 1
# define RET_NOMOVE 0
# define RET_STOP 2

int ia_search(Board board, Color color, int depth);

/*
 * Evaluation
 */
typedef int Mark;

# define MARK_MAX 10000
# define MARK_MIN (-MARK_MAX)
# define MARK_PAT 0
# define MARK_MAT_WIN (MARK_MAX-10)
# define MARK_MAT_LOSE (-MARK_MAT_WIN)

# define KING_VALUE 0
# define QUEEN_VALUE 9
# define ROCK_VALUE 5
# define BISHOP_VALUE 3
# define KNIGHT_VALUE 3
# define PAWN_VALUE 1

Mark ia_eval(Board board, Color color);

/*
 * Negamax algorithm
 */
Mark ia_negamax(Board board, Color color, int depth, Mark alpha, Mark beta);
int ia_negamaxBack(Board board, Color color, int depth,
		   Mark *alpha, Mark *beta, MovesList *move,
		   int srcX, int srcY, int dstX, int dstY,
		   Piece myPiece);

typedef int (*MovementFunction)(Board, Color, int, int, int, Mark *, Mark *, MovesList *);

#endif /* IA_H_ */
