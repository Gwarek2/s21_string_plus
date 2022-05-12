#include "s21_string.h"


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
