#ifndef _S21_CONVERTERS

#define _S21_CONVERTERS

#define DEC_VALUES "0123456789"
#define OCT_VALUES "01234567"
#define HEX_VALUES "0123456789abcdef"

#define FLAGS " +-"
#define SPECS "cdifsu%"

struct f_params {
    char flag;
    int width;
    int precision;
    char type[5];
};

enum bases {OCT = 8, DEC = 10, HEX = 16};


int read_format_params(struct f_params* params, const char *format);
int convert_arg(char *str, va_list args, struct f_params params);
int itoa(long long value, char* result, int base, char flag, int precision);
int dtoa(long double value, char *result, int precision);
int _read_f_char(const char *format, char *ch, const char *values);
int _read_f_spec(const char *format, char ch[5]);
int _read_f_num(const char *format, int *num);
void _add_padding(char *str, int len);
void _set_default_params(struct f_params *params);
char _base_values(int i, int base);
char* _reverse(char* start, char *end);

#endif
