/*
 * ChessEngine
 *
 * file piecesMovements.h in Includes/
 *
 * header of piecesMovements.h in Src/
 */

#ifndef PIECES_MOVEMENTS_H_
# define PIECES_MOVEMENTS_H_

# include "chess.h"
# include "movesList.h"
# include "ia.h"

void applyMovement(Board board, Color color, Piece piece, Move move);

MovesList *makeMovesList(Board board, Color color, MovesList *movesList);

MovesList *addKingMovesToList(Board board, Color color, int srcX, int srcY, MovesList *movesList);
MovesList *addQueenMovesToList(Board board, Color color, int srcX, int srcY, MovesList *movesList);
MovesList *addRockMovesToList(Board board, Color color, int srcX, int srcY, MovesList *movesList);
MovesList *addBishopMovesToList(Board board, Color color, int srcX, int srcY, MovesList *movesList);
MovesList *addKnightMovesToList(Board board, Color color, int srcX, int srcY, MovesList *movesList);
MovesList *addPawnMovesToList(Board board, Color color, int srcX, int srcY, MovesList *movesList);

#endif /* PIECES_MOVEMENTS_H_ */
