#ifndef _S21_CONVERTERS

#define _S21_CONVERTERS

#define MAX_INT_LEN 100
#define MAX_FLOAT_LEN 100

#define DEC_VALUES "0123456789"
#define OCT_VALUES "01234567"
#define HEX_VALUES "0123456789abcdef"

enum bases {OCT = 8, DEC = 10, HEX = 16};

int itoa(int value, char* result, int base);
int dtoa(double value, char *result, int precision);

#endif
