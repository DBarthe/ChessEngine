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


#define SEARCH_OK 0
#define SEARCH_MAT 1
#define SEARCH_PAT 2
#define SEARCH_ERROR 3


int search(Board board, Color color, int depth, Move *moveBuffer);

/*
 * Evaluation
 */
typedef int Mark;

# define MARK_MAX 10000
# define MARK_MIN (-MARK_MAX)
# define MARK_PAT 0
# define MARK_MAT_WIN (MARK_MAX-10)
# define MARK_MAT_LOSE (-MARK_MAT_WIN)
# define MARK_NULL 0

# define KING_VALUE 0
# define QUEEN_VALUE 9
# define ROCK_VALUE 5
# define BISHOP_VALUE 3
# define KNIGHT_VALUE 3
# define PAWN_VALUE 1

Mark eval(Board board, Color color);

/*
 * Negamax algorithm
 */
Mark negamax(Board board, Color color, int depth, Mark alpha, Mark beta);


typedef MovesList *(*MovementFunction)(Board, Color, int, int, MovesList *);

#endif /* IA_H_ */
