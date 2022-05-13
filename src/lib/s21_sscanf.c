#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>

#include "s21_string.h"
#include "s21_sscanf.h"

int sscanf(const char *str, const char *format, ...) {
    while (*format) {
        if (is_space(*format)) {
            format++;
            continue;
        }
        if (*format == '%') {
            // todo
            format++;
        } else {
            while (is_space(*str)) str++;
            if (*str != *format)
                break;
        }
    }
    return 0;
}

bool is_space(char ch) {
    return ch <= 32;
}
