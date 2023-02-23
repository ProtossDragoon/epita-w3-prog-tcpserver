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
OBJ = echo_test.o echo.o single_server.o loop_server.o fork_server.o
DEP = ${OBJ:.o=.d}
EXC = echo_test single_server loop_server fork_server

# Instructions
all: echo_test single_server loop_server fork_server

echo_test: echo_test.o echo.o 

single_server: single_server.o echo.o

loop_server: loop_server.o echo.o

fork_server: fork_server.o echo.o

# Not related to files
.PHONY: clean
clean:
	${RM} ${OBJ} ${DEP} ${EXC}
