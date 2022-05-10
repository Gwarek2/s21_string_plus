CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11

UNAME = $(shell uname -s)
ifeq ($(UNAME),Darwin)
	CHECK_DEPENDENCIES=-lcheck -lm -lpthread
endif
ifeq ($(UNAME),Linux)
	CHECK_DEPENDENCIES=-lcheck -lm -lpthread -lrt -lsubunit
endif

all: test gcov_report

test: s21_string.a
	$(CC) $(FLAGS) tests/s21_string_tests.c $(CHECK_DEPENDENCIES) s21_string.a -o s21_string_test

build_test_file:
	rm tests/s21_string_tests.c && checkmk clean_mode=1 tests/*.check > tests/s21_string_tests.c

gcov_report:
	$(CC) $(FLAGS) -c --coverage s21_string.c s21_string_helpers.c
	$(CC) $(FLAGS) s21_string_helpers.o s21_string.o tests/s21_string_tests.c --coverage $(CHECK_DEPENDENCIES) -o s21_string_report
	./s21_string_report
	gcov -a tests/s21_string_tests.c
	lcov -c -f -d . --output-file s21_string_coverage.info
	genhtml s21_string_coverage.info --output-directory s21_string_coverage

s21_string.a:
	$(CC) $(FLAGS) -c s21_string_helpers.c s21_string.c
	ar -rc s21_string.a s21_string_helpers.o s21_string.o
	ranlib s21_string.a

clean:
	-rm -rf *.o *.out *.a *.html *.gcno *.gcda *.info s21_string_test s21_string_report s21_string_coverage
