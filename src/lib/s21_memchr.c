#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
    void *result = S21_NULL;
    const unsigned char *cursor = (const unsigned char*) str;
    const unsigned char ch = c;
    while (n > 0 && result == S21_NULL) {
        if (*cursor == ch)
            result = (void*) cursor;
        cursor++;
        n--;
    }
    return result;
}

