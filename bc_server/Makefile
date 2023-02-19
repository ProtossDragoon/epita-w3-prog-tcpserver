CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
LDFLAGS =
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
