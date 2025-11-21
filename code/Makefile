<<<<<<< HEAD
CC       = gcc
=======
<<<<<<< Updated upstream
CC = gcc
>>>>>>> ce6fab7 (Resolve Makefile merge conflict and configure Criterion for tests)

# Criterion (Linux on cerf)
CPPFLAGS = -I/util/criterion/include
CFLAGS   = -Wall -Wextra -pedantic -std=c11 -g -O0
LDFLAGS  = -L/util/criterion/lib/x86_64-linux-gnu
<<<<<<< HEAD
LDLIBS   = -lcriterion
=======
TEST_LIBS = -lcriterion
=======
# ============================
# Makefile for LPR Recipe Book
# ============================

CC = gcc

# ----------------------------
# Criterion paths (IMPORTANT)
# ----------------------------
# Set these two based on a working lab (lex/exp).
# Example (FAKE) values:
#   CRIT_INC    = -I/opt/criterion/include
#   CRIT_LIBDIR = -L/opt/criterion/lib
#
# Go to a working lab (e.g. lex22-SunniWarrior716/code),
# open its Makefile, and copy the real -I and -L flags.
CRIT_INC    = -I/util/criterion/include
CRIT_LIBDIR = -L/util/criterion/lib/x86_64-linux-gnu

# ----------------------------
# Flags
# ----------------------------

CFLAGS         = -Wall -Wextra -pedantic -g -O0
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
PROFILE_FLAGS  = -pg

# Criterion compile + link flags
TEST_CFLAGS = $(CFLAGS) $(CRIT_INC)
TEST_LIBS   = $(CRIT_LIBDIR) -lcriterion

# ----------------------------
# Sources / Objects
# ----------------------------
>>>>>>> Stashed changes
>>>>>>> ce6fab7 (Resolve Makefile merge conflict and configure Criterion for tests)

SRC      = recipes.c main.c
TEST_SRC = tests.c recipes.c

OBJ      = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

<<<<<<< Updated upstream
.PHONY: all clean tests
=======
# ----------------------------
# Phony targets
# ----------------------------

.PHONY: all clean tests tests_coverage coverage main_profile profile

# ----------------------------
# Main targets
# ----------------------------
>>>>>>> Stashed changes

all: main

main: $(OBJ)
<<<<<<< HEAD
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $(OBJ)
=======
<<<<<<< Updated upstream
	$(CC) $(CPPFLAGS) $(CFLAGS) -o main $(OBJ)
>>>>>>> ce6fab7 (Resolve Makefile merge conflict and configure Criterion for tests)

tests: $(TEST_OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $(TEST_OBJ) $(LDLIBS)

clean:
	rm -f *.o main tests *.gcno *.gcda *.gcov gmon.out
	rm -f testResults.* gcovResults.* gprofResults.* valgrindResults.* callgrind.log
<<<<<<< HEAD


=======
=======
	$(CC) $(CFLAGS) -o main $(OBJ)

tests: $(TEST_OBJ)
	$(CC) $(TEST_CFLAGS) -o tests $(TEST_OBJ) $(TEST_LIBS)

# ----------------------------
# Coverage (gcov)
# ----------------------------

tests_coverage: CFLAGS += $(COVERAGE_FLAGS)
tests_coverage: clean tests

coverage: tests_coverage
	./tests > testResults.coverage.0 2>&1
	gcov -abcfu recipes.c > gcovResults.0

# ----------------------------
# Profiling (gprof)
# ----------------------------

main_profile: CFLAGS += $(PROFILE_FLAGS)
main_profile: clean main

profile: main_profile
	./main > runProfile.0 2>&1
	gprof main gmon.out -b > gprofResults.0

# ----------------------------
# Cleanup
# ----------------------------

clean:
	rm -f *.o main tests *.gcno *.gcda *.gcov gmon.out
	rm -f testResults.* gcovResults.* gprofResults.* valgrindResults.* callgrind.log
>>>>>>> Stashed changes
>>>>>>> ce6fab7 (Resolve Makefile merge conflict and configure Criterion for tests)
