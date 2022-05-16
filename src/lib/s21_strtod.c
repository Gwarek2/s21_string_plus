#include <math.h>
#include "s21_string.h"

long double _convert_float_part(long double value, int exp);

long double s21_strtod(char *buffer) {
    char *int_part = buffer;
    char *float_part = s21_strchr(buffer, '.');

    if (float_part != S21_NULL)
        *float_part++ = '\0';

    long double result = s21_atoi(int_part);
    if (float_part != S21_NULL) {
        int exponent = s21_strlen(float_part);
        long double fl = s21_atoi(float_part);
        result += _convert_float_part(fl, exponent);
    }
    return result;
}

long double _convert_float_part(long double value, int exp) {
    while (exp--)
        value = exp2(log2(value) - log2(10));
    return value;
}

