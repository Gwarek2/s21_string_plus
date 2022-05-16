#include "s21_string.h"


long long unsigned s21_atou(char *str) {
    long long unsigned num = 0;
    long long unsigned dec = 1;

    if (*str) {
        char *cursor = str + s21_strlen(str) - 1;
        while (1) {
            num += (*cursor - 48) * dec;
            dec *= 10;
            if (str == cursor) break;
            cursor--;
        }
    }
    return num;
}
