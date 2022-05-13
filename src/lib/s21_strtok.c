#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
    static char *pointer_to_next_token;  // stores pointer to the next "word"
                                         // after separator
    int null_flag = 0;
    if (!str)
        str = pointer_to_next_token;

    if (!str)
        null_flag = 1;

    // check if string only consists of separators
    if (str && s21_strspn(str, delim) == s21_strlen(str))
        null_flag = 1;

    char *return_string = str;  // since we change str for while loop, we create
                                // returning "checkpoint" so we can RETURN it
    int flag = 0;
    if (null_flag == 0) {
        while (*str != '\0' && flag != 1) {
            char *cdelim =
                (char *)delim;  // create a cdelim here
                                // so we can reset it
                                // after checking every character in str
            while (*cdelim != '\0' && flag != 1) {
                flag = 0;
                if (*str == *cdelim) {
                    *str = '\0';
                    char *tmp = str;  // creates temporary pointer to store data
                                      // for pointer_to_next_token
                    pointer_to_next_token = tmp + 1;  // points the pointer to the
                                                      // start of the next token
                    flag = 1;
                    // return return_string;
                } else {
                    cdelim++;
                }
            }
            if (flag == 0)
                str++;
        }
    } else {
        return_string = S21_NULL;
    }
    if (flag == 0)
        pointer_to_next_token = S21_NULL;  // setting pointer to null,
                                           // since if we reached this part
                                           // of the code it means that
                                           // we reached the end of the string
    return return_string;
}
