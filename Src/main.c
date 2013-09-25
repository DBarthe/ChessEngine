#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess.h"

extern void printBoard(Board board);
extern void clearBoard(Board board);
extern void initBoard(Board board);

static void gameSimultating(Board board)
{
	int ret;
	int stop = 0;
	Color color;

	  initBoard(board);
	  printBoard(board);

	  color = white;
	  while (!stop)
	  {
		  ret = ia_search(board, color, 5);
		  switch (ret)
		  {
		  case 0: break;
		  case 1: stop = 1; printf("%d win\n", color^COLOR_ON); break;
		  case 2: stop = 1; printf("null\n"); break;
		  case 3: stop = 1; printf("strange"); break;
		  }
		  printf("color = %d:\n", color);
		  printBoard(board);
		  color ^= COLOR_ON;
		  //sleep(1);
	  }
}

int main(void)
{
  Board board;

  gameSimultating(board);
  /*
  initBoard(board);
  printBoard(board);
  //ia_negamax(board, black, 1, MARK_MIN, MARK_MAX);
  ia_search(board, white, 9);
  printf("------------------------------\nchoice = \n");
  printBoard(board);
  */
  return 0;
}
