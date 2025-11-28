CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -O0
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
PROFILE_FLAGS = -pg
TEST_LIBS = -lcriterion

SRC = recipes.c main.c
TEST_SRC = tests.c recipes.c

OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

.PHONY: all clean tests coverage main_coverage main_profile profile

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

tests: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o tests $(TEST_OBJ) $(TEST_LIBS)

# ==== COVERAGE USING main (no Criterion needed here) ====

main_coverage: CFLAGS += $(COVERAGE_FLAGS)
main_coverage: clean main

coverage: main_coverage
	./main > testResults.3 2>&1
	gcov -abcfu recipes.c > gcovResults.0

# ==== GPROF (performance) ====

main_profile: CFLAGS += $(PROFILE_FLAGS)
main_profile: clean main

profile: main_profile
	./main
	gprof main gmon.out -b > gprofResults.0

# ==== CLEAN ====

clean:
	rm -f *.o main tests *.gcno *.gcda *.gcov gmon.out
	rm -f testResults.* gcovResults.* gprofResults.* valgrindResults.* callgrind.log gdbSession.*
