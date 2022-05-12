#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    s21_size_t i = 0;
    unsigned char *cursor1 = (unsigned char*) str1;
    unsigned char *cursor2 = (unsigned char*) str2;
    while (i < n && cursor1[i] == cursor2[i])
        i++;
    return cursor1[i] - cursor2[i];
}

