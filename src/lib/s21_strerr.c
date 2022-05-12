#include "s21_string.h"
#include "s21_strerr.h"
#include "s21_sprintf.h"

char *s21_strerror(int errnum) {
    static char buff[100] = "";
    if (errnum >= 0 && errnum < ERROR_COUNT) {
        s21_strcpy(buff, ERROR_LIST[errnum]);
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
