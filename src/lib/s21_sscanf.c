#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

#include "s21_string.h"
#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
    va_list args;
    struct scan_state state;

    va_start(args, format);
    _initialize_state(&state);

    while (*format && !state.failure) {
        if (*format == '%') {
            format++;
            _read_format(&format, &state);
            // printf("----new_format: bytes - %i, correct_writes - %i, numargs - %i, oargs - %i, fail - %i\n",
            //         state.bytes_scanned, state.correct_writes, state.num_args_flag, state.ordered_args_flag, state.failure),
            // printf("supress - %i, arg_num - %i, width - %i, use_alloc - %i, length - %i, specifier - %c\n",
            //          state.format.supress, state.format.arg_num, state.format.width, state.format.use_alloc, state.format.length,
            //          state.format.specifier);
            if (!state.failure && state.format.specifier != '%') {
                _parse_arg(args, &str, &state);
            } else if (state.format.specifier == '%') {
                _ignore_space_chars(&str);
                if (*str != '%')
                    state.failure = true;
                str++;
            }
            _reset_format(&state);
        } else if (!is_space(*format)) {
            _ignore_space_chars(&str);
            if (*str != *format)
                state.failure = 1;
            str++;
            format++;
        } else {
            format++;
        }
    }
    va_end(args);
    return state.correct_writes;
}

void _initialize_state(struct scan_state *st) {
    st->bytes_scanned = 0;
    st->correct_writes = 0;
    st->num_args_flag = 0;
    st->ordered_args_flag = 0;
    st->failure = 0;
    _reset_format(st);
}

void _reset_format(struct scan_state *st) {
    st->format.supress = 0;
    st->format.arg_num = 0;
    st->format.width = -1;
    st->format.use_alloc = 0;
    st->format.length = 0;
    st->format.specifier = '\0';
    st->format.scanset[0] = '\0';
}

void _ignore_space_chars(const char **str) {
    while (is_space(**str)) (*str)++;
}

void _ignore_non_digits(const char **str) {
    while (!is_digit(**str) && !_is_neg_num_starts(*str)) (*str)++;
}

bool is_space(char ch) {
    return ch <= 32;
}

bool is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool _is_neg_num_starts(const char *str) {
    return *str == '-' && is_digit(str[1]);
}

void _read_format(const char **format, struct scan_state *st) {
    _read_supressor(format, st);
    _read_width_and_argnum(format, st);
    _read_alloc_flag(format, st);
    _read_len(format, st);
    _read_specifier(format, st);
}

void _read_supressor(const char **format, struct scan_state *st) {
    if (**format == SUPRESSOR) {
        st->format.supress = true;
        (*format)++;
    }
}


void _read_width_and_argnum(const char **format, struct scan_state *st) {
    char buffer[50];
    _read_number(buffer, format, -1);
    int num = s21_atoi(buffer);
    if (**format == NUM_ARG) {
        st->format.arg_num = num;
        st->num_args_flag = true;
        st->failure = st->ordered_args_flag || num == 0;
        if (!st->failure) {
            (*format)++;
            s21_memset(buffer, '\0', 50);
            _read_number(buffer, format, -1);
            num = s21_atoi(buffer);
        }
    } else {
        st->ordered_args_flag = !st->format.supress && st->format.specifier == '%';
        st->failure = st->num_args_flag && !st->format.supress;
    }
    if (num) st->format.width = num;
}

void _read_number(char *buffer, const char **src, int len) {
    const char *cursor = *src;
    int i = 0;

    if (**src == '-') {
        buffer[i++] = '-';
        cursor++;
        len--;
    }

    while (is_digit(*cursor) && len) {
        buffer[i++] = *cursor++;
        len--;
    }
    buffer[i] = '\0';
    *src = cursor;
}

void _read_alloc_flag(const char **format, struct scan_state *st) {
    if (**format == USE_ALLOC) {
        st->format.use_alloc = true;
        (*format)++;
    }
}

void _read_len(const char **format, struct scan_state *st) {
    if (**format == 'l' && *(*format + 1) == 'l') {
        st->format.length = LLONG;
        *format += 2;
    } else if (**format == 'L') {
        st->format.length = LLONG;
        *format += 1;
    } else if (**format == 'l') {
        st->format.length = LONG;
        *format += 1;
    } else if (**format == 'h') {
        st->format.length = SHORT;
        *format += 1;
    } else {
        st->format.length = COMMON;
    }
}

void _read_specifier(const char **format, struct scan_state *st) {
    if (s21_strchr(SPECIFIERS, **format)) {
        st->format.specifier = **format;
        (*format)++;
    } else if (**format == SCANSET_START) {
        st->format.specifier = 's';
        (*format)++;
    } else {
        st->failure = true;
    }
}

void _read_scanset(const char **format, struct scan_state *st) {
    int i = 0;
    while (**format && **format != SCANSET_END) {
        (*format)++;
        st->format.scanset[i] = **format;
    }
    st->failure = !**format;
    st->format.scanset[i] = '\0';
}

void _parse_arg(va_list args, const char **str, struct scan_state *st) {
    void *arg_ptr;
    if (st->num_args_flag)
        arg_ptr = _parse_by_index(args, st->format.arg_num);
    else
        arg_ptr = _parse_by_order(args);

    if (st->format.specifier == 'i' || st->format.specifier == 'd') {
        _parse_int(str, arg_ptr, st);
    } else if (st->format.specifier == 'u') {

    } else if (st->format.specifier == 'o') {

    } else if (st->format.specifier == 'x' || st->format.specifier == 'X') {

    } else if (st->format.specifier == 'p') {

    } else if (st->format.specifier == 'f') {

    } else if (st->format.specifier == 'e' || st->format.specifier == 'E') {

    } else if (st->format.specifier == 'g' || st->format.specifier == 'G') {

    } else if (st->format.specifier == 'c') {

    } else if (st->format.specifier == 'n') {

    } else if (st->format.specifier == 'c') {

    } else if (st->format.specifier == 's') {

    } else if (st->format.specifier == 'n') {

    }
}

void *_parse_by_order(va_list args) {
    return va_arg(args, void*);
}

void *_parse_by_index(va_list args, int index) {
    va_list cursor;
    void *arg_ptr;
    va_copy(cursor, args);
    while (index--)
        arg_ptr = va_arg(args, void*);
    va_end(cursor);
    return arg_ptr;
}

void _parse_int(const char **str, void *ptr, struct scan_state *st) {
    char buffer[512];
    _ignore_non_digits(str);
    _read_number(buffer, str, st->format.width);
    printf("%s %s\n", buffer, *str);

    long long parsed_num = s21_atoi(buffer);
    if (st->format.length == LLONG) {
        long long *llptr = ptr;
        *llptr = parsed_num;
    } else if (st->format.length == LONG) {
        long *lptr = ptr;
        *lptr = parsed_num;
    } else if (st->format.length == SHORT) {
        short *sptr = ptr;
        *sptr = parsed_num;
    } else {
        int *cptr = ptr;
        *cptr = parsed_num;
    }
}

// void _parse_uint(const char **str, void *ptr, struct scan_state *st) {
//     char buffer[512];
//     _ignore_non_digits
// }
