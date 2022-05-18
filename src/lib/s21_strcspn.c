#include "../s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t length = 0;
    int accept = 1;
    s21_size_t counter;
    s21_size_t str1_length = s21_strlen(str1);
    s21_size_t str2_length = s21_strlen(str2);

    while (accept) {
        counter = 0;
        for (s21_size_t i = 0; i < str2_length; i++) {
            if (*str1 != *str2)
                counter++;
            str2++;
        }

        str2 -= str2_length;

        if (counter == str2_length && str1_length != 0 )
            length++;
        else
            accept = 0;

        str1_length--;

        if (str1_length == 0)
            accept = 0;

        str1++;
    }
    return length;
}
