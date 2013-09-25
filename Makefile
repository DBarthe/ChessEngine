CC ?= gcc

INCPATH = ./Includes
SRCPATH = ./Src

CFLAGS = -Wall -Wextra -I $(INCPATH)
OFLAGS = -O3
DBGFLAGS = -g -DDEBUG
NDBGFLAGS = -DNDEBUG
LDFLAGS =

TARGET = chess-engine
SRC = $(wildcard $(SRCPATH)/*.c)
OBJ = $(SRC:.c=.o)

RM = rm -vf

all: CFLAGS += $(OFLAGS) $(NDBGFLAGS)
all: compile

debug: CFLAGS += $(DBGFLAGS)
debug: compile

compile: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

re-debug: fclean debug

.PHONY: all re clean debug re-debug fclean