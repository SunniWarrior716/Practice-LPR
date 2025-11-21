CC = gcc

# Criterion include + lib paths (from lex22 on Linux)
CPPFLAGS = -I/util/criterion/include
CFLAGS   = -Wall -Wextra -pedantic -std=c11 -g -O0
LDFLAGS  = -L/util/criterion/lib/x86_64-linux-gnu
TEST_LIBS = -lcriterion

SRC      = recipes.c main.c
TEST_SRC = tests.c recipes.c

OBJ      = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

.PHONY: all clean tests

all: main

main: $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o main $(OBJ)

tests: $(TEST_OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o tests $(TEST_OBJ) $(TEST_LIBS)

clean:
	rm -f *.o main tests *.gcno *.gcda *.gcov gmon.out
	rm -f testResults.* gcovResults.* gprofResults.* valgrindResults.* callgrind.log