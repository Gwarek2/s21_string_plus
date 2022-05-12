#include <stdarg.h>
#include <stdlib.h>

#include "s21_string.h"
#include "s21_errors.h"
#include "s21_sprintf_helpers.h"


void *s21_memchr(const void *str, int c, s21_size_t n) {
    void *result = S21_NULL;
    unsigned char *cursor = (unsigned char*) str;
    for (s21_size_t i = 0; i < n && result == S21_NULL; i++) {
        if (cursor[i] == c)
            result = (void*) cursor + i;
    }
    return result;
}


int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    s21_size_t i = 0;
    unsigned char *cursor1 = (unsigned char*) str1;
    unsigned char *cursor2 = (unsigned char*) str2;
    while (i < n && cursor1[i] == cursor2[i])
        i++;
    return cursor1[i] - cursor2[i];
}


void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    unsigned char *cursor_dest = (unsigned char*) dest;
    unsigned char *cursor_src = (unsigned char*) src;
    for (s21_size_t i = 0; i < n; i++)
        cursor_dest[i] = cursor_src[i];
    return dest;
}


void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    unsigned char *cdest = (unsigned char*) dest;
    unsigned char *csrc = (unsigned char*) src;
    unsigned char *tmp = calloc(n + 1, sizeof(unsigned char));
    for (s21_size_t i = 0; i < n; i++)
        tmp[i] = *csrc++;
    for (s21_size_t i = 0; i < n; i++)
        *cdest++ = tmp[i];
    free(tmp);
    return dest;
}


void *s21_memset(void *str, int c, s21_size_t n) {
    unsigned char *cstr = (unsigned char*) str;
    for (s21_size_t i = 0 ; i < n; i++)
        cstr[i] = c;
    return str;
}


char *s21_strcat(char *dest, const char *src) {
    char *start = dest;
    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
    return start;
}


char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    char *start = dest;
    while (*dest)
        dest++;
    for (s21_size_t i = 0; i < n; i++)
        *dest++ = src[i];
    *dest = '\0';
    return start;
}


char *s21_strchr(const char *str, int c) {
    char *result = S21_NULL;
    while (*str && *str != c) str++;
    if (*str == c)
        result = (char*) str;
    return result;
}


int s21_strcmp(const char *str1, const char *str2) {
    int result = 0;
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    if (*str1 != *str2)
        result = *str1 > *str2 ? 1 : -1;
    return result;
}


int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    s21_size_t i = 0;
    int result = 0;
    while (*str1 && *str2 && *str1 == *str2 && i < n) {
        str1++;
        str2++;
        i++;
    }
    if (*str1 != *str2)
        result = *str1 > *str2 ? 1 : -1;
    return result;
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
    if (errnum >= 0 && errnum < ERROR_COUNT) {
        s21_strcpy(buff, error_descrs[errnum]);
    } else {
        char num[5];
        struct f_params params;
        _set_default_params(&params);
        int arg = errnum < 0 ? -errnum : errnum;
        itoa(arg, num, 10, errnum < 0, params);
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

char *s21_strtok(char *str, const char *delim) {
    static char *pointer_to_next_token; /* stores pointer to the next "word"
                                           after separator */
    int null_flag = 0;
    if (!str) {
        str = pointer_to_next_token;
    }
    if (!str) {
        null_flag = 1;
    }
    if (str &&
        s21_strspn(str, delim) ==
            s21_strlen(str)) { /* check if string only consists of separators */
        null_flag = 1;
    }
    char *return_string = str; /* since we change str for while loop, we create
                                  returning "checkpoint" so we can RETURN it */
    int flag = 0;
    if (null_flag == 0) {
        while (*str != '\0' && flag != 1) {
            char *cdelim =
                (char *)delim; /* create a cdelim here so we can reset it
                       after checking every character in str */
            while (*cdelim != '\0' && flag != 1) {
                flag = 0;
                if (*str == *cdelim) {
                    *str = '\0';
                    char *tmp = str; /* creates temporary pointer to store data
                                        for pointer_to_next_token */
                    pointer_to_next_token =
                        tmp + 1; /* points the pointer to the
                                    start of the next token */
                    flag = 1;
                    /*              return return_string; */
                } else {
                    cdelim++;
                }
            }
            if (flag == 0)
                str++;
        }
    } else {
        return_string = S21_NULL;
    }
    if (flag == 0)
        pointer_to_next_token =
            S21_NULL; /* setting pointer to null, since if we reached this part
                         of the code it means that we reached the end of the
                         string */
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
            format += read_format_params(&params, (char*) format, vars);
            params.chars_printed = str - start;
            str += convert_arg(str, vars, params);
        } else {
            *str++ = *format++;
        }
    }
    *str = '\0';
    va_end(vars);

    return str - start;
}

/** C# string class functions **/
void *s21_to_upper(const char *str) {
    char* returned_string = S21_NULL;
    if (str != S21_NULL) {
        long unsigned int length = s21_strlen(str);
        returned_string = calloc(length + 1, sizeof(char));
        if (returned_string != S21_NULL) {
            for (s21_size_t i = 0; i < length; i++) {
                if (str[i] >= 97 && str[i] <= 122)
                    returned_string[i] = str[i] - 32;
                else
                    returned_string[i] = str[i];
            }
            returned_string[length] = '\0';
        }
    }
    return (void*) returned_string;
}

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

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char* returned_string = S21_NULL;
    if (src != NULL && str != NULL) {
        s21_size_t src_len = s21_strlen(src);
        s21_size_t str_len = s21_strlen(str);
        if (start_index <= src_len) {
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

    return (void*) returned_string;
}


void *s21_trim(const char *src, const char *trim_chars) {
    s21_size_t length = src != S21_NULL ? s21_strlen(src) : 0;
    s21_size_t indexStartStr = 0;
    s21_size_t indexFinishStr = 0;

    for (s21_size_t i = 0; i < length && trim_chars != S21_NULL && src != S21_NULL; i++) {
        char *symbol = (char*) trim_chars;
        int status = 1;
        while (*symbol) {
            if (*symbol == src[i])
                status = 0;
            symbol++;
        }
        if (status) {
            indexStartStr = i;
            i = length;
        }
    }

    for (s21_size_t i = length - 1; i > 0 && !indexFinishStr && trim_chars != S21_NULL && src != S21_NULL; i--) {
        char *symbol = (char*) trim_chars;
        int status = 1;
        while (*symbol) {
            if (*symbol == src[i])
                status = 0;
            symbol++;
        }
        if (status) indexFinishStr = i;
    }

    char *resultStr = src && trim_chars ? malloc((indexFinishStr - indexStartStr + 3) * sizeof(char)) : S21_NULL;
    char *rs = resultStr;

    for (s21_size_t i = indexStartStr; i <= indexFinishStr && length && trim_chars != S21_NULL; i++) {
        *rs = src[i];
        rs++;
        if (i == indexFinishStr) *rs = '\0';
    }

    return resultStr;
}
