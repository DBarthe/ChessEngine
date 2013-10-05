/*
 * ChessEngine
 *
 * file macros.h
 *
 * Contains project macros.
 */



#ifdef DEBUG
# define IFDEBUG(instruction) instruction
# define IFNDEBUG(instruction)
# include <stdio.h>
# define IFDEBUG_PRINT(msg) printf("%s\n", msg)
#else
# define IFDEBUG(instruction)
# define IFNDEBUG(instruction) instruction
# define IFDEBUG_PRINT(msg)


#endif /* DEBUG */

