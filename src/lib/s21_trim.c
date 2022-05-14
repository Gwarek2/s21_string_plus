#include <stdlib.h>
#include "s21_string.h"
void *s21_trim(const char *src, const char *trim_chars) {
    void *resultStr = NULL;

    if (src != NULL && trim_chars != NULL) {
        s21_size_t length = s21_strlen(src);
        s21_size_t indexStartStr = 0;
        s21_size_t indexFinishStr = 0;

        for (s21_size_t i = 0; i < length && trim_chars && src; i++) {
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

        for (s21_size_t i = length - 1; i > 0 && !indexFinishStr && trim_chars && src; i--) {
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


        resultStr = malloc((indexFinishStr - indexStartStr + 3) * sizeof(char));
        char *rs = resultStr;

        for (s21_size_t i = indexStartStr; i <= indexFinishStr && indexFinishStr && length ; i++) {
            *rs = src[i];
            rs++;
        }
        *rs = '\0';
    }

    return resultStr;
}

