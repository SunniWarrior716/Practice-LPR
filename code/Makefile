CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -O0
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
PROFILE_FLAGS = -pg
TEST_LIBS = -lcriterion

SRC = recipes.c main.c
TEST_SRC = tests.c recipes.c

OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

.PHONY: all clean tests tests_coverage coverage main_profile profile

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

tests: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o tests $(TEST_OBJ) $(TEST_LIBS)

# Build tests with coverage flags for gcov
tests_coverage: CFLAGS += $(COVERAGE_FLAGS)
tests_coverage: clean tests

# Build main with profiling (gprof)
main_profile: CFLAGS += $(PROFILE_FLAGS)
main_profile: clean main

# Convenience target: run tests and gcov in one go
coverage: tests_coverage
	./tests
	gcov -abcfu recipes.c > gcovResults.0

# Convenience target: run main and gprof in one go
profile: main_profile
	./main
	gprof main gmon.out -b > gprofResults.0

clean:
	rm -f *.o main tests *.gcno *.gcda *.gcov gmon.out
	rm -f testResults.* gcovResults.* gprofResults.* valgrindResults.* callgrind.log gdbSession.*
