#include "s21_string.h"
#include "s21_errors.h"


void *s21_memchr(const void *str, int c, s21_size_t n) {
    void* result = S21_NULL;
    int found = 0;
    for (s21_size_t i = 0; i < n && !found; i++) {
        if (((char*) str)[i] == c) {
            result = (void*) (str + i);
            found = 1;
        }
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
    ((char*) dest)[n] = '\0';
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


// char *s21_strchr(const char *str, int c) {
//     // todo
// }


// int s21_strcmp(const char *str1, const char *str2) {
//     // todo
// }


// int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
//     // todo
// }


// char *s21_strcpy(char *dest, const char *src) {
//     // todo
// }


// char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
//     // todo
// }


// s21_size_t s21_strcspn(const char *str1, const char *str2) {
//     // todo
// }


char *s21_strerror(int errnum) {
    return (char*) error_descrs[errnum];
}


// s21_size_t s21_strlen(const char *str) {
//     // todo
// }


// char *s21_strpbrk(const char *str1, const char *str2) {
//     // todo
// }


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


// int s21_sprintf(char *str, const char *format, ...) {

// }
