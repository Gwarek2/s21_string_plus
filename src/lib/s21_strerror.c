#include "s21_string.h"
#include "s21_strerror.h"
#include "s21_sprintf.h"

char *s21_strerror(int errnum) {
    static char buff[100] = "";
    if (errnum >= 0 && errnum < ERROR_COUNT) {
        const char error_list[ERROR_COUNT][100] = ERROR_LIST;
        s21_strcpy(buff, error_list[errnum]);
    } else {
        s21_sprintf(buff, "%s%d", UNKNOWN_ERROR, errnum);
    }
    return buff;
}
