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

 
int convert_arg(char *str, long double arg, struct f_params params) {
    char *start = str;
    char buffer[100];
    if (s21_strpbrk(params.specifier, "id") != S21_NULL) {
        if (params.specifier[0] == 'l' && params.specifier[1] == 'l') {
            long long value = (long long) arg;
        } else if (params.specifier[0] == 'l') {
            long value = (long) arg;
        } else if (params.specifier[0] == 'h') {
            short value = (short) arg;
        } else {
            int value = (int) arg;
        }
        itoa(value, buffer, 10)
    } else if (s21_strchr(params.specifier, 'f') != S21_NULL) {
        if (param.specifier[0] != 'L')
            double value = (double) arg;
        else
            long double value = arg;
        dtoa(value, buffer, params.precision));
    } else if (s21_strchr(params.specifier, 'c') != S21_NULL) {
        *buffer = (char) arg;
        buffer[1] = '\0';
    } else if (s21_strchr(params.specifier, 's') != S21_NULL) {
        char *value = (char*) arg;
        int arg_len = s21_strlen(arg);
        s21_strcpy(arg, buffer, arg_len);
    } else if (params.specifier == '%') {
        *buffer = '%';
        buffer[1] = '\0';
    }
    int padding_len = params.width - s21_strlen(buffer);
    for (int i = 0; i < padding_len; i++)
        str++ = ' ';
    s21_strncpy(buffer, str, s21_strlen(buffer));
    return str - start;
}

// Returns length of resulting string
int itoa(long long value, char* result, int base, char flag) {
    char *cur = result;
    int neg = value < 0;
    if (neg) value = -value;
    do {
        long long index = value % base;
        value /= base;
        *cur++ = _base_values(index, base);
    } while (value);
    if (neg)
        *cur++ = '-';
    else if (flag == ' ' || flag == '+')
        *cur++ == flag;

    _reverse(result, cur);
    *cur = '\0';
    return cur - result;
}

// Returns length of resulting string
int dtoa(long double value, char *result, int precision) {
    int i = 0;
    if (isnan(value)) {
        i = 3;
        s21_strcpy((void*) result, (void*) "nan", i);
    } else if (isinf(value)) {
        i = 3;
        s21_strcpy(result, "inf", i);
    } else {
        long long int_part = (long long) value;
        i += itoa(int_part, result, 10);

        long double float_part = fabsl(value - (long double) int_part);
        // printf("%Lf\n", float_part);
        if (precision > 0) {
            result[i] = '.';
            while (float_part * 10 < 1) {
                result[++i] = '0';
                float_part *= 10;
                precision--;
            }
            float_part = round(float_part * pow(10, precision));
            // printf("%lld\n", (long long) floor(float_part));
            i += itoa(float_part, result + i + 1, 10) + 1;
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

int main() {
    double n1 = 127.23;
    float n2 = 127.23;
    char c = 'a';
    long double k = (long double) c;
    printf("%c\n", (char) k);

    char buff1[100];
    char buff2[100];

    dtoa(n1, buff1, 19);
    dtoa(n2, buff2, 19);
    printf("%.30f %.30f\n%s %s\n", n1, n2, buff1, buff2);
    printf("%u\n", sizeof(float));
    return 0;
}
