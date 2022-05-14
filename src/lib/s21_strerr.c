#include "s21_string.h"
#include "s21_strerr.h"
#include "s21_sprintf.h"

char *s21_strerror(int errnum) {
    static char buff[100] = "";
    if (errnum >= 0 && errnum < ERROR_COUNT) {
        s21_strcpy(buff, ERROR_LIST[errnum]);
    } else {
        // char num[100];
        s21_sprintf(buff, "%s%d", UNKNOWN_ERROR, errnum);
        // s21_strcpy(buff, UNKNOWN_ERROR);
        // s21_strcpy(buff + s21_strlen(UNKNOWN_ERROR), num);
    }
    return buff;
}
