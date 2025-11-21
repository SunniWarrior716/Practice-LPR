CC=gcc
CFLAGS=-Wall -Wextra -pedantic -g -O0
LDFLAGS=
TEST_LIBS=-lcriterion

SRC=recipes.c main.c
TEST_SRC=tests.c recipes.c
OBJ=$(SRC:.c=.o)
TEST_OBJ=$(TEST_SRC:.c=.o)

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ) $(LDFLAGS)

tests: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o tests $(TEST_OBJ) $(TEST_LIBS)

clean:
	rm -f *.o main tests *.gcno *.gcda *.gcov gmon.out
