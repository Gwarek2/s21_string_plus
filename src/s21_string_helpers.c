#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>

#include "s21_string.h"
#include "s21_string_helpers.h"


int read_format_params(struct f_params* params, const char *format) {
    _set_default_params(params);
    char *cursor = (char*) format;
    cursor += _read_f_char(cursor, &(params->flag), FLAGS);
    cursor += _read_f_num(cursor, &(params->width));
    if (*cursor == '.') {
        cursor++;
        cursor += _read_f_num(cursor, &(params->precision));
    }
    cursor += _read_f_spec(cursor, params->type);
    return cursor - format;
}

int _read_f_char(const char *format, char *ch, const char *values) {
    int len = 0;
    char *result = s21_strchr(values, *format);
    if (result != NULL) {
        *ch = *result;
        len = 1;
    }
    return len;
}

int _read_f_spec(const char *format, char ch[5]) {
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
    buff[i] ='\0';
    s21_strcpy(ch, buff);
    return i;
}

int _read_f_num(const char *format, int *num) {
    char *cursor = (char*) format;
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
    params->precision = -1;
}

 
int convert_arg(char *str, va_list args, struct f_params params) {
    char *start = str;
    char buffer[1000];

    // Parse arg to buffer
    if (s21_strpbrk(params.type, "id") != S21_NULL) {
        if (params.type[0] == 'l' && params.type[1] == 'l') {
            itoa(va_arg(args, long long), buffer, 10, params.flag, params.precision);
        } else if (params.type[0] == 'l') {
            itoa(va_arg(args, long), buffer, 10, params.flag, params.precision);
        } else {
            itoa(va_arg(args, int), buffer, 10, params.flag, params.precision);
        }
    } else if (s21_strchr(params.type, 'u') != S21_NULL) {
        if (params.type[0] == 'l' && params.type[1] == 'l') {
            itoa(va_arg(args, long long unsigned), buffer, 10, params.flag, params.precision);
        } else if (params.type[0] == 'l') {
            itoa(va_arg(args, long unsigned), buffer, 10, params.flag, params.precision);
        } else {
            itoa(va_arg(args, unsigned int), buffer, 10, params.flag, params.precision);
        }
    } else if (s21_strchr(params.type, 'f') != S21_NULL) {
        if (params.precision == -1)
            params.precision = 6;
        if (params.type[0] == 'L')
            dtoa(va_arg(args, long double), buffer, params.precision);
        else 
            dtoa(va_arg(args, double), buffer, params.precision);
    } else if (s21_strchr(params.type, 'c') != S21_NULL) {
        *buffer = va_arg(args, int);
        buffer[1] = '\0';
    } else if (s21_strchr(params.type, 's') != S21_NULL) {
        s21_strcpy(buffer, va_arg(args, char*));
    } else if (s21_strchr(params.type, '%') != S21_NULL) {
        *buffer = '%';
        buffer[1] = '\0';
    }

    // Add padding and parsed arg
    int buff_len = s21_strlen(buffer);
    int padding_len = params.width > buff_len ? params.width - buff_len : 0;
    if (params.flag == '-') {
        s21_strncpy(str, buffer, buff_len);
        str += buff_len;
        _add_padding(str, padding_len);
        str += padding_len;
    } else {
        _add_padding(str, padding_len);
        str += padding_len;
        s21_strncpy(str, buffer, buff_len);
        str += buff_len;
    }
    return str - start;
}

void _add_padding(char *str, int len) {
    for (int i = 0; i < len; i++)
        *str++ = ' ';
}

// Returns length of resulting string
int itoa(long long value, char* result, int base, char flag, int precision) {
    char *cur = result;
    int neg = value < 0;
    if (neg) value = -value;
    do {
        long long index = value % base;
        value /= base;
        *cur++ = _base_values(index, base);
    } while (value);

    int zero_padding_len = precision - (cur - result);
    while (zero_padding_len-- > 0)
        *cur++ = '0';

    if (neg)
        *cur++ = '-';
    else if (flag == ' ' || flag == '+')
        *cur++ = flag;

    _reverse(result, cur);
    *cur = '\0';
    return cur - result;
}

// Returns length of resulting string
int dtoa(double value, char *result, int precision) {
    int i = 0;
    if (isnan(value)) {
        i = 3;
        s21_strcpy(result, "nan");
    } else if (isinf(value)) {
        i = 3;
        s21_strcpy(result, "inf");
    } else {
        long long int_part = (long long) value;
        i += itoa(int_part, result, 10, 0, 0);

        double float_part = fabs(value - (double) int_part);
        // printf("%f\n", float_part);
        if (precision > 0) {
            result[i] = '.';
            while (float_part * 10 < 1) {
                result[++i] = '0';
                float_part *= 10;
                precision--;
            }
            // printf("%f %i\n", float_part, precision);
            float_part = round(float_part * pow(10, precision));
            // printf("%lld\n", (long long) float_part);
            i += itoa((long long) float_part, result + i, 10, 0, 0) + 1;
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

// int main() {
//     double n1 = 1.23;
// 
//     char buff1[100];
// 
//     dtoa(n1, buff1, 3);
//     printf("%s\n", buff1);
//     return 0;
// }
