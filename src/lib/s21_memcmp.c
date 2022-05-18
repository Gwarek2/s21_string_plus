#include <stdbool.h>
#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    const unsigned char *cursor1 = (const unsigned char*) str1;
    const unsigned char *cursor2 = (const unsigned char*) str2;
    while (true) {
        if (n-- == 0 || n == 0 ||
            *cursor1 != *cursor2) break;
        cursor1++;
        cursor2++;
    }
    return *cursor1 - *cursor2;
}

