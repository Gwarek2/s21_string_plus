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

bool is_space(char ch) {
    return ch <= 32;
}


bool is_oct(char ch) {
    return ch >= '0' && ch <= '7';
}

bool is_dec(char ch) {
    return ch >= '0' && ch <= '9';
}

bool is_hex(char ch) {
    return (ch >= '0' && ch <= '9') ||
           (ch >= 'a' && ch <= 'f') ||
           (ch >= 'A' && ch <= 'F');
}

bool _is_neg_num_starts(const char *str, int width) {
    return *str == '-' && is_dec(str[1]) && (width > 1 || width == -1);
}

bool _is_float_starts_with_point(const char *str, int width) {
    return *str == '.' && is_dec(str[1]) && (width > 1 || width == -1);
}

bool _is_scientific_notation_starts(const char *str) {
    return (str[0] == 'e' || str[0] == 'E') &&
            (str[1] == '+' || str[1] == '-') &&
            is_dec(str[2]);
}

bool _is_oct_prefix(const char *str, int width) {
    return *str == '0' && is_oct(str[1])  && (width == -1 || width > 1);
}

bool _is_hex_prefix(const char *str, int width) {
    return *str == '0' && (str[1] == 'x' || str[1] == 'X') &&
           is_hex(str[2])  && (width == -1 || width > 2);
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
    _read_number(buffer, format, -1, &is_dec);
    int num = s21_atoi(buffer);
    if (**format == NUM_ARG) {
        st->format.arg_num = num;
        st->num_args_flag = true;
        st->failure = st->ordered_args_flag || num == 0;
        if (!st->failure) {
            (*format)++;
            s21_memset(buffer, '\0', 50);
            _read_number(buffer, format, -1, &is_dec);
            num = s21_atoi(buffer);
        }
    } else {
        st->ordered_args_flag = !st->format.supress && st->format.specifier == '%';
        st->failure = st->num_args_flag && !st->format.supress;
    }
    if (num) st->format.width = num;
}

void _read_number(char *buffer, const char **src, int len, bool (*num_check)(char)) {
    const char *cursor = *src;

    // Consider negative number
    if (*cursor == '-') {
        *buffer++ = '-';
        cursor++;
        len--;
    }

    while (num_check(*cursor) && len) {
        *buffer++ = *cursor++;
        len--;
    }
    *buffer = '\0';
    *src = cursor;
}

void _read_float(char *buffer, const char **src, int len) {
    const char *cursor = *src;

    // Consider negative number
    if (*cursor == '-') {
        *buffer++ = '-';
        cursor++;
        len--;
    }

    // Until point
    while (is_dec(*cursor) && len && *cursor != '.') {
        *buffer++ = *cursor++;
        len--;
    }

    // Consider point
    if (*cursor && *cursor == '.' && len) {
        *buffer++ = *cursor++;
        len--;
    }

    // After point
    while (is_dec(*cursor) && len) {
        *buffer++ = *cursor++;
        len--;
    }

    *buffer = '\0';
    *src = cursor;
}

int _read_exponent(const char **str, int width) {
    int exponent = 0;
    char buffer[5];
    char *buff_cursor = buffer;
    const char *cursor = *str;
    if (_is_scientific_notation_starts(cursor)) {
        cursor++;
        *buff_cursor++ = *cursor++;
        while (is_dec(*cursor) && width--)
            *buff_cursor++ = *cursor++;
        *buff_cursor = '\0';
        exponent = s21_atoi(buffer);
    }
    return exponent;
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
        struct uint_utils utils = { DEC, &is_dec, &_is_neg_num_starts, 0 };
        _parse_uint(str, arg_ptr, st, &utils);
    } else if (st->format.specifier == 'o') {
        struct uint_utils utils = { OCT, &is_dec, &_is_oct_prefix, 1 };
        _parse_uint(str, arg_ptr, st, &utils);
    } else if (st->format.specifier == 'x' || st->format.specifier == 'p') {
        struct uint_utils utils = { HEX, &is_hex, &_is_hex_prefix, 2 };
        _parse_uint(str, arg_ptr, st, &utils);
    } else if (s21_strchr("feg", st->format.specifier)) {
        _parse_float(str, arg_ptr, st);
    } else if (st->format.specifier == 'c') {

    } else if (st->format.specifier == 'n') {

    } else if (st->format.specifier == 'c') {

    } else if (st->format.specifier == 's') {

    } else if (st->format.specifier == 'n') {

    }
    st->correct_writes++;
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
    _ignore_space_chars(str);
    if (is_dec(**str) || _is_neg_num_starts(*str, st->format.width))  {
        char buffer[512];
        _read_number(buffer, str, st->format.width, &is_dec);

        if (!st->format.supress) {
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
    } else {
        st->failure = true;
    }
}

void _parse_uint(const char **str, void *ptr, struct scan_state *st, struct uint_utils* utils) {
    _ignore_space_chars(str);

    bool is_prefix = utils->prefix_check(*str, st->format.width);
    if (utils->num_check(**str) || is_prefix) {
        if (is_prefix) (*str) += utils->prefix_len;
        char buffer[512];
        _read_number(buffer, str, st->format.width, utils->num_check);

        long long unsigned parsed_num;

        // Negative number conversion to unsigned
        if (utils->base == DEC && buffer[0] == '-')
            parsed_num = s21_atoi(buffer);
        else
            parsed_num = s21_atou(buffer, utils->base);

        if (!st->format.supress) {
            if (st->format.length == LONG || st->format.specifier == 'p') {
                long unsigned *lptr = ptr;
                *lptr = parsed_num;
            } else if (st->format.length == LLONG) {
                long long unsigned *llptr = ptr;
                *llptr = parsed_num;
            } else if (st->format.length == SHORT) {
                short unsigned *sptr = ptr;
                *sptr = parsed_num;
            } else {
                unsigned *cptr = ptr;
                *cptr = parsed_num;
            }
        }
    } else {
        st->failure = true;
    }
}

void _parse_float(const char **str, void *ptr, struct scan_state *st) {
    _ignore_space_chars(str);
    if (is_dec(**str) ||
            _is_neg_num_starts(*str, st->format.width) ||
            _is_float_starts_with_point(*str, st->format.width)) {
        char buffer[1024];
        int width = st->format.width;
        _read_float(buffer, str, width);

        int exponent = 0;
        s21_size_t buffer_len = s21_strlen(buffer);
        if ((st->format.specifier == 'e' || st->format.specifier == 'g') &&
                (st->format.width == -1 || width - buffer_len > 3))
            exponent = _read_exponent(str, width - buffer_len);

        if (!st->format.supress) {
            long double parsed_num = s21_strtod(buffer) * powl(10.0L, exponent);
            if (st->format.length == LLONG) {
                long double *llptr = ptr;
                *llptr = parsed_num;
            } else if (st->format.length == LONG ) {
                double *lptr = ptr;
                *lptr = parsed_num;
            } else {
                float *cptr = ptr;
                *cptr = parsed_num;
            }
        }
    } else {
        st->failure = 1;
    }
}

