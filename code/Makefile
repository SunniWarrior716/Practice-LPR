CC       = gcc

# Criterion paths for Linux on cerf (from your lex22 Makefile)
CPPFLAGS = -I/util/criterion/include
CFLAGS   = -Wall -Wextra -pedantic -std=c11 -g -O0
LDFLAGS  = -L/util/criterion/lib/x86_64-linux-gnu
TEST_LIBS = -lcriterion

SRC      = main.c recipes.c
TEST_SRC = tests.c recipes.c

OBJ      = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

.PHONY: all clean tests

all: main

main: $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $(OBJ)

tests: $(TEST_OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $(TEST_OBJ) $(TEST_LIBS)

# Generic rule for object files that depend on recipes.h
%.o: %.c recipes.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o main tests *.gcno *.gcda *.gcov gmon.out
	rm -f testResults.* gcovResults.* gprofResults.* valgrindResults.* callgrind.log
