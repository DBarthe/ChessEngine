/*
 * ChessEngine
 *
 * file movements.h in Includes/
 *
 * Headers of movements.c in Src/
 */

#ifndef MOVEMENTS_H_
# define MOVEMENTS_H_

# include "chess.h"
# include "movesList.h"
# include "ia.h"



int ia_moveKing(Board board, Color color, int depth, int x, int y, Mark *alpha, Mark *beta, MovesList *move);
int ia_moveQueen(Board board, Color color, int depth, int x, int y, Mark *alpha, Mark *beta, MovesList *move);
int ia_moveRock(Board board, Color color, int depth, int x, int y, Mark *alpha, Mark *beta, MovesList *move);
int ia_moveBishop(Board board, Color color, int depth, int x, int y, Mark *alpha, Mark *beta, MovesList *move);
int ia_moveKnight(Board board, Color color, int depth, int x, int y, Mark *alpha, Mark *beta, MovesList *move);
int ia_movePawn(Board board, Color color, int depth, int x, int y, Mark *alpha, Mark *beta, MovesList *move);

#endif /* MOVEMENTS_H_ */
