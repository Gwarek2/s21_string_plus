#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
    char *result = S21_NULL;
    char *start = (char*) str;
    char *cursor = start + s21_strlen(str) - 1;
    while (*cursor != c && cursor != start)
        cursor--;

    if (*cursor == c)
        result = cursor;
    return result;
}

