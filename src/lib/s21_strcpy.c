#include "../s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
    char* start = dest;
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
    return start;
}
