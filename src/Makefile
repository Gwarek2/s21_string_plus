CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11 -fsanitize=address -Wformat=0 -g
OUT_DIR=obj

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
	-@mv *.o $(OUT_DIR)
	$(CC) $(FLAGS) tests/s21_string_tests.c $(OUT_DIR)/*.o --coverage $(CHECK_DEPENDENCIES) -o s21_string_report
	-./s21_string_report
	@mv *.gcda *.gcno tests/
	gcov tests/s21_string_tests.c --object-directory tests
	lcov -c --directory tests --output-file s21_string_coverage.info
	genhtml s21_string_coverage.info --output-directory s21_string_coverage

s21_string.a:
	$(CC) $(FLAGS) -c lib/*.c
	@mv *.o $(OUT_DIR)
	ar -rc s21_string.a $(OUT_DIR)/*.o
	ranlib s21_string.a

clean:
	-rm -rf *.o obj/*.o *.out *.a tests/*.gcno tests/*.gcda tests/*.gcov *.info s21_string_test s21_string_report s21_string_coverage
