CC       = gcc

# Criterion (Linux on cerf)
CPPFLAGS = -I/util/criterion/include
CFLAGS   = -Wall -Wextra -pedantic -std=c11 -g -O0
LDFLAGS  = -L/util/criterion/lib/x86_64-linux-gnu
LDLIBS   = -lcriterion

SRC      = recipes.c main.c
TEST_SRC = tests.c recipes.c

OBJ      = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

.PHONY: all clean tests

all: main

main: $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $(OBJ)

tests: $(TEST_OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $(TEST_OBJ) $(LDLIBS)

clean:
	rm -f *.o main tests *.gcno *.gcda *.gcov gmon.out
	rm -f testResults.* gcovResults.* gprofResults.* valgrindResults.* callgrind.log


