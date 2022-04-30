#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "s21_string.h"
#include "s21_string_helpers.h"


int read_format_params(struct f_params* params, char *format) {
    _set_default_params(params);
    char *start = format;
    format += _read_f_char(format, &(params->flag), FLAGS);
    format += _read_f_num(format, &(params->wid));
    if (*format == '.') {
        format++;
        format += _read_f_num(format, &(params->prec));
    }
    format += _read_f_char(format, &(params->len), LENGTH);
    format += _read_f_char(format, &(params->spec), SPECS);
    return format - start;
}

int _read_f_char(char *format, char *ch, const char *values) {
    int len = 0;
    char *result = (char*) s21_memchr(values, *format, s21_strlen(values));
    if (result != NULL) {
        *ch = *result;
        len = 1;
    }
    return len;
}

int _read_f_num(char *format, int *num) {
    char *cursor = format;
    while (*cursor >= '0' && *cursor <= '9')
        cursor++;
    if (cursor > format) {
        static char result[100];
        char tmp = *cursor;
        s21_memcpy((void*) result, format, cursor - format);
        *num = atoi(result);
    }
    return cursor - format;
}

void _set_default_params(struct f_params *params) {
    params->flag = '\0';
    params->wid = 0;
    params->prec = 6;
    params->len = '\0';
    params->spec = '\0';
}

// Returns length of resulting string
int itoa(int value, char* result, int base) {
    char *cur = result;
    int neg = value < 0;
    if (neg) value = -value;
    do {
        int index = value % base;
        value /= base;
        *cur++ = _base_values(index, base);
    } while (value);
    if (neg) *cur++ = '-';

    _reverse(result, cur);
    *cur = '\0';
    return cur - result;
}

// Returns length of resulting string
int dtoa(double value, char *result, int precision) {
    int i = 0;
    if (isnan(value)) {
        i = 3;
        s21_memcpy((void*) result, (void*) "nan", i);
    } else if (isinf(value)) {
        i = 3;
        s21_memcpy((void*) result, (void*) "inf", i);
    } else {
        int int_part = (int) value;
        i += itoa(int_part, result, 10);

        double float_part = fabs(value - (float) int_part);
        if (precision > 0) {
            result[i] = '.';
            while (float_part * 10 < 1) {
                result[++i] = '0';
                float_part *= 10;
                precision--;
            }
            float_part = float_part * pow(10, precision);
            i += itoa((int) float_part, result + i + 1, 10) + 1;
        }
    }
    return i;
}

char _base_values(int i, int base) {
    char ch = '\0';
    if (base == OCT)
        ch = OCT_VALUES[i];
    else if (base == HEX)
        ch = HEX_VALUES[i];
    else
        ch = DEC_VALUES[i];
    return ch;
}

char* _reverse(char* start, char *end) {
    char *result = start;
    while (start < end--) {
        char tmp = *end;
        *end = *start;
        *start++ = tmp;
    }
    return result;
}