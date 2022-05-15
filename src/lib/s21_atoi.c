#include "s21_string.h"


long long s21_atoi(char *str) {
    long long num = 0;
    long long dec = 1;

    if (*str) {
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
    }
    return num;
}
