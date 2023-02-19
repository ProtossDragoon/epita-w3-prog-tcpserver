CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -g -fsanitize=address -std=c99
LDFLAGS = -fsanitize=address -static-libsan
LDLIBS =

SRC = main.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: main.o

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} main
