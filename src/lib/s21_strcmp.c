#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
    int result = 0;
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    if (*str1 != *str2)
        result = *str1 > *str2 ? 1 : -1;
    return result;
}
