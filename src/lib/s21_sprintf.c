#ifndef S21_STRING_HELPERS
#define S21_STRING_HELPERS

#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>
#include <limits.h>
#include <float.h>

#include "s21_string.h"
#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
    char *start = str;
    va_list vars;

    va_start(vars, format);
    while (*format) {
        if (*format == '%') {
            format++;
            struct f_params params;
            format += _read_format_params(&params, (char*) format, vars);
            params.chars_printed = str - start;
            str += _convert_arg(str, vars, params);
        } else {
            *str++ = *format++;
        }
    }
    *str = '\0';
    va_end(vars);

    return str - start;
}

int _read_format_params(struct f_params* params, const char *format, va_list args) {
    _set_default_params(params);
    char *cursor = (char*) format;
    cursor += _read_flag(cursor, params, FLAGS);
    if (*cursor == '*') {
        int width = va_arg(args, int);
        params->width = width;
        cursor++;
    } else {
        cursor += _read_num(cursor, &(params->width));
    }
    if (*cursor == '.') {
        cursor++;
        if (*cursor == '*') {
            int precision = va_arg(args, int);
            params->precision = precision;
            cursor++;
        } else {
            cursor += _read_num(cursor, &(params->precision));
        }
        if (params->precision >= 0)
            params->default_precision = 0;
    }
    cursor += _read_spec(cursor, params->type);
    return cursor - format;
}

int _read_flag(const char *format, struct f_params *params, const char *values) {
    int len = 0;
    while (s21_strchr(values, *format)) {
        if (*format == '-')
            params->minus = 1;
        else if (*format == '#')
            params->sharp = 1;
        else if (*format == '0')
            params->zero = 1;
        else
            params->flag = *format;
        len++;
        format++;
    }
    return len;
}

int _read_spec(const char *format, char ch[5]) {
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

int _read_num(const char *format, int *num) {
    char *cursor = (char*) format;
    if (s21_strchr(FLAGS, *cursor))
        cursor++;
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
    params->minus = 0;
    params->sharp = 0;
    params->zero = 0;
    params->width = 0;
    params->precision = 0;
    params->default_precision = 1;
    for (int i = 0; i < 5; i++)
        params->type[i] = '\0';
}

int _convert_arg(char *str, va_list args, struct f_params params) {
    char *start = str;
    int len = 0;
    char buffer[100000];
    buffer[0] = '\0';

    // Parse arg to buffer
    if (s21_strpbrk(params.type, "id") != S21_NULL) {
        len += _int_to_str(buffer, args, params, 10);
    } else if (s21_strchr(params.type, 'u') != S21_NULL) {
        len += _uint_to_str(buffer, args, params, 10);
    } else if (s21_strchr(params.type, 'n')) {
        _get_printed_chars_num(args, params);
    } else if (s21_strchr(params.type, 'o')) {
        len += _uint_to_str(buffer, args, params, 8);
    } else if (s21_strpbrk(params.type, "xX")) {
        len += _uint_to_str(buffer, args, params, 16);
    } else if (s21_strchr(params.type, 'p')) {
        len += _ptr_to_str(buffer, args);
    } else if (s21_strpbrk(params.type, "feEgG") != S21_NULL) {
        len += _float_to_str(buffer, params, args);
    } else if (s21_strchr(params.type, 'c') != S21_NULL) {
        len += _chr_to_str(buffer, args);
    } else if (s21_strchr(params.type, 's') != S21_NULL) {
        len += _str_to_str(buffer, args, params);
    } else if (s21_strchr(params.type, '%') != S21_NULL) {
        *str++ = '%';
    }

    // Add padding and parsed arg
    int width = params.width;
    if (width < 0) {
        width = -width;
        params.minus = 1;
    }
    int padding_len = width > len ? width - len : 0;
    if (params.minus || params.width < 0) {
        s21_strncpy(str, buffer, len);
        str += len;
        _add_padding(str, padding_len, ' ');
        str += padding_len;
    } else {
        _add_padding(str, padding_len, ' ');
        str += padding_len;
        s21_strncpy(str, buffer, len);
        str += len;
    }
    return str - start;
}

int _int_to_str(char *buffer, va_list args, struct f_params params, int base) {
    int i = 0;
    if (params.type[0] == 'l' && params.type[1] == 'l') {
        long long value = va_arg(args, long long);
        unsigned long long arg = value < 0 ? -value : value;
        i += itoa(arg, buffer, base, value < 0, params);
    } else if (params.type[0] == 'l') {
        long value = va_arg(args, long);
        unsigned long long arg = value < 0 ? -value : value;
        i += itoa(arg, buffer, base, value < 0, params);
    } else if (params.type[0] == 'h') {
        short value = (short) va_arg(args, int);
        unsigned long long arg = value < 0 ? -value : value;
        i += itoa(arg, buffer, base, value < 0, params);
    } else {
        int value = va_arg(args, int);
        unsigned long long arg = value < 0 ? -value : value;
        if (value == INT_MIN)
            arg = (unsigned long long) INT_MAX + 1;
        i += itoa(arg, buffer, base, value < 0, params);
    }
    return i;
}

int _uint_to_str(char *buffer, va_list args, struct f_params params, int base) {
    int i = 0;
    if (params.type[0] == 'l' && params.type[1] == 'l') {
        i += itoa(va_arg(args, long long unsigned), buffer, base, 0, params);
    } else if (params.type[0] == 'l') {
        i += itoa(va_arg(args, long unsigned), buffer, base, 0, params);
    } else if (params.type[0] == 'h') {
        short unsigned arg = (short unsigned) va_arg(args, unsigned);
        i += itoa(arg, buffer, base, 0, params);
    } else {
        i += itoa(va_arg(args, unsigned), buffer, base, 0, params);
    }
    return i;
}

int _ptr_to_str(char *buffer, va_list args) {
    int i = 0;
    struct f_params params;
    _set_default_params(&params);
    params.type[0] = 'p';
    long unsigned arg = va_arg(args, long unsigned);
    if (arg != 0) {
        i += itoa(arg, buffer, 16, 0, params);
    } else {
        s21_strcpy(buffer, NULL_INT);
        i += s21_strlen(NULL_INT);
    }
    return i;
}

int _float_to_str(char *buffer, struct f_params params, va_list args) {
    int i = 0;
    if (params.type[0] == 'L')
        i += ftoa(va_arg(args, long double), buffer, params);
    else
        i += ftoa(va_arg(args, double), buffer, params);
    return i;
}

int _chr_to_str(char *buffer, va_list args) {
    int ch = va_arg(args, int);
    *buffer = ch;
    return 1;
}

int _str_to_str(char *buffer, va_list args, struct f_params params) {
    int i = 0;
    int chars_print = params.default_precision ? -1 : params.precision;
    if (s21_strchr(params.type, 'l')) {
        wchar_t *tmp = va_arg(args, wchar_t*);
        if (tmp != NULL) {
            while (*tmp && (chars_print)) {
                *buffer++ = *tmp++;
                chars_print--;
                i++;
            }
            *buffer = '\0';
        } else {
            s21_strcpy(buffer, "(null)");
            i += 6;
        }
    } else {
        char *str = va_arg(args, char*);
        if (str != NULL) {
            if (chars_print == -1)
                chars_print = s21_strlen(str);
            s21_strncpy(buffer, str, chars_print);
            buffer[chars_print] = '\0';
            i += chars_print;
        } else {
            s21_strcpy(buffer, "(null)");
            i += 6;
        }
    }
    return i;
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
int itoa(long long unsigned value, char* result, int base, int neg, struct f_params params) {
    char *cur = result;
    int precision = params.precision;
    int flag = params.flag;

    char *num_table = NUM_TABLE_LOWER;
    int upper_case = s21_strchr(params.type, 'X') != S21_NULL;
    if (upper_case)
        num_table = NUM_TABLE_UPPER;

    // Converting number
    unsigned long long temp_value = value;
    do {
        int index = temp_value % base;
        temp_value /= base;
        *cur++ = num_table[index];
    } while (temp_value);

    // Add zero padding
    int zero_padding_len = 0;
    if (value == 0 && precision == 0) {
        *--cur = '\0';
    } else if (precision > 0) {
        zero_padding_len = precision - (cur - result);
    } else if (params.zero && !params.minus) {
        zero_padding_len = params.width - (cur - result) - neg;
    }
    _add_padding(cur, zero_padding_len, '0');
    if (zero_padding_len > 0)
        cur += zero_padding_len;

    // Checking flags
    if (neg) {
        *cur++ = '-';
    } else if (base == 10 && s21_strchr(params.type, 'u') == S21_NULL && (flag == ' ' || flag == '+')) {
        *cur++ = flag;
    } else if (base == 16 && (params.sharp || s21_strchr(params.type, 'p'))) {
        *cur++ = upper_case ? 'X' : 'x';
        *cur++ = '0';
    } else if (base == 8 && params.sharp) {
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
    int neg = value < 0;
    int is_nan = isnan(value);
    int is_inf = isinf(value);
    char buffer[100000];
    if (params.default_precision)
        params.precision = 6;

    if (neg) value = -value;

    if (is_nan) {
        i = 3;
        char *nan = "nan";
        if (s21_strpbrk(params.type, "GE"))
            nan = "NAN";
        s21_strcpy(buffer, nan);
    } else if (is_inf) {
        i = 3;
        char *inf = "fni";
        if (s21_strpbrk(params.type, "GE"))
            inf = "FNI";
        s21_strcpy(buffer, inf);
    } else {
        if (s21_strchr(params.type, 'f')) {
            i += fntoa(buffer, value, params);
        } else if (s21_strpbrk(params.type, "eE")) {
            int exponent = _calc_exponent(value);
            i += fetoa(buffer, value, exponent, params);
        } else if (s21_strpbrk(params.type, "gG")) {
            int exponent = _calc_exponent(value);
            i += fgtoa(buffer, value, exponent, params);
        }

        // Add zero padding
        if (params.zero) {
            int zero_padding_len = params.width - (i + neg);
            _add_padding(buffer + i, zero_padding_len, '0');
            i += zero_padding_len > 0 ? zero_padding_len : 0;
        }
    }

    // Evaluating flags
    if (neg && !is_nan)
        buffer[i++] = '-';
    else if ((flag == ' ' || flag == '+') && !is_nan)
        buffer[i++] = flag;
    _reverse(buffer, buffer + i);
    buffer[i] = '\0';
    s21_strcpy(result, buffer);
    return i;
}

int fntoa(char *buffer, long double value, struct f_params params) {
    int precision = params.precision;
    int g_spec = s21_strpbrk(params.type, "gG") != NULL;
    int i = 0;
    long double int_part, float_part;
    float_part = fabsl(modfl(value, &int_part));
    if (precision > 0) {
        int write_trailing_nums = 0;
        int_part = fabsl(int_part);
        float_part = roundl(float_part * pow(10, precision));
        while (precision-- > 0) {
            int num = roundl(fmodl(float_part, 10));
            if (!g_spec || params.sharp || num || write_trailing_nums) {
                buffer[i++] = NUM_TABLE_LOWER[num];
                write_trailing_nums = 1;
            }
            float_part = truncl(float_part / 10);
        }
        params.sharp = 1;
    } else {
        int_part = roundl(value);
    }
    if (params.sharp)
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

int fetoa(char *buffer, long double value, int exponent, struct f_params params) {
    int i = 0;
    int precision = params.precision;
    int g_spec = s21_strpbrk(params.type, "gG") != NULL;
    int upper_case = s21_strpbrk(params.type, "EG") != NULL;
    long double mant = fabsl(value);
    mant = exp2l(log2l(mant) + log2l(powl(10, precision - exponent)));

    // Handling cases like 9.99 or 0.99 if number of digits after point less than precision
    if ((fmodl(roundl(mant), 10) < 1) ^ (fmodl(mant, 10) < 1))
        exponent++;

    int exponent_temp = exponent;
    if (exponent_temp < 0)
        exponent_temp = -exponent_temp;
    do {
        int index = exponent_temp % 10;
        buffer[i++] = NUM_TABLE_LOWER[index];
        exponent_temp /= 10;
    } while (exponent_temp);
    if (exponent < 10 && exponent > -10)
        buffer[i++] = '0';
    buffer[i++] = exponent < 0 ? '-' : '+';
    buffer[i++] = upper_case ? 'E' : 'e';

    if (precision > 0) {
        mant = roundl(mant);
        int write_trailing_nums = 0;
        int start_index = i;
        while (precision--) {
            int index = fmodl(mant, 10);
            if (!g_spec || params.sharp || index || write_trailing_nums) {
                buffer[i++] = NUM_TABLE_LOWER[index];
                write_trailing_nums = 1;
            }
            mant /= 10;
        }
        if (i > start_index)
            params.sharp = 1;
    } else {
        mant = roundl(mant);
    }
    if (params.sharp)
        buffer[i++] = '.';
    int index = fmodl(mant, 10);
    if (index < 1) {
        index = 1;
        // buffer[0] += 1;
    }
    buffer[i++] = NUM_TABLE_LOWER[index];
    return i;
}

int fgtoa(char *buffer, long double value, int exponent, struct f_params params) {
    int i = 0;
    if (params.precision > exponent && exponent >= -4) {
        params.precision -= exponent + 1;
        i += fntoa(buffer, value, params);
    } else {
        params.precision -= 1;
        i += fetoa(buffer, value, exponent, params);
    }
    return i;
}

int _calc_exponent(long double num) {
    int exponent = 0;
    num = fabsl(num);
    if (num < 1) {
        do {
            num *= 10;
            exponent--;
        } while (num < 1);
    } else if (num > 10) {
        do {
            num /= 10;
            exponent++;
        } while (num > 10);
    }

    return exponent;
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
