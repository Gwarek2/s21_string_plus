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
	$(CC) $(FLAGS) s21_string_test.c $(CHECK_DEPENDENCIES) -L. -ls21_string -o s21_string_test

gcov_report:

s21_string.a:
	$(CC) $(FLAGS) -c s21_string.c
	ar -rc libs21_string.a s21_string.o
	ranlib libs21_string.a

clean:
	-rm *.o *.out *.a