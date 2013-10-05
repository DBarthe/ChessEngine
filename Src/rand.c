/*
 * ChessEngine
 *
 * file rand.c in Src/
 */

#include <stdlib.h>
#include <time.h>
#include <assert.h>

/*
 * Initializes seed with the current time
 */
void initSeed(void)
{
	srand(time(NULL));
}

/*
 * Gets a pseudo-random integer belonging to the interval [inf;sup]
 */
int bornedRand(int inf, int sup)
{
	assert(inf <= sup);
	return rand() % (sup+1 - inf) + inf;
}
