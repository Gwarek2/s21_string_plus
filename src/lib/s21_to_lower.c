#include <stdlib.h>

#include "../s21_string.h"

void* s21_to_lower(const char* str) {
    char* returned_string = S21_NULL;
    if (str != S21_NULL) {
        long unsigned int length = s21_strlen(str);
        returned_string = calloc(length + 1, sizeof(char));
        if (returned_string != S21_NULL) {
            for (s21_size_t i = 0; i < length; i++) {
                if (str[i] >= 65 && str[i] <= 90)
                    returned_string[i] = str[i] + 32;
                else
                    returned_string[i] = str[i];
            }
            returned_string[length] = '\0';
        }
    }
    return (void*) returned_string;
}
