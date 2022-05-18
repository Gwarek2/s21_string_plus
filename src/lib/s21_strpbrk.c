#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
    char *result = S21_NULL;
    while (*str1 && result == S21_NULL) {
        char *cursor = (char*) str2;
        while (*cursor) {
            if (*cursor++ == *str1)
                result = (char*) str1;
        }
        str1++;
    }
    return result;
}
