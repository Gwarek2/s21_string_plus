CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11 -fsanitize=address -Wformat=0 -g

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
	$(CC) $(FLAGS) -c lib/*.c --coverage
	$(CC) $(FLAGS) tests/s21_string_tests.c *.o --coverage $(CHECK_DEPENDENCIES) -o s21_string_report
	./s21_string_report
	gcov tests/s21_string_tests.c
	lcov -c --directory . --output-file s21_string_coverage.info
	genhtml s21_string_coverage.info --output-directory s21_string_coverage

s21_string.a:
	$(CC) $(FLAGS) -c lib/*.c 
	ar -rc s21_string.a *.o
	ranlib s21_string.a

clean:
	-rm -rf *.o *.out *.a *.html *.gcno *.gcda *.gcov *.info s21_string_test s21_string_report s21_string_coverage
