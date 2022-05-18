#include <stdbool.h>
#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
    char *result = S21_NULL;
    const char *start = str;
    const char *cursor = start + s21_strlen(str);
    while (true) {
        if (*cursor == c || cursor == start) break;
        cursor--;
    }

    if (*cursor == c)
        result = (char*) cursor;
    return result;
}

