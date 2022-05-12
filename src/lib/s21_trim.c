#include <stdlib.h>
#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
    s21_size_t length = src != S21_NULL ? s21_strlen(src) : 0;
    s21_size_t indexStartStr = 0;
    s21_size_t indexFinishStr = 0;

    for (s21_size_t i = 0; i < length && trim_chars != S21_NULL && src != S21_NULL; i++) {
        char *symbol = (char*) trim_chars;
        int status = 1;
        while (*symbol) {
            if (*symbol == src[i])
                status = 0;
            symbol++;
        }
        if (status) {
            indexStartStr = i;
            i = length;
        }
    }

    for (s21_size_t i = length - 1; i > 0 && !indexFinishStr && trim_chars != S21_NULL && src != S21_NULL; i--) {
        char *symbol = (char*) trim_chars;
        int status = 1;
        while (*symbol) {
            if (*symbol == src[i])
                status = 0;
            symbol++;
        }
        if (status) indexFinishStr = i;
    }

    char *resultStr = src && trim_chars ? malloc((indexFinishStr - indexStartStr + 3) * sizeof(char)) : S21_NULL;
    char *rs = resultStr;

    for (s21_size_t i = indexStartStr; i <= indexFinishStr && length && trim_chars != S21_NULL; i++) {
        *rs = src[i];
        rs++;
        if (i == indexFinishStr) *rs = '\0';
    }

    return resultStr;
}
