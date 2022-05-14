CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11 -fsanitize=address -g
OUT_DIR=obj
COV_DIR=coverage_info

UNAME = $(shell uname -s)
ifeq ($(UNAME),Darwin)
	CHECK_DEPENDENCIES=-lcheck -lm -lpthread
endif
ifeq ($(UNAME),Linux)
	CHECK_DEPENDENCIES=-lcheck -lm -lpthread -lrt -lsubunit
endif

.PHONY: all
all: test gcov_report

test: s21_string.a
	$(CC) $(FLAGS) tests/s21_string_tests.c $(CHECK_DEPENDENCIES) s21_string.a -o s21_string_test

build_test_file:
	@rm tests/s21_string_tests.c && checkmk clean_mode=1 tests/*.check > tests/s21_string_tests.c

gcov_report: create_out_dirs
	$(CC) $(FLAGS) -c lib/*.c --coverage
	-@mv *.o $(OUT_DIR)
	$(CC) $(FLAGS) tests/s21_string_tests.c $(OUT_DIR)/*.o --coverage $(CHECK_DEPENDENCIES) -o s21_string_report
	-@./s21_string_report
	-@mv *.gcda *.gcno $(COV_DIR)
	@gcov -f lib/s21_string_tests.c -o=$(COV_DIR)
	@lcov -c --directory $(COV_DIR) --output-file $(COV_DIR)/s21_string_coverage.info
	@genhtml $(COV_DIR)/s21_string_coverage.info --output-directory $(COV_DIR)

.PHONY: s21_string.a
s21_string.a: create_out_dirs
	$(CC) $(FLAGS) -c lib/*.c
	-@mv *.o $(OUT_DIR)
	ar -rc s21_string.a $(OUT_DIR)/*.o
	ranlib s21_string.a


create_out_dirs:
	-@mkdir $(OUT_DIR)
	-@mkdir $(COV_DIR)

clean:
	-rm -rf *.o obj *.out *.a *.dSYM *.gcov s21_string_test s21_string_report coverage_info
