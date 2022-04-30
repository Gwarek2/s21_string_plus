#include <stdio.h>
#include <math.h>

#include "s21_string.h"
#include "s21_converters.h"

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
        i = itoa(int_part, result, 10);

        double float_part = fabs(value - (float) int_part);
        if (precision > 0) {
            result[i] = '.';
            float_part = float_part * pow(10, precision);
            i = itoa((int) float_part, result + i + 1, 10);
        }
    }
    return i;
}
