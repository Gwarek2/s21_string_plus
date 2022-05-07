#ifndef _S21_CONVERTERS

#define _S21_CONVERTERS

#define NUM_TABLE_UPPER "0123456789ABCDEF"
#define NUM_TABLE_LOWER "0123456789abcdef"

#define FLAGS " +-0#"
#define SPECS "cdifsugGeExXonp%"

struct f_params {
    char flag;
    int width;
    int precision;
    char type[5];
    int chars_printed;
};


int read_format_params(struct f_params* params, const char *format, va_list args);
int convert_arg(char *str, va_list args, struct f_params params);
int itoa(long long value, char* result, int base, struct f_params params);
int ftoa(long double value, char *result, struct f_params params);
int fntoa(char *buffer, long double value, int precision); 
int fetoa(char *buffer, long double value, int precision, int upper_case);
int fgtoa(char *buffer, long double value, int precision, int upper_case);
int s21_atoi(char *str);

void _int_to_str(char *buffer, va_list args, struct f_params params, int base);
void _uint_to_str(char *buffer, va_list args, struct f_params params, int base);
void _ptr_to_str(char *buffer, va_list args);
void _float_to_str(char *buffer,struct f_params params, va_list args);
void _get_printed_chars_num(va_list args, struct f_params params);
int _read_f_flag(const char *format, char *ch, const char *values);
int _read_f_spec(const char *format, char ch[5]);
int _read_f_num(const char *format, int *num);
void _add_padding(char *str, int len, char ch);
void _set_default_params(struct f_params *params);
char* _reverse(char* start, char *end);

#endif
