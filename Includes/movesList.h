/*
 * ChessEngine
 *
 * file movesList.h in Includes/
 *
 * Header for movesList.c in Src/
 */

#ifndef MOVES_LIST_H_
# define MOVES_LIST_H_

# include "chess.h"

typedef struct MoveLink MoveLink;
typedef struct MovesList MovesList;

struct MoveLink
{
	Move move;
	MoveLink *next;
};

struct MovesList
{
	MoveLink *head;
	int length;
};

MoveLink *newMoveLink(Move move, MoveLink *next);
MovesList newMovesList(void);
void addMoveLink(MovesList *list, Move move);
void setMovesListEmpty(MovesList *list);
Move getRandomMove(MovesList *list);

#endif /* MOVES_LIST_H_ */
