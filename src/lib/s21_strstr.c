#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
    char *i = (char *)haystack;
    char *j = (char *)needle;
    int flag = 1;
    char *result = '\0' == *j ? i : S21_NULL;

    while (*i != '\0' && !result) {
        if (*i == *j) {
            char *I = i;
            char *J = j;
            while (*J != '\0' && flag) {
                if (*I != *J) {
                    flag = 0;
                }
                J++;
                I++;
            }
            if (flag) {
                result = i;
            }
        }
        i++;
    }
    return result ? result : S21_NULL;
}
