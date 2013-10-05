/*
 * ChessEngine
 *
 * file tableMovements.c in Src/
 *
 * Contains a table of function pointers 'MovementFunction' (piece => movement function)
 */

#include <stdlib.h>
#include "ia.h"
#include "piecesMovements.h"

MovementFunction tableMovements[7] = {
		NULL,
		&addKingMovesToList,
		&addQueenMovesToList,
		&addRockMovesToList,
		&addBishopMovesToList,
		&addKnightMovesToList,
		&addPawnMovesToList,
};
