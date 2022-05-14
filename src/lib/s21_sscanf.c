#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>

#include "s21_string.h"
#include "s21_sscanf.h"

int sscanf(const char *str, const char *format, ...) {
    struct scan_state state;
    _initialize_state(&state);
    while (*format && !state.failure) {
        if (is_space(*format)) {
            format++;
            continue;
        }
        if (*format == '%') {
            format++;
            // todo
        } else {
            while (is_space(*str)) str++;
            if (*str != *format)
                state.failure = 1;
            else
                str++;
        }
    }
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
    st->format.width = 0;
    st->format.use_alloc = 0;
    st->format.length = 0;
    st->format.specifier = '\0';
    st->format.scanset[0] = '\0';
}



bool is_space(char ch) {
    return ch <= 32;
}


void _read_format(char **format, struct scan_state *st) {
    _read_supressor(format, st);
    _read_width_and_arg_num(format, st);
    _read_alloc_flag(format, st);
    _read_len(format, st);
    _read_specifier(format, struct, st);
}

void _read_supressor(char **format, struct scan_state *st) {
    if (**format == SUPRESSOR) {
        st->format.supressor = true;
        (*format)++;
    }
}


void _read_width_and_arg_num(char **format, struct state *st) {
    char buffer[50];
    _read_num(buffer, format);
    int num = s21_atoi(buffer);
    if (*cursor == NUM_ARG) {
        st->format.arg_num = num;
        st->num_args_flag = true;
        st->failure = !st->ordered_args_flag && num != 0;
        if (!st->failure) {
            s21_memset(buffer, '\0', 50);
            _read_num(buffer, format);
            num = s21_atoi(buffer);
        }
    }
    st->format.width = num;
}

void _read_num(char *buffer, char **src) {
    char *cursor = *src;
    int i = 0;
    while (*cursor >= 0 && *cursor <= '9'))
        buffer[i++] = *cursor++;
    buffer[i] = '0';
    *src = cursor;
}

void _read_alloc_flag(char **format, struct scan_state *st) {
    if (**format == USE_ALLOC) {
        st->format.use_alloc = true;
        (*format)++;
    }
}

void _read_len(char **format, struct state *st) {
    if (**format == LONG && *(*format + 1) == LONG) {
        st->format.length = 4;
        *format += 2;
    } else if (**format == LONG_DOUBLE) {
        st->format.length = 4;
        *format += 1;
    } else if (**format == LONG) {
        st->format.length = 3;
        *format += 1;
    } else if (**format == SHORT) {
        st->format.length = 1;
        *format += 1;
    } else {
        st->format.length = 2;
    }
}

void _read_specifier(char **format, struct scan_state *st) {
    if (s21_strchr(SPECIFIERS, **format)) {
        st->format.specifier = **format;
        (*format)++;
    } else {
        st->failure = true;
    }
}
