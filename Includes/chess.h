/*
 * ChessEngine
 *
 * file chess.h in Inludes/
 */

#ifndef CHESS_H_
# define CHESS_H_

# define PIECE_MASK 0x7
# define COLOR_MASK 0x8

enum Piece
  {
    noPiece = 0,
    king = 1,
    queen = 2,
    rock = 3,
    bishop = 4,
    knight = 5,
    pawn = 6
  };

typedef unsigned char Piece;

//int pieceValueTab[7] = {0, KING_VALUE, QUEEN_VALUE, ROCK_VALUE, BISHOP_VALUE, KNIGHT_VALUE, PAWN_VALUE };

typedef enum Color
  {
    white = 0 << 3,
    black = 1 << 3
  } Color;

# define COLOR_ON black //color with one bit '1'
# define COLOR_OFF white  // color without bit '1'


/*
 * Chess coordinates
 */

# define _A 0
# define _B 1
# define _C 2
# define _D 3
# define _E 4
# define _F 5
# define _G 6
# define _H 7

# define _1 0
# define _2 1
# define _3 2
# define _4 3
# define _5 4
# define _6 5
# define _7 6
# define _8 7


# define isPair(x) (((x)+1)%2)
# define isOdd(x) ((x)%2)

/*
 * if the board is 4*8
 *

# define FIRST_SQUARE_MASK 0xF0
# define SECOND_SQUARE_MASK 0xF
# define SQUARES_NUMBER 32
# define indexOf(x, y) ((y*4) + (x/2))
# define bGet(board, x, y) ((board[indexOf(x, y)] >> (4*isPair(x))) & SECOND_SQUARE_MASK)
# define bSet(board, x, y, value) (board[indexOf(x, y)] = ((board[indexOf(x, y)] & (SECOND_SQUARE_MASK << (4*isOdd(x)))) | value << 4*isPair(x)))
*/

/*
** the board is 8*8
*/
# define SQUARES_NUMBER 64
# define SIDE_SIZE 8
# define BOARD_SIZE 67
# define indexOf(x, y) ((y)*SIDE_SIZE + (x))
# define bGet(board, x, y) board[indexOf((x), (y))]
# define bSet(board, x, y, value) (board[indexOf((x), (y))] = (value))

/*
** datas for rocks and 'prise en passant'
*/
# define ENPASSANT_INDEX(color) (SQUARES_NUMBER + (color >> 3))
# define ROCK_INDEX (SQUARES_NUMBER+2)
# define LEFT_ROCK_BIT(color) (1 << (3 * ((color) >> 3)))
# define RIGHT_ROCK_BIT(color) (2 << (3 * ((color) >> 3)))
# define KING_BIT(color) (4 << (3 * ((color) >> 3)))

typedef unsigned char Case;
typedef Case Board[SQUARES_NUMBER+3];

# define ENPASSANT_DANGER 1
# define ENPASSANT_EAT 2

# define NO_ROCK 0
# define ROCK_LEFT 1
# define ROCK_RIGHT 2

typedef struct Move
{
  int srcX;
  int srcY;
  int dstX;
  int dstY;
  int promotion;
  unsigned char enpassant;
  unsigned char rock;
} Move;


#endif /* CHESS_H_ */
