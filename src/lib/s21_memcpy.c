#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    unsigned char *cursor_dest = (unsigned char*) dest;
    unsigned char *cursor_src = (unsigned char*) src;
    for (s21_size_t i = 0; i < n; i++)
        cursor_dest[i] = cursor_src[i];
    return dest;
}
