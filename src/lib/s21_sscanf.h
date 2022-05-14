#ifndef S21_SSCANF
#define S21_SSCANF

#define SUPRESSOR '*'
#define NUM_ARG '$'
#define USE_ALLOC 'm'
#define LONG 'l'
#define LONG_DOUBLE 'L'
#define SHORT 'h'
#define SPECIFIERS "cdifsugGeExXonp%"

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

int sscanf(const char *str, const char *format, ...);
bool is_space(char ch);
void _initialize_state(struct scan_state *st);
void _reset_format(struct scan_state *st);
void _read_format(char **format, struct scan_state *st);
void _read_supressor(char **format, struct scan_state *st);
void _read_width_and_argnum(char **format, struct scan_state *st);
void _read_alloc_flag(char **format, struct scan_state *st);
void _read_len(char **format, struct state *st);
void _read_specifier(char **format, struct scan_state *st);
void _read_num(char *buffer, char **src);
#endif  // S21_SSCANF
