/*
 * ChessEngine
 *
 * file tableMovements.c in Src/
 *
 * Contains a table of function pointers 'MovementFunction' (piece => movement function)
 */

#include <stdlib.h>
#include "movements.h"

MovementFunction tableMovements[7] = {
		NULL,
		&ia_moveKing,
		&ia_moveQueen,
		&ia_moveRock,
		&ia_moveBishop,
		&ia_moveKnight,
		&ia_movePawn
};
