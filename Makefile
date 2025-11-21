CC = gcc


CFLAGS = -Wall -Wextra -pedantic -g -O0

COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
PROFILE_FLAGS  = -pg

SRC      = recipes.c main.c
TEST_SRC = tests.c recipes.c

OBJ      = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

.PHONY: all clean tests tests_coverage coverage main_profile profile


all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

tests: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o tests $(TEST_OBJ)

tests_coverage: CFLAGS += $(COVERAGE_FLAGS)
tests_coverage: clean tests

coverage: tests_coverage
	./tests > gcovTestRun.out 2>&1
	gcov -abcfu recipes.c > gcovResults.0 2>&1


main_profile: CFLAGS += $(PROFILE_FLAGS)
main_profile: clean main

profile: main_profile
	./main > profileRun.out 2>&1
	gprof main gmon.out -b > gprofResults.0 2>&1



clean:
	rm -f *.o main tests *.gcno *.gcda *.gcov gmon.out
	rm -f gcovResults.* gprofResults.* gcovTestRun.out profileRun.out testResults.*



