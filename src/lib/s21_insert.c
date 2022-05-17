#include <stdlib.h>
#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char* returned_string = S21_NULL;
    if (src != NULL && str != NULL) {
        s21_size_t src_len = s21_strlen(src);
        if (start_index <= src_len) {
            if (str == NULL) {
                returned_string = calloc(src_len + 1, sizeof(char));
                s21_strcpy( returned_string, src);
            } else {
                s21_size_t str_len = s21_strlen(str);
                returned_string = calloc(src_len + str_len + 1, sizeof(char));
                if (returned_string != S21_NULL) {
                    s21_strncpy(returned_string, src, start_index);
                    returned_string = returned_string + start_index;
                    src = src + start_index;
                    s21_strcpy(returned_string, str);
                    returned_string = returned_string + str_len;
                    s21_strcpy(returned_string, src);
                    returned_string = returned_string - str_len - start_index;
                }
            }
        }
    }

    return (void*) returned_string;
}
