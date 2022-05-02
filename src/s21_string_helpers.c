#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>

#include "s21_string.h"
#include "s21_string_helpers.h"


int read_format_params(struct f_params* params, const char *format) {
    _set_default_params(params);
    char *start = (char*) format;
    char *fmt = (char*) format;
    fmt += _read_f_char(fmt, &(params->flag), FLAGS);
    fmt += _read_f_num(fmt, &(params->width));
    if (*fmt == '.') {
        fmt++;
        fmt += _read_f_num(fmt, &(params->precision));
    }
    fmt += _read_f_spec(fmt, params->type);
    return fmt - start;
}

int _read_f_char(const char *format, char *ch, const char *values) {
    int len = 0;
    char *result = (char*) s21_memchr(values, *format, s21_strlen(values));
    if (result != NULL) {
        *ch = *result;
        len = 1;
    }
    return len;
}

int _read_f_spec(char *format, char ch[5]) {
    int i = 0;
    char buff[5];
    if (format[i] == 'l' || format[i] == 'L' || format[i] == 'h') {
        buff[i] = format[i];
        i++;
    }
    if (format[i] == 'l' && format[i - 1] == 'l') {
        buff[i] = format[i];
        i++;
    }
    if (s21_memchr(SPECS, format[i], s21_strlen(SPECS))) {
            buff[i] = format[i];
            i++;
    }
    buff[i++] ='\0';
    s21_memcpy((void*) ch, buff, 5);
    return i;
}

int _read_f_num(char *format, int *num) {
    char *cursor = format;
    while (*cursor >= '0' && *cursor <= '9')
        cursor++;
    if (cursor > format) {
        static char result[100];
        s21_memcpy((void*) result, format, cursor - format);
        *num = atoi(result);
    }
    return cursor - format;
}

void _set_default_params(struct f_params *params) {
    params->flag = '\0';
    params->width = 0;
    params->precision = 6;
}

 
// int convert_arg(char *str, long long arg, struct f_params params) {
//     int len = 0;
//     if (params.specifier == 'd' || params.specifier == 'i') {
//         if (params.length == 'l') {

//         } else if (params.length == 'h') {

//         } else {

//         }
//     } else if (params.specifier == 's') {

//     } else if (params.specifier == 'u') {
//         if (params.length == 'l') {

//         } else if (params.length == 'h') {

//         } else {

//         }
//     } else if (params.specifier == 'f') {
//         if (params.length == 'l') {

//         } else if (params.length == 'h') {

//         } else {

//         }
//     } else if (params.specifier == 'c') {
        
//     } else if (params.specifier == '%') {
//         *str++ = '%';
//     } else {

//     }
//     return len;
// }

// Returns length of resulting string
int itoa(long long value, char* result, int base) {
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
int dtoa(long double value, char *result, int precision) {
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

        long double float_part = fabsl(value - (float) int_part);
        if (precision > 0) {
            result[i] = '.';
            while (float_part * 10 < 1) {
                result[++i] = '0';
                float_part *= 10;
                precision--;
            }
            float_part = round(float_part * pow(10, precision));
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
