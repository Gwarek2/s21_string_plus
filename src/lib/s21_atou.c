#include "s21_string.h"

int _convert_char(char ch);

long long unsigned s21_atou(char *str, int base) {
    long long unsigned num = 0;
    long long unsigned multiplier = 1;

    if (*str) {
        char *cursor = str + s21_strlen(str) - 1;
        while (1) {
            num += _convert_char(*cursor) * multiplier;
            multiplier *= base;
            if (str == cursor) break;
            cursor--;
        }
    }
    return num;
}

int _convert_char(char ch) {
    if (ch >= '0' && ch <= '9')
        ch -= '0';
    else if (ch >= 'a' && ch <= 'f')
        ch -= 'a' - 10;
    else if (ch >= 'A' && ch <= 'F')
        ch -= 'A' - 10;
    return ch;
}
