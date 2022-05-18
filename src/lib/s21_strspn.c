#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
    int len_str1 = s21_strlen(str1);
    int len_str2 = s21_strlen(str2);
    int num = 0;
    for (int i = 0, change = 1; i < len_str1 && change; i++) {
        change = 0;
        for ( int j = 0; j < len_str2; j++ ) {
            if (str1[i] == str2[j]) {
                num++;
                change = 1;
                j += len_str2;
            }
        }
    }
    return num;
}
