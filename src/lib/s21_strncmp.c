#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    s21_size_t i = 0;
    int result = 0;
    while (*str1 && *str2 && *str1 == *str2 && i < n) {
        str1++;
        str2++;
        i++;
    }
    if (*str1 != *str2)
        result = *str1 > *str2 ? 1 : -1;
    return result;
}
