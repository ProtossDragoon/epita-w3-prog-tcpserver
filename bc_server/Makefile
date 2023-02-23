# Compiler
CC = gcc

# Compiler flags
# -std=c99: C standard version
# -g: make debuggable
# -fsanitize=address: help to find memory leak
# -Wall: show all warnings
# -Wextra: show extra warnings
# -Dxxx: work as #define xxx in C code
CFLAGS = -std=c99 -g -fsanitize=address -Wall -Wextra -D_GNU_SOURCE

# Linker flags
LDFLAGS = -fsanitize=address

# File variables
OBJ = main.o 
DEP = ${OBJ:.o=.d} 
EXC = main 

# Instructions
all: main

main: main.o

.PHONY: clean
clean:
	${RM} ${OBJ} ${DEP} ${EXC}
