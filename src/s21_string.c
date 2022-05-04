#include <stdarg.h>

#include "s21_string.h"
#include "s21_errors.h"
#include "s21_string_helpers.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
    void* result = S21_NULL;
    for (s21_size_t i = 0; i < n && result == S21_NULL; i++) {
        if (((char*) str)[i] == c)
            result = (void*) str + i;
    }
    return result;
}


int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    s21_size_t i = 0;
    while (i < n && ((char*) str1)[i] == ((char*) str2)[i])
        i++;
    return ((char*) str1)[i] - ((char*) str2)[i];
}


void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    for (s21_size_t i = 0; i < n; i++)
        ((char*) dest)[i] = ((const char*) src)[i];
    return dest;
}


// void *s21_memmove(void *dest, const void *src, s21_size_t n) {
//     // todo
// }


// void *s21_memset(void *str, int c, s21_size_t n) {
//     // todo
// }


// char *s21_strcat(char *dest, const char *src) {
//     // todo
// }


// char *s21_strncat(char *dest, const char *src, s21_size_t n) {
//     // todo
// }


char *s21_strchr(const char *str, int c) {
    char *result = S21_NULL;
    while (*str && *str != c) str++;
    if (*str == c)
        result = (char*) str;
    return result;
}


int s21_strcmp(const char *str1, const char *str2) {
    s21_size_t i = 0;
    while (str1[i] == str2[i] && (str1[i] != '\0' || str2[i] != '\0'))
        i++;
    return str1[i] - str2[i];
}


int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    s21_size_t i = 0;
    while (str1[i] == str2[i] && (str1[i] != '\0' || str2[i] != '\0') && i < n) {
        i++;
    }
    return(str1[i] - str2[i]);
}


char *s21_strcpy(char *dest, const char *src) {
    char* start = dest;
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
    return start;
}


char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    char* start = dest;
    for (s21_size_t i = 0; i < n ; i++)
        dest[i] = src[i];
    return start;
}


// s21_size_t s21_strcspn(const char *str1, const char *str2) {
//     // todo
// }


char *s21_strerror(int errnum) {
    static char buff[100];
    if (errnum > 0 && errnum <= ERROR_COUNT) {
        s21_memcpy((void*) buff, error_descrs[errnum], 100);
    } else {
        char num[5];
        itoa(errnum, num, 10, 0, 0);
        s21_memcpy((void*) buff, UNKNOWN_ERROR, 100);
        s21_memcpy((void*) (buff + s21_strlen(UNKNOWN_ERROR)), num, 5);
    }
    return buff;
}


s21_size_t s21_strlen(const char *str) {
    s21_size_t i = 0;
    char *cursor = (char*) str;
    while (*cursor++) i++;
    return i;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    char *result = S21_NULL;
    while (*str1 && result == S21_NULL) {
        char *cursor = (char*) str2;
        while (*cursor) {
            if (*cursor++ == *str1)
                result = (char*) str1;
        }
        str1++;
    }
    return result;
}


// char *s21_strrchr(const char *str, int c) {
//     // todo
// }


// s21_size_t s21_strspn(const char *str1, const char *str2) {
//     // todo
// }


// char *s21_strstr(const char *haystack, const char *needle) {

// }


// char *s21_strtok(char *str, const char *delim) {

// }


int s21_sprintf(char *str, const char *format, ...) {
    char *start = str;
    va_list vars;

    va_start(vars, format);
    while (*format) {
        if (*format == '%') {
            format++;
            struct f_params params;
            format += read_format_params(&params, (char*) format);
            str += convert_arg(str, vars, params);
        } else {
            *str++ = *format++;
        }
    }
    *str = '\0';
    va_end(vars);

    return str - start;
}
