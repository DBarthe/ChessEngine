/*
 * ChessEngine
 *
 * moveList.c in Src/
 *
 * This list contains best moves that the player to move can do.*
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "movesList.h"
#include "rand.h"

/*
 * Allocates a new MoveLink and initializes it with parameters values.
 * Returns a pointer to the new link.
 */
MoveLink *newMoveLink(Move move, MoveLink *next)
{
	MoveLink *link;

	link = malloc(sizeof(MoveLink));
	if (!link)
	{
		fprintf(stderr, "Function malloc() returns null\n");
		exit(EXIT_FAILURE);
	}
	link->move = move;
	link->next = next;
	return link;
}

/*
 * Initializes a MovesList and returns it.
 */
MovesList newMovesList(void)
{
	MovesList list;

	list.head = NULL;
	list.length = 0;
	return list;
}

/*
 * Creates a new link with the parameter 'move',
 * and adds it in the head of list.
 */
void addMoveLink(MovesList *list, Move move)
{
	MoveLink *link;

	link = newMoveLink(move, list->head);
	list->head = link;
	list->length++;
}

/*
 * Resets the list, frees all links.
 */
void setMovesListEmpty(MovesList *list)
{
	MoveLink *curLink;
	MoveLink *toDeleteLink = NULL;

	for (curLink = list->head; curLink; curLink = curLink->next)
	{
		free(toDeleteLink);
		toDeleteLink = curLink;
	}
	free(toDeleteLink);
	list->head = NULL;
	list->length = 0;
}

/*
 * Choices and returns a random move in the list
 * list must contain at least one move
 */
Move getRandomMove(MovesList *list)
{
	MoveLink *curLink;
	int randNumber, i;

	assert(list->length > 0);
	randNumber = bornedRand(0, list->length - 1);
	i = 0;
	curLink = list->head;
	while (i < randNumber)
	{
		curLink = curLink->next;
		i++;
	}
	return curLink->move;
}
