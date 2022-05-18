#include <stdlib.h>

#include "../s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    unsigned char *cdest = (unsigned char*) dest;
    unsigned char *csrc = (unsigned char*) src;
    unsigned char *tmp = calloc(n + 1, sizeof(unsigned char));
    for (s21_size_t i = 0; i < n; i++)
        tmp[i] = *csrc++;
    for (s21_size_t i = 0; i < n; i++)
        *cdest++ = tmp[i];
    free(tmp);
    return dest;
}

