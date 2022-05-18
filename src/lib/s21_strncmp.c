#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    s21_size_t i = 0;
    int res = 0;

    if (n > 0) {
        while (str1[i] == str2[i] && i < n - 1)
            i++;
        if (str1[i] != str2[i])
            res = str1[i] - str2[i];
    }
    return res;
}
