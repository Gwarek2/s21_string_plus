#include "s21_string.h"
#include <stdarg.h>
#include "s21_string_helpers.h"
#include <stdio.h>
#include <math.h>

int main() {
    char buff1[100];
    char buff2[100];
    // s21_sprintf(buff1, "'%f/ is int, 5%%, the float is '%i/,  the char is '%c/, the string is '%s/", 1.234, 5, 's', "string");
    // sprintf(buff2, "'%i' is int, 5%%, the float is '%f',  the char is '%c', the string is '%s'", 5, 1.234, 's', "string");
    printf("%s\n", buff1);
    printf("%s\n", buff2);
    char buff3[100];
    dtoa(1.234, buff3, 3);
    // printf("%s\n", buff3);
    return 0;
}
