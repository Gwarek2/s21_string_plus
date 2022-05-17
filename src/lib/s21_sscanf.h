#ifndef S21_SSCANF
#define S21_SSCANF

#define SUPRESSOR '*'
#define NUM_ARG '$'
#define USE_ALLOC 'm'
#define SPECIFIERS "cdifsugGeExXonp%"
#define SCANSET_START '['
#define SCANSET_END ']'

enum length {
    SHORT=1,
    COMMON=2,
    LONG=3,
    LLONG=4,
};

enum number_system {
    OCT=8,
    DEC=10,
    HEX=16,
};

struct scan_state {
    int bytes_scanned;
    int correct_writes;
    bool num_args_flag;
    bool ordered_args_flag;
    bool failure;
    struct {
        bool supress;
        int arg_num;
        int width;
        bool use_alloc;
        int length;
        char specifier;
        char scanset[500];
    } format;
};

struct uint_utils {
    int base;
    bool (*num_check)(char);
    bool (*prefix_check)(const char*, int);
    int prefix_len;
};

int sscanf(const char *str, const char *format, ...);
bool is_space(char ch);
bool is_dec(char ch);
bool is_oct(char ch);
bool is_hex(char ch);
bool _is_signed_num_starts(const char *str, int width);
bool _is_float_starts_with_point(const char *str, int width);
bool _is_scientific_notation_starts(const char *str);
bool _is_oct_prefix(const char *str, int width);
bool _is_hex_prefix(const char *str, int width);
void _ignore_space_chars(const char **str);
void _initialize_state(struct scan_state *st);
void _reset_format(struct scan_state *st);
void _ignore_space_chars(const char **str);
void _read_format(const char **format, struct scan_state *st);
void _read_supressor(const char **format, struct scan_state *st);
void _read_width_and_argnum(const char **format, struct scan_state *st);
void _read_alloc_flag(const char **format, struct scan_state *st);
void _read_len(const char **format, struct scan_state *st);
void _read_specifier(const char **format, struct scan_state *st);
void _read_scanset(const char **format, struct scan_state *st);
void _read_number(char *buffer, const char **src, int width, bool (*num_check)(char));

void _parse_arg(va_list args, const char **str, struct scan_state *st);
void* _parse_by_order(va_list args);
void* _parse_by_index(va_list args, int index);
void _parse_int(const char **str, void *ptr, struct scan_state *st);
void _parse_uint(const char **str, void *ptr, struct scan_state *st, struct uint_utils* utils);
void _parse_float(const char **str, void *ptr, struct scan_state *st);
void _parse_char(const char **str, void *ptr, struct scan_state *st);
void _parse_str(const char **str, void *ptr, struct scan_state *st);
void _write_str_to_static_buffer(char *buffer, const char **str, struct scan_state *st);
void _write_str_to_heap_buffer(char **buffer, const char **str, struct scan_state *st);
#endif  // S21_SSCANF
