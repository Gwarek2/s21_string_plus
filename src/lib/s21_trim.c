#include <stdlib.h>
#include "s21_string.h"

int *del_space_trim(const char *src, s21_size_t length);

void *s21_trim(const char *src, const char *trim_chars) {
    void *resultStr = NULL;
    int status_trim_chars = trim_chars != NULL && *trim_chars;

    if (src != NULL) {
        s21_size_t length = s21_strlen(src);
        s21_size_t indexStartStr = 0;
        s21_size_t indexFinishStr = 0;

        for (s21_size_t i = 0; i < length && status_trim_chars && src; i++) {
            char *symbol = (char *)trim_chars;
            int status = 1;
            while (*symbol) {
                if (*symbol == src[i]) {
                    status = 0;
                }
                symbol++;
            }
            if (status) {
                indexStartStr = i;
                i = length;
            }
        }

        for (s21_size_t i = length - 1;
             i > 0 && !indexFinishStr && status_trim_chars && src; i--) {
            char *symbol = (char *)trim_chars;
            int status = 1;
            while (*symbol) {
                if (*symbol == src[i]) {
                    status = 0;
                }
                symbol++;
            }
            if (status) indexFinishStr = i;
        }

        if (!status_trim_chars) {
           int * index_str = del_space_trim(src, length);
           indexStartStr = index_str[0];
           indexFinishStr = index_str[1];
        }

        resultStr = malloc((indexFinishStr - indexStartStr + 3) * sizeof(char));

        if (resultStr) {
            char *rs = resultStr;

            for (s21_size_t i = indexStartStr;
                 i <= indexFinishStr && indexFinishStr && length; i++) {
                *rs = src[i];
                rs++;
            }
            *rs = '\0';
        }
    }

    return resultStr;
}

int *del_space_trim(const char *src, s21_size_t length) {

    int *result = malloc(2 * sizeof(int));
    result[0] = 1;
    result[1] = 2;

    for (s21_size_t i = 0; i < length; i++) {
        if (src[i] > 32) {
            result[0] = i;
            i = length;
        }
    }

    for (s21_size_t i = length - 1; i > 0; i--) {
        if (src[i] > 32) {
            result[1] = i;
            i = 1;
        }
    }

    return result;
}

