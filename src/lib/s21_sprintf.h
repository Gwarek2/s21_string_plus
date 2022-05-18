#ifndef S21_SPRINTF

#define S21_SPRINTF

#include <stdarg.h>

#define NUM_TABLE_UPPER "0123456789ABCDEF"
#define NUM_TABLE_LOWER "0123456789abcdef"

#define FLAGS " +-0#"
#define SPECS "cdifsugGeExXonp%"


#define NULL_STR "(null)"

#ifdef __APPLE__
#define NULL_INT "0x0"
#else
#define NULL_INT "(nil)"
#endif

struct f_params {
    char flag;
    int minus;
    int sharp;
    int zero;
    int width;
    int precision;
    char type[5];
    int chars_printed;
    int default_precision;
};

int _read_format_params(struct f_params* params, const char *format, va_list args);
int _convert_arg(char *str, va_list args, struct f_params params);
int _itoa(long long unsigned value, char* result, int base, int neg, struct f_params params);
int _ftoa(long double value, char *result, struct f_params params);
int _fntoa(char *buffer, long double value, struct f_params params); 
int _fetoa(char *buffer, long double value, int exp, struct f_params params);
int _fgtoa(char *buffer, long double value, int exp, struct f_params params); 

int _int_to_str(char *buffer, va_list args, struct f_params params, int base);
int _uint_to_str(char *buffer, va_list args, struct f_params params, int base);
int _ptr_to_str(char *buffer, va_list args);
int _float_to_str(char *buffer,struct f_params params, va_list args);
int _chr_to_str(char *buffer, va_list args);
int _str_to_str(char *buffer, va_list args, struct f_params params);
void _get_printed_chars_num(va_list args, struct f_params params);
int _read_flag(const char *format, struct f_params *params, const char *values);
int _read_spec(const char *format, char ch[5]);
int _read_num(const char *format, int *num);
void _add_padding(char *str, int len, char ch);
int _calc_exponent(long double num);
void _set_default_params(struct f_params *params);
char* _reverse(char* start, char *end);

#endif  // S21_SPRINTF
