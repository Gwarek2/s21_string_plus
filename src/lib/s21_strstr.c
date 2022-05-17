#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
    char *result = S21_NULL;
    if (!*haystack && !*needle)
        result = "";

    while (*haystack && result == S21_NULL) {
        const char *h_cursor = haystack;
        const char *n_cursor = needle;
        while (*n_cursor && *n_cursor == *h_cursor) {
            n_cursor++;
            h_cursor++;
        }
        if (!*n_cursor)
            result = (char*) haystack;
        haystack++;
    }
    return result;
}
