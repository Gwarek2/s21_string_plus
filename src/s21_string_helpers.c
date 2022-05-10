#ifndef S21_STRING_HELPERS
#define S21_STRING_HELPERS

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>

#include "s21_string.h"
#include "s21_string_helpers.h"


int read_format_params(struct f_params* params, const char *format, va_list args) {
    _set_default_params(params);
    char *cursor = (char*) format;
    cursor += _read_f_flag(cursor, &(params->flag), FLAGS);
    if (*cursor == '*') {
        params->width = va_arg(args, int);
        cursor++;
    } else {
        cursor += _read_f_num(cursor, &(params->width));
    }
    if (*cursor == '.') {
        cursor++;
        if (*cursor == '*') {
            params->precision = va_arg(args, int);
            cursor++;
        } else {
            cursor += _read_f_num(cursor, &(params->precision));
        }
    }
    cursor += _read_f_spec(cursor, params->type);
    return cursor - format;
}

int _read_f_flag(const char *format, char *ch, const char *values) {
    int len = 0;
    char *result = s21_strchr(values, *format);
    if (result != S21_NULL) {
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
    if (s21_strchr(SPECS, format[i])) {
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
        char result[100];
        s21_strncpy(result, format, cursor - format);
        result[cursor - format] = '\0';
        *num = s21_atoi(result);
    }
    return cursor - format;
}

void _set_default_params(struct f_params *params) {
    params->flag = '\0';
    params->width = 0;
    params->precision = -1;
    for (int i = 0; i < 5; i++)
        params->type[i] = '\0';
}

int convert_arg(char *str, va_list args, struct f_params params) {
    char *start = str;
    char buffer[100000];
    buffer[0] = '\0';

    // Parse arg to buffer
    if (s21_strpbrk(params.type, "id") != S21_NULL) {
        _int_to_str(buffer, args, params, 10);
    } else if (s21_strchr(params.type, 'u') != S21_NULL) {
        _uint_to_str(buffer, args, params, 10);
    } else if (s21_strchr(params.type, 'n')) {
        _get_printed_chars_num(args, params);
    } else if (s21_strchr(params.type, 'o')) {
        _uint_to_str(buffer, args, params, 8);
    } else if (s21_strpbrk(params.type, "xX")) {
        _uint_to_str(buffer, args, params, 16);
    } else if (params.type[0] == 'p') {
        _ptr_to_str(buffer, args);
    } else if (s21_strpbrk(params.type, "feEgG") != S21_NULL) {
        _float_to_str(buffer, params, args);
    } else if (s21_strchr(params.type, 'c') != S21_NULL) {
        _chr_to_str(buffer, args);
    } else if (s21_strchr(params.type, 's') != S21_NULL) {
        _str_to_str(buffer, args, params);
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
        _add_padding(str, padding_len, ' ');
        str += padding_len;
    } else {
        _add_padding(str, padding_len, ' ');
        str += padding_len;
        s21_strncpy(str, buffer, buff_len);
        str += buff_len;
    }
    return str - start;
}

void _int_to_str(char *buffer, va_list args, struct f_params params, int base) {
    if (params.type[0] == 'l' && params.type[1] == 'l') {
        itoa(va_arg(args, long long), buffer, base, params);
    } else if (params.type[0] == 'l') {
        itoa(va_arg(args, long), buffer, base, params);
    } else if (params.type[0] == 'h') {
        short arg = (short) va_arg(args, int);
        itoa(arg, buffer, base, params);
    } else {
        itoa(va_arg(args, int), buffer, base, params);
    }
}

void _uint_to_str(char *buffer, va_list args, struct f_params params, int base) {
    if (params.type[0] == 'l' && params.type[1] == 'l') {
        itoa(va_arg(args, long long unsigned), buffer, base, params);
    } else if (params.type[0] == 'l') {
        itoa(va_arg(args, long unsigned), buffer, base, params);
    } else if (params.type[0] == 'h') {
        short unsigned arg = (short unsigned) va_arg(args, unsigned);
        itoa(arg, buffer, base, params);
    } else {
        itoa(va_arg(args, unsigned), buffer, base, params);
    }
}

void _ptr_to_str(char *buffer, va_list args) {
    struct f_params params;
    _set_default_params(&params);
    params.type[0] = 'p';
    itoa(va_arg(args, long unsigned), buffer, 16, params);
}

void _float_to_str(char *buffer, struct f_params params, va_list args) {
    if (params.type[0] == 'L')
        ftoa(va_arg(args, long double), buffer, params);
    else
        ftoa(va_arg(args, double), buffer, params);
}

void _chr_to_str(char *buffer, va_list args) {
    int ch = va_arg(args, int);
    *buffer = ch;
    buffer[1] = '\0';
}

void _str_to_str(char *buffer, va_list args, struct f_params params) {
    int chars_print = params.precision;

    if (s21_strchr(params.type, 'l')) {
        wchar_t *tmp = va_arg(args, wchar_t*);
        while (*tmp && (chars_print)) {
            *buffer++ = *tmp++;
            chars_print--;
        }
        *buffer = '\0';
    } else {
        char *str = va_arg(args, char*);
        if (chars_print == -1)
            chars_print = s21_strlen(str);
        s21_strncpy(buffer, str, chars_print);
        buffer[chars_print] = '\0';
    }
}

void _get_printed_chars_num(va_list args, struct f_params params) {
    int *arg_ptr = va_arg(args, int*);
    *arg_ptr = params.chars_printed;
}

void _add_padding(char *str, int len, char ch) {
    for (int i = 0; i < len; i++)
        *str++ = ch;
}

// Returns length of resulting string
int itoa(long long value, char* result, int base, struct f_params params) {
    char *cur = result;
    int neg = value < 0;
    int precision = params.precision;
    int flag = params.flag;

    char *num_table = NUM_TABLE_LOWER;
    int upper_case = s21_strchr(params.type, 'X') != S21_NULL;
    if (upper_case)
        num_table = NUM_TABLE_UPPER;

    if (neg) value = -value;
    do {
        long long index = value % base;
        value /= base;
        *cur++ = num_table[index];
    } while (value);

    int zero_padding_len = 0;
    if (precision != -1)
        zero_padding_len = precision - (cur - result);
    else if (flag == '0')
        zero_padding_len = params.width - (cur - result) - neg;
    _add_padding(cur, zero_padding_len, '0');
    if (zero_padding_len > 0)
        cur += zero_padding_len;

    if (neg) {
        *cur++ = '-';
    } else if (base == 10 && s21_strchr(params.type, 'u') == S21_NULL && (flag == ' ' || flag == '+')) {
        *cur++ = flag;
    } else if (base == 16 && (flag == '#' || s21_strchr(params.type, 'p'))) {
        *cur++ = upper_case ? 'X' : 'x';
        *cur++ = '0';
    } else if (base == 8 && flag == '#') {
        *cur++ = '0';
    }

    _reverse(result, cur);
    *cur = '\0';
    return cur - result;
}

// Returns length of resulting string
int ftoa(long double value, char *result, struct f_params params) {
    int i = 0;
    int flag = params.flag;
    int precision = params.precision;
    if (params.precision == -1)
        precision = 6;

    if (isnan(value)) {
        i = 3;
        s21_strcpy(result, "nan");
    } else if (isinf(value)) {
        i = 3;
        s21_strcpy(result, "inf");
    } else {
        int neg = value < 0;
        char buffer[100000];
        if (s21_strchr(params.type, 'f')) {
            i += fntoa(buffer, value, precision, flag, 0);
        } else if (s21_strpbrk(params.type, "eE")) {
            int exp = _calc_exp(value);
            int upper_case = s21_strchr(params.type, 'E') != NULL;
            i += fetoa(buffer, value, exp, precision, flag, upper_case);
        } else if (s21_strpbrk(params.type, "gG")) {
            int exp = _calc_exp(value);
            int upper_case = s21_strchr(params.type, 'G') != NULL;
            i += fgtoa(buffer, value, exp, precision, flag, upper_case);
        }

        if (flag == '0') {
            int zero_padding_len = params.width - (i + neg);
            _add_padding(buffer + i, zero_padding_len, '0');
            i += zero_padding_len > 0 ? zero_padding_len : 0;
        }
        if (neg)
            buffer[i++] = '-';
        else if (flag == ' ' || flag == '+')
            buffer[i++] = flag;
        _reverse(buffer, buffer + i);

        buffer[i] = '\0';
        s21_strcpy(result, buffer);
    }
    return i;
}

int fntoa(char *buffer, long double value, int precision, char flag, int g_spec) {
    int i = 0;
    long double int_part, float_part;
    float_part = fabsl(modfl(value, &int_part));
    if (precision > 0) {
        int write_trailing_nums = 0;
        int_part = fabsl(int_part);
        float_part = roundl(float_part * pow(10, precision));
        while (precision-- > 0) {
            int num = roundl(fmodl(float_part, 10));
            if (!g_spec || num || write_trailing_nums) {
                buffer[i++] = NUM_TABLE_LOWER[num];
                write_trailing_nums = 1;
            }
            float_part = truncl(float_part / 10.0);
        }
        flag = '#';
    } else {
        int_part = roundl(value);
    }
    if (flag == '#')
        buffer[i++] = '.';

    if (int_part >= 1) {
        int_part += float_part;
        while (int_part >= 1) {
            int num = (int) fmodl(int_part, 10);
            buffer[i++] = NUM_TABLE_LOWER[num];
            int_part = truncl(int_part / 10.0);
        }
    } else {
        buffer[i++] = '0';
    }
    return i;
}

int fetoa(char *buffer, long double value, int exp, int precision, char flag, int upper_case) {
    int i = 0;
    long double mant = fabsl(value);
    if (exp < 0)
        mant = mant * powl(10, -exp);
    else
        mant = mant / powl(10, exp);

    int exp_temp = exp;
    if (exp_temp < 0)
        exp_temp = -exp_temp;
    do {
        int index = exp_temp % 10;
        buffer[i++] = NUM_TABLE_LOWER[index];
        exp_temp /= 10;
    } while (exp_temp);
    if (exp < 10 && exp > -10)
        buffer[i++] = '0';
    buffer[i++] = exp < 0 ? '-' : '+';
    buffer[i++] = upper_case ? 'E' : 'e';

    if (precision > 0) {
        mant = roundl(mant * powl(10, precision));
        while (precision--) {
            int index = fmodl(mant, 10);
            buffer[i++] = NUM_TABLE_LOWER[index];
            mant /= 10;
        }
        flag = '#';
    } else {
        mant = roundl(mant);
    }
    if (flag == '#')
        buffer[i++] = '.';
    int index = fmodl(mant, 10);
    if (index < 1) {
        index = 1;
        // buffer[0] += 1;
    }
    buffer[i++] = NUM_TABLE_LOWER[index];
    return i;
}

int fgtoa(char *buffer, long double value, int exp, int precision, char flag, int upper_case) {
    int i = 0;
    if (precision > exp && exp >= -4) {
        i += fntoa(buffer, value, precision - (exp + 1), flag, 1);
    } else {
        i += fetoa(buffer, value, exp, precision - 1, flag, upper_case);
    }
    return i;
}

int _calc_exp(long double num) {
    int exp = 0;
    num = fabsl(num);
    if (num < 1) {
        do {
            num *= 10;
            exp--;
        } while (num < 1);
    } else if (num > 10) {
        do {
            num /= 10;
            exp++;
        } while (num > 10);
        if (fmodl(roundl(num), 10) < 1)
            exp++;
    }
    return exp;
}

int s21_atoi(char *str) {
    int num = 0;
    int dec = 1;

    char *cursor = str + s21_strlen(str) - 1;
    while (str < cursor) {
        num += (*cursor - 48) * dec;
        dec *= 10;
        cursor--;
    }

    if (*cursor == '-')
        num = -num;
    else
        num += (*cursor - 48) * dec;
    return num;
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

#endif  // S21_STRING_HELPERS
