#include <stdlib.h>
#include "s21_string.h"

void del_space_chars(const char **start, const char **end);

void *s21_trim(const char *src, const char *trim_chars) {
    char *result = S21_NULL;
    if (src != S21_NULL) {
        const char *start = src;
        const char *end = src + s21_strlen(src) - 1;
        if (trim_chars == S21_NULL || !*trim_chars) {
            del_space_chars(&start, &end);
        } else {
            while (*start && s21_strchr(trim_chars, *start) != S21_NULL)
                start++;
            while (end > start && s21_strchr(trim_chars, *end) != S21_NULL)
                end--;
        }
        s21_size_t len = end - start + 2;
        result = calloc(len, sizeof(char));
        s21_strncpy(result, start, len - 1);
        result[len - 1] = '\0';
    }
    return result;
}

void del_space_chars(const char **start, const char **end) {
    const char *s = *start;
    const char *e = *end;
    while (*s && *s <= 32)
        s++;
    while (e > s && *e <= 32)
        e--;
    *start = s;
    *end = e;
}
