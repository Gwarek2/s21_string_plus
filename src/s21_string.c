#include <stdarg.h>
#include <stdlib.h>

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


void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    char *cdest = (char *) dest;
    char *csrc = (char *) src; 
    char *tmp = malloc(n * sizeof(char) + 1);
    for (s21_size_t i = 0; i < n; i++)
        tmp[i] = *csrc++; 
    for (s21_size_t i = 0; i < n; i++)
        *cdest++ = tmp[i];
    free(tmp);
    return dest;
}


void *s21_memset(void *str, int c, s21_size_t n) {
    char *cstr = (char*) str; 
    for (s21_size_t i = 0 ; i < n; i++)
        cstr[i] = c; 
    return str;
}


char *s21_strcat(char *dest, const char *src) {
    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
    return dest;
}


char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    while (*dest)
        dest++;
    for (s21_size_t i = 0; i < n; i++)
        *dest++ = src[i];
    *dest = '\0';
    return dest;
}


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
    while (str1[i] == str2[i] && (str1[i] != '\0' || str2[i] != '\0') && i < n)
        i++;
    return str1[i] - str2[i];
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


char *s21_strerror(int errnum) {
    static char buff[100];
    if (errnum > 0 && errnum <= ERROR_COUNT) {
        s21_strcpy(buff, error_descrs[errnum]);
    } else {
        char num[5];
        itoa(errnum, num, 10, 0, 0);
        s21_strcpy(buff, UNKNOWN_ERROR);
        s21_strcpy(buff + s21_strlen(UNKNOWN_ERROR), num);
    }
    return buff;
}


s21_size_t s21_strlen(const char *str) {
    s21_size_t i = 0;
    while (*str++) i++;
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


char *s21_strrchr(const char *str, int c) {
    char *result = S21_NULL;
    char *start = (char*) str;
    char *cursor = start + s21_strlen(str) - 1;
    while (*cursor != c && cursor != start)
        cursor--;

    if (*cursor == c)
        result = cursor;
    return result;
}


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


char *s21_strstr(const char *haystack, const char *needle) {
    char *result = (char*) haystack;
    if (*needle) {
        result = S21_NULL;
        int is_haystack_end = 0;
        while (*haystack && result == S21_NULL && !is_haystack_end) {
            char *cursor = (char*) needle;
            while (*cursor == *haystack && *cursor && !is_haystack_end) {
                haystack++;
                if (!*haystack) {
                    is_haystack_end = 1;
                    result = cursor;
                }
            }
            cursor++;
        }
    }
    return result;
}


char *s21_strtok(char *str, const char *delim) {
    static char *pointer_to_next_token;         /* stores pointer to the next "word" after separator */
    if (!str) str = pointer_to_next_token;      /* if str = \0, then we put the start of the rest of the string into it.  */

    if (!str) return S21_NULL;                      /* if start of the rest of the string = \0, that means that we are done with whole string and return S21_NULL */

    if ( s21_strspn(str,delim) == s21_strlen(str))    /* check if string only consists of separators  */
        return S21_NULL;

    char *return_string = str;                  /* since we change str for while loop, we create returning "checkpoint" so we can RETURN it */
    int flag = 0;
    while (*str != '\0' && flag != 1) {
        char* cdelim = (char*)delim;            /* create a cdelim here so we can reset it after checking every character in str */
        while (*cdelim != '\0' && flag != 1) {
            flag = 0;
            if (*str == *cdelim) {
                *str = '\0';
                char* tmp = str;                /* creates temporary pointer to store data for pointer_to_next_token */
                pointer_to_next_token = tmp+1;  /* points the pointer to the start of the next token */
                flag = 1; 
/*              return return_string; */
            } else {
                cdelim++;
            }
        }
        if (flag == 0) str++;
    }
    if (flag == 0) pointer_to_next_token = S21_NULL;               /* setting pointer to null, since if we reached this part of the code it means that we reached the end of the string */
    return return_string;
}


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
