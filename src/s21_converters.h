#ifndef _S21_CONVERTERS

#define _S21_CONVERTERS

#define MAX_INT_LEN 100
#define MAX_FLOAT_LEN 100

#define INT_CONVERT_DEC "0123456789"
#define INT_CONVERT_OCT "01234567"
#define INT_CONVERT_HEX "0123456789abcdef"

enum bases {OCT=8, DEC=10, HEX=16};

int itoa(int value, char* result, int base);
int dtoa(double value, char *result, int precision);

#endif