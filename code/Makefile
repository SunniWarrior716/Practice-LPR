CC = gcc

# Get Criterion include + libs from pkg-config
CRIT_CFLAGS := $(shell pkg-config --cflags criterion)
CRIT_LIBS   := $(shell pkg-config --libs criterion)

CFLAGS = -Wall -Wextra -pedantic -g -O0 $(CRIT_CFLAGS)
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
PROFILE_FLAGS  = -pg

TEST_LIBS = $(CRIT_LIBS)

SRC      = recipes.c main.c
TEST_SRC = tests.c recipes.c

OBJ       = $(SRC:.c=.o)
TEST_OBJ  = $(TEST_SRC:.c=.o)

.PHONY: all clean tests tests_coverage coverage main_profile profile

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

tests: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o tests $(TEST_OBJ) $(TEST_LIBS)

# Build tests with coverage flags for gcov
tests_coverage: CFLAGS += $(COVERAGE_FLAGS)
tests_coverage: clean tests

# Run tests and then gcov (no redirect here; we'll capture manually)
coverage: tests_coverage
	./tests
	gcov -abcfu recipes.c

# Build main with profiling (gprof)
main_profile: CFLAGS += $(PROFILE_FLAGS)
main_profile: clean main

profile: main_profile
	./main
	gprof main gmon.out -b

clean:
	rm -f *.o main tests *.gcno *.gcda *.gcov gmon.out
	rm -f testResults.* gcovResults.* gprofResults.* valgrindResults.* callgrind.log gdbSession.*
