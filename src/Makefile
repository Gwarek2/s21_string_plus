CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11 #-g -fsanitize=address 
CHECKMK=checkmk clean_mode=1
OUT_DIR=obj
COV_DIR=coverage_info
ALL_C=`find . -name "*.c"`
CHECK_FLAGS=`pkg-config --cflags --libs check`

.PHONY: all
all: test gcov_report

test: s21_string.a
	$(CC) $(FLAGS) tests/s21_string_tests.c $(CHECK_FLAGS) s21_string.a -o s21_string_test

remove_test_file:
	@-rm tests/s21_string_tests.c

build_sscanf_test: remove_test_file
	$(CHECKMK) tests/headers.check tests/s21_sscanf.check > tests/s21_string_tests.c

build_test_file: remove_test_file
	$(CHECKMK) tests/*.check > tests/s21_string_tests.c

gcov_report: create_out_dirs
	$(CC) $(FLAGS) -c lib/*.c --coverage
	@-mv *.o $(OUT_DIR)
	$(CC) $(FLAGS) tests/s21_string_tests.c $(OUT_DIR)/*.o --coverage $(CHECK_FLAGS) -o s21_string_report
	@-./s21_string_report
	@-mv *.gcda *.gcno $(COV_DIR)
	@gcov -f lib/s21_string_tests.c -o=$(COV_DIR)
	@lcov -c --directory $(COV_DIR) --output-file $(COV_DIR)/s21_string_coverage.info
	@genhtml $(COV_DIR)/s21_string_coverage.info --output-directory $(COV_DIR)

.PHONY: s21_string.a
s21_string.a: create_out_dirs
	$(CC) $(FLAGS) -c lib/*.c
	@-mv *.o $(OUT_DIR)
	ar -rc s21_string.a $(OUT_DIR)/*.o
	ranlib s21_string.a

static_analysis:
	@-cp ../materials/linters/* .
	python3 cpplint.py --extensions=c $(ALL_C)
	@-rm cpplint.py CPPLINT.cfg
	cppcheck $(ALL_C)

create_out_dirs:
	@-mkdir $(OUT_DIR)
	@-mkdir $(COV_DIR)

clean:
	@-rm -rf *.o obj *.out *.a *.dSYM *.gcov s21_string_test s21_string_report coverage_info
