/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "tests/headers.check" instead.
 */

#include <check.h>

#include <stdio.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_string.h"
START_TEST(test_insert_zero_index)
{
    char* str1 = "123456\0";
    char* str2 = "AB\0";
    s21_size_t index = 0;
    char* result_insert = s21_insert(str1, str2, index);
    ck_assert_str_eq(result_insert, "AB123456\0");
    free(result_insert);
}
END_TEST

START_TEST(test_insert_last_index)
{
    char* str1 = "123456\0";
    char* str2 = "AB\0";
    s21_size_t index = 6;
    char* result_insert = s21_insert(str1, str2, index);
    ck_assert_str_eq(result_insert, "123456AB\0");
    free(result_insert);
}
END_TEST

START_TEST(test_insert_middle_index)
{
    char* str1 = "123456\0";
    char* str2 = "AB\0";
    s21_size_t index = 3;
    char* result_insert = s21_insert(str1, str2, index);
    ck_assert_str_eq(result_insert, "123AB456\0");
    free(result_insert);
}
END_TEST

START_TEST(test_insert_larger_index)
{
    char* str1 = "123456\0";
    char* str2 = "AB\0";
    s21_size_t index = 11;
    char* result_insert = s21_insert(str1, str2, index);
    ck_assert_ptr_eq(result_insert, NULL);
}
END_TEST

START_TEST(test_insert_neg_index)
{
    char* str1 = "123456\0";
    char* str2 = "AB\0";
    s21_size_t index = -1;
    char* result_insert = s21_insert(str1, str2, index);
    ck_assert_ptr_eq(result_insert, NULL);
}
END_TEST

START_TEST(test_insert_null_strings)
{
    char *str1 = NULL;
    char *str2 = NULL;
    s21_size_t index = 0;
    char* result_insert = s21_insert(str1, str2, index);
    ck_assert_ptr_eq(result_insert, NULL);
}
END_TEST

START_TEST(test_insert_null_src)
{
    char *str1 = NULL;
    char *str2 = "string";
    s21_size_t index = 0;
    char* result_insert = s21_insert(str1, str2, index);
    ck_assert_ptr_eq(result_insert, NULL);
}
END_TEST

START_TEST(test_insert_null_dest)
{
    char *str1 = "string";
    char *str2 = NULL;
    s21_size_t index = 1;
    char* result_insert = s21_insert(str1, str2, index);
    ck_assert_ptr_eq(result_insert, NULL);
}
END_TEST

START_TEST(test_s21_memchr_normal)
{
    void *str = (void*) "Hello world";
    ck_assert_str_eq(s21_memchr(str, ' ', 11), memchr(str, ' ', 11));
}
END_TEST

START_TEST(test_s21_memchr_zero_len)
{
    void *str = (void*) "Hello world";
    ck_assert_ptr_eq(s21_memchr(str, 111, 0), memchr(str, 111, 0));
}
END_TEST

START_TEST(test_s21_memchr_min_len)
{
    void *str = (void*) "Hello world";
    ck_assert_str_eq(s21_memchr(str, 'H', 1), memchr(str, 'H', 1));
}
END_TEST

START_TEST(test_s21_memchr_no_result)
{
    void *str = (void*) "Hello world";
    ck_assert_ptr_eq(s21_memchr(str, 107, 11), memchr(str, 107, 11));
}
END_TEST

START_TEST(test_s21_memchr_null_char_in_the_middle)
{
    void *str = (void*) "Hello\0world";
    ck_assert_ptr_eq(s21_memchr(str, 12, 11), memchr(str, 12, 11));
}
END_TEST

START_TEST(test_s21_memchr_empty_string)
{
    void *str = (void*) "";
    ck_assert_ptr_eq(s21_memchr(str, 12, 1), memchr(str, 12, 1));
}
END_TEST

START_TEST(test_s21_memcmp_eq_str)
{
    void *str1 = (void*) "Hello world";
    void *str2 = (void*) "Hello world";
    ck_assert_int_eq(s21_memcmp(str1, str2, 11), memcmp(str1, str2, 11));
}
END_TEST

START_TEST(test_s21_memcmp_neq_str)
{
    void *str1 = (void*) "Hello world";
    void *str2 = (void*) "HELLO WORLD";
    ck_assert_int_eq(s21_memcmp(str1, str2, 11), memcmp(str1, str2, 11));
}
END_TEST

START_TEST(test_s21_memcmp_neq_str_diff_len)
{
    void *str1 = (void*) "daddy";
    void *str2 = (void*) "dim";
    ck_assert_int_eq(s21_memcmp(str1, str2, 3), s21_memcmp(str1, str2, 3));
}
END_TEST

START_TEST(test_s21_memcmp_empty_str)
{
    void *str1 = (void*) "\0";
    void *str2 = (void*) "\0";
    ck_assert_int_eq(s21_memcmp(str1, str2, 1), memcmp(str1, str2, 1));
}
END_TEST

START_TEST(test_s21_memcpy_full)
{
    void *template = (void*) "Hello world";
    char buff1[50]; char buff2[50];
    void *str1 = (void*) buff1;
    void *str2 = (void*) buff2;
    ck_assert_mem_eq(memcpy(str1, template, 12), s21_memcpy(str2, template, 12), 12);
}
END_TEST

START_TEST(test_s21_memcpy_partial)
{
    void *template = (void*) "Text to copy";
    char buff1[50]; char buff2[50];
    void *str1 = (void*) buff1;
    void *str2 = (void*) buff2;
    ck_assert_mem_eq(memcpy(str1, template, 5), s21_memcpy(str2, template, 5), 5);
}
END_TEST

START_TEST(test_s21_memcpy_empty)
{
    void *template = (void*) "\0";
    char buff1[50]; char buff2[50];
    void *str1 = (void*) buff1;
    void *str2 = (void*) buff2;
    ck_assert_mem_eq(memcpy(str1, template, 1), s21_memcpy(str2, template, 1), 1);
}
END_TEST

START_TEST(s21_memmove_test_different_strings)
{
    char str1[] = "Hi World";
    char str2[] = "bye 12345";
    char str3[] = "Hi World";
    char str4[] = "bye 12345";
    ck_assert_mem_eq(s21_memmove(str1, str2, 3), memmove(str3, str4, 3), 3);
}
END_TEST

START_TEST(s21_memmove_test_same_string_overlap)
{
    char str2[] = "123456789";
    char str1[] = "123456789";
    ck_assert_mem_eq(s21_memmove(str1, str1 + 2, 4), memmove(str2, str2 + 2, 4), 4);
}
END_TEST

START_TEST(s21_memmove_test_same_string_non_overlap)
{
    char str2[] = "123456789";
    char str1[] = "123456789";
    ck_assert_mem_eq(s21_memmove(str1 + 1, str1, 4), memmove(str2 + 1, str2, 4), 4);
}
END_TEST

START_TEST(s21_memmove_test_null)
{
    char str1[] = "\0"; 
    char str2[] = "123456789";
    ck_assert_mem_eq(s21_memmove(str2, str1, 1), memmove(str2, str1, 1), 1);
}
END_TEST

START_TEST(s21_memset_test_normal)
{
    char str[] = "123snake";
    char str1[] = "123snake";
    char c = 's';
    ck_assert_mem_eq(s21_memset(str, c, 3), memset(str1, c, 3), 3);
}
END_TEST

START_TEST(s21_memset_test_null)
{
    char str[] = "1234";
    char str1[] = "1234";
    char c = '\0';
    ck_assert_mem_eq(s21_memset(str, c, 3), memset(str1, c, 3), 3);
}
END_TEST

START_TEST(s21_memset_test_newline)
{
    char str[] = "1234";
    char str1[] = "1234";
    char c = '\n';
    ck_assert_mem_eq(s21_memset(str, c, 3), memset(str1, c, 3), 3);
}
END_TEST

START_TEST(s21_memset_fill_empty_array)
{
    char str[10];
    char str1[10];
    char c = 'd';
    ck_assert_mem_eq(s21_memset(str, c, 10), memset(str1, c, 10), 10);
#include "../s21_string.h"
}
END_TEST

START_TEST(test_s21_sprintf_strings)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|5%%|, |%c|, |%20.5s|, |%40.5s|",
                         'n', "helloHELLO", "stringSTRINGstringSTRING");
    int c2 = sprintf(buff2, "|5%%|, |%c|, |%20.5s|, |%40.5s|",
                     'n', "helloHELLO", "stringSTRINGstringSTRING");
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_null_char)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "string) |%---c|\n", '\0');
    int c2 = sprintf(buff2, "string) |%---c|\n", '\0');
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
// #test test_s21_sprintf_strings_null
//     char buff1[100000];
//     char buff2[100000];
//     char *str1 = NULL;
//     char *str2 = NULL;
//     int c1 = s21_sprintf(buff1, "null string is - |%s|", str1);
//     int c2 = sprintf(buff2, "null string is - |%s|", str2);
//     ck_assert_str_eq(buff1, buff2);
//     ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_wide_strings)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|5%%|, |%10lc|, |%-10.10ls|", L'n', L"hello");
    int c2 = sprintf(buff2, "|5%%|, |%10lc|, |%-10.10ls|", L'n', L"hello");
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_float_values)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%+*.*f|, |%+-10.2f|, |%.0f|, |%#6.2f|", -23, -20, 0.001, 999.999, -320.3, 0.199);
    int c2 = sprintf(buff2, "|%+*.*f|, |%+-10.2f|, |%.0f|, |%#6.2f|", -23, -20, 0.001, 999.999, -320.3, 0.199);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
// #test test_s21_sprintf_float_max
//     char buff1[100000];
//     char buff2[100000];
//     int c1 = s21_sprintf(buff1, "|%+.7f|, |% 10.2f|, |%012.1f|, |%#.0f|", FLT_MAX, 999.999, -125.56, 76456.9);
//     int c2 = sprintf(buff2, "|%+.7f|, |% 10.2f|, |%012.1f|, |%#.0f|", FLT_MAX, 999.999, -125.56, 76456.9);
//     ck_assert_str_eq(buff1, buff2);
//     ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_nan)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "%-4f %10.3E % 5G", NAN, NAN, NAN);
    int c2 = sprintf(buff2, "%-4f %10.3E % 5G", NAN, NAN, NAN);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_inf)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "%+f %-4f % 4f", INFINITY, -INFINITY, INFINITY);
    int c2 = sprintf(buff2, "%+f %-4f % 4f", INFINITY, -INFINITY, INFINITY);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_int_values)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%2.d|, |%010d|, |%+4i|", 0, -1234, 4219);
    int c2 = sprintf(buff2, "|%2.d|, |%010d|, |%+4i|", 0, -1234, 4219);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(s21_sprintf_int_max_values)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%hu|, |%-10.7d|, |%010ld|, |%+4lli|", SHRT_MAX, INT_MAX, LONG_MAX, LLONG_MAX);
    int c2 = sprintf(buff2, "|%hu|, |%-10.7d|, |%010ld|, |%+4lli|", SHRT_MAX, INT_MAX, LONG_MAX, LLONG_MAX);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(s21_sprintf_int_min_values)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%hu|, |%-10.7d|, |%010ld|, |%+4lli|", SHRT_MIN, INT_MIN, LONG_MIN, LLONG_MIN);
    int c2 = sprintf(buff2, "|%hu|, |%-10.7d|, |%010ld|, |%+4lli|", SHRT_MIN, INT_MIN, LONG_MIN, LLONG_MIN);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_uint_max_values)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%hu|, |%-10.7u|, |%010lu|, |%4llu|", USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX);
    int c2 = sprintf(buff2, "|%hu|, |%-10.7u|, |%010lu|, |%4llu|", USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_oct_values)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%-10.7o|, |%010o|, |%*.*o|", 9512, 1234, 0, 0, 0);
    int c2 = sprintf(buff2, "|%-10.7o|, |%010o|, |%*.*o|", 9512, 1234, 0, 0, 0);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_uint_oct_max_values)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%ho|, |%-10.7o|, |%010lo|, |%4llo|", USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX);
    int c2 = sprintf(buff2, "|%ho|, |%-10.7o|, |%010lo|, |%4llo|", USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_hex_values)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%-10.7x|, |%010X|, |%0*.*x|", 9512, 1234, 20, -20, 4219);
    int c2 = sprintf(buff2, "|%-10.7x|, |%010X|, |%0*.*x|", 9512, 1234, 20, -20, 4219);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_uint_hex_max_values)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%hx|, |%-10.7x|, |%010lx|, |%4llx|", USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX);
    int c2 = sprintf(buff2, "|%hx|, |%-10.7x|, |%010lx|, |%4llx|", USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_ptr)
{
    char buff1[100000];
    char buff2[100000];
    int p1, p2, p3;
    int c1 = s21_sprintf(buff1, "|%-20p|, |%p|, |%15p|", &p1, &p2, &p3);
    int c2 = sprintf(buff2, "|%-20p|, |%p|, |%15p|", &p1, &p2, &p3);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_ptr_null)
{
    char buff1[100000];
    char buff2[100000];
    void *p1 = NULL;
    int c1 = s21_sprintf(buff1, "|%p|", p1);
    int c2 = sprintf(buff2, "|%p|", p1);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_chars_printed)
{
    char buff1[100000];
    char buff2[100000];
    int p1, p2, p3, p4, p5, p6;
    int c1 = s21_sprintf(buff1, "|%-20d|, |%n| |%s|, |%n| |%.2f||%n|",
                         1234, &p1, "string", &p2, 234.564, &p3);
    int c2 = sprintf(buff2, "|%-20d|, |%n| |%s|, |%n| |%.2f||%n|",
                     1234, &p4, "string", &p5, 234.564, &p6);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(p1, p4);
    ck_assert_int_eq(p2, p5);
    ck_assert_int_eq(p3, p6);
}
END_TEST

START_TEST(test_s21_sprintf_width_and_precision_from_arg)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%*.*d|, |%0*i|, |%*s|", 20, 10, 12345, 10, 5782, 15, "string");
    int c2 = sprintf(buff2, "|%*.*d|, |%0*i|, |%*s|", 20, 10, 12345, 10, 5782, 15, "string");
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_width_from_arg_neg)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%0*d|", -20, 12345);
    int c2 = sprintf(buff2, "|%0*d|", -20, 12345);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_float_exp_format)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%#.0E|, |%-10.2e|, |%+.1E|, |%e|", 299.99, 0.9999, -9.454, 999.99);
    int c2 = sprintf(buff2, "|%#.0E|, |%-10.2e|, |%+.1E|, |%e|", 299.99, 0.9999, -9.454, 999.99);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_float_exp_format_1)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%#.0E|, |%.10e|, |%+.1E|, |%e|", 299.0, 3.0, -9.0, 332.34);
    int c2 = sprintf(buff2, "|%#.0E|, |%.10e|, |%+.1E|, |%e|", 299.0, 3.0, -9.0, 332.34);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_float_g_format)
{
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%#.1G|, |%-10g|, |%#.0g|, |%#-*.*g|", 236.78, 0.001329, 999.99, 10, 10, 0.0000001);
    int c2 = sprintf(buff2, "|%#.1G|, |%-10g|, |%#.0g|, |%#-*.*g|", 236.78, 0.001329, 999.99, 10, 10, 0.0000001);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_strcat_s1_sum_s2_normal)
{
    char str1[100] = "01234";
    char str2[100] = "56789";
    char str3[100] = "01234";
    char str4[100] = "56789";
    ck_assert_pstr_eq(s21_strcat(str1, str2), strcat(str3, str4));
}
END_TEST

START_TEST(test_s21_strcat_to_empty)
{
    char str1[100] = "\0";
    char str2[100] = "string";
    char str3[100] = "\0";
    char str4[100] = "string";
    ck_assert_pstr_eq(s21_strcat(str1, str2), s21_strcat(str3, str4));
}
END_TEST

START_TEST(test_s21_strcat_empty)
{
    char str1[100] = "string";
    char str2[100] = "\0";
    char str3[100] = "string";
    char str4[100] = "\0";
    ck_assert_pstr_eq(s21_strcat(str1, str2), s21_strcat(str3, str4));
}
END_TEST

START_TEST(test_s21_strcat_empty_to_empty)
{
    char str1[100] = "\0";
    char str2[100] = "\0";
    char str3[100] = "\0";
    char str4[100] = "\0";
    ck_assert_pstr_eq(s21_strcat(str1, str2), s21_strcat(str3, str4));
}
END_TEST

START_TEST(test_s21_strcat_null_in_the_middle)
{
    char str1[100] = "str\0ing";
    char str2[100] = "ike\0ld";
    char str3[100] = "str\0ing";
    char str4[100] = "ike\0ld";
    ck_assert_pstr_eq(s21_strcat(str1, str2), s21_strcat(str3, str4));
}
END_TEST

START_TEST(test_s21_strchr_normal)
{
    char *str = (void *)"Hello world";
    char *str2 = "o";
    ck_assert_str_eq(s21_strchr(str, *str2), strchr(str, *str2));
}
END_TEST

START_TEST(test_s21_strchr_no_result)
{
    char *str = (void *)"Hello world";
    char *str2 = "f";
    ck_assert_ptr_eq(s21_strchr(str, *str2), strchr(str, *str2));
}
END_TEST

START_TEST(test_s21_strchr_empty_str)
{
    char *str = (void *)"Hello world";
    char *str2 = "";
    ck_assert_str_eq(s21_strchr(str, *str2), strchr(str, *str2));
}
END_TEST

START_TEST(test_s21_strcmp_1_equal)
{
    char str1[100] = "abc";
    char str2[100] = "abc";
    ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(test_s21_strcmp_2_non_equal)
{
    char str1[100] = "abc";
    char str2[100] = "abd";
    ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(test_s21_strcmp_1_littel)
{
    char str1[100] = "abd";
    char str2[100] = "abc";
    ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(test_s21_strcpy_not_empty)
{
    char line1[20] = "Hello world\0";
    char line2[20] = "Hi\0";
    char* dest = line1;
    const char* src = line2;
    char line3[20] = "Hello world\0";
    char line4[20] = "Hi\0";
    char* dest2 = line3;
    const char* src2 = line4;
    ck_assert_str_eq(s21_strcpy(dest, src), strcpy(dest2, src2));
}
END_TEST

START_TEST(test_s21_strcpy_empty)
{
    char line1[20] = "\0";
    char line2[20] = "\0";
    char* dest = line1;
    const char* src = line2;
    char line3[20] = "\0";
    char line4[20] = "\0";
    char* dest2 = line3;
    const char* src2 = line4;
    ck_assert_str_eq(s21_strcpy(dest, src), strcpy(dest2, src2));
}
END_TEST

START_TEST(test_s21_strcspn_equal_lines)
{
    char* dest = "hello\0";
    const char* src = "hello\0";
    char* dest2 = "hello\0";
    const char* src2 = "hello\0";
    ck_assert_int_eq(s21_strcspn(dest, src), strcspn(dest2, src2));
}
END_TEST

START_TEST(test_s21_strcspn_dif_start)
{
    char* dest = "hello\0";
    const char* src = "bello\0";
    char* dest2 = "hello\0";
    const char* src2 = "bello\0";
    ck_assert_int_eq(s21_strcspn(dest, src), strcspn(dest2, src2));
}
END_TEST

START_TEST(test_s21_strcspn_dif_end)
{
    char* dest = "hello, friend\0";
    const char* src = "hello\0";
    char* dest2 = "hello, friend\0";
    const char* src2 = "hello\0";
    ck_assert_int_eq(s21_strcspn(dest, src), strcspn(dest2, src2));
}
END_TEST

START_TEST(test_s21_strcspn_empty_lines)
{
    char* dest = "\0";
    const char* src = "\0";
    char* dest2 = "\0";
    const char* src2 = "\0";
    ck_assert_int_eq(s21_strcspn(dest, src), strcspn(dest2, src2));
}
END_TEST

START_TEST(test_s21_strcspn_first_line_is_empty)
{
    char* dest = "\0";
    const char* src = "hello\0";
    char* dest2 = "\0";
    const char* src2 = "hello\0";
    ck_assert_int_eq(s21_strcspn(dest, src), strcspn(dest2, src2));
}
END_TEST

START_TEST(test_s21_strcspn_second_line_is_empty)
{
    char* dest = "hello\0";
    const char* src = "\0";
    char* dest2 = "hello\0";
    const char* src2 = "\0";
    ck_assert_int_eq(s21_strcspn(dest, src), strcspn(dest2, src2));
}
END_TEST

START_TEST(test_s21_strerror_true_codes)
{
    for (int i = 0; i <= 140; i++)
        ck_assert_str_eq(strerror(i), s21_strerror(i));
}
END_TEST

START_TEST(test_s21_strerror_wrong_code)
{
    ck_assert_str_eq(strerror(-1), s21_strerror(-1));
}
END_TEST

START_TEST(test_s21_strlen_normal)
{
    char *str = (void *)"Hello world";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strlen_no_result)
{
    void *str = (void *)"";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strlen_empty_str)
{
    void *str = (void *)"\n\0";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strncat_normal)
{
    char str1[100] = "01234";
    char str2[100] = "56789";
    char str3[100] = "01234";
    char str4[100] = "56789";
    ck_assert_str_eq(s21_strncat(str1, str2, 3), strncat(str3, str4, 3));
}
END_TEST

START_TEST(test_s21_strncat_to_empty)
{
    char str1[100] = "\0";
    char str2[100] = "string";
    char str3[100] = "\0";
    char str4[100] = "string";
    ck_assert_pstr_eq(s21_strncat(str1, str2, 3), s21_strncat(str3, str4, 3));
}
END_TEST

START_TEST(test_s21_strncat_empty)
{
    char str1[100] = "\0";
    char str2[100] = "string";
    char str3[100] = "\0";
    char str4[100] = "string";
    ck_assert_pstr_eq(s21_strncat(str2, str1, 1), s21_strncat(str4, str3, 1));
}
END_TEST

START_TEST(test_s21_strncat_empty_to_empty)
{
    char str1[100] = "\0";
    char str2[100] = "\0";
    char str3[100] = "\0";
    char str4[100] = "\0";
    ck_assert_pstr_eq(s21_strncat(str1, str2, 1), s21_strncat(str3, str4, 1));
}
END_TEST

START_TEST(test_s21_strncat_null_in_the_middle)
{
    char str1[100] = "str\0ing";
    char str2[100] = "ike\0old";
    char str3[100] = "str\0ing";
    char str4[100] = "ike\0old";
    ck_assert_pstr_eq(s21_strncat(str1, str2, 7), s21_strncat(str3, str4, 7));
}
END_TEST

START_TEST(test_s21_strncmp_1_same)
{
    char str1[100] = "abc";
    char str2[100] = "abc";
    long unsigned n = 3;
    ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_s21_strncmp_2_big)
{
    char str1[100] = "abc";
    char str2[100] = "abd";
    long unsigned n = 3;
    ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_s21_strncmp_1_littel)
{
    char str1[100] = "abd";
    char str2[100] = "abc";
    long unsigned n = 3;
    ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_s21_strncpy_not_empty_lines_n0)
{
    char line1[20] = "hello\0";
    char line2[20] = "123\0";
    char* dest = line1;
    const char* src = line2;
    char line3[20] = "hello\0";
    char line4[20] = "123\0";
    char* dest2 = line3;
    const char* src2 = line4;
    s21_size_t n = 0;
    ck_assert_str_eq(s21_strncpy(dest, src, n), strncpy(dest2, src2, n));
}
END_TEST

START_TEST(test_s21_strncpy_not_empty_lines_n2)
{
    char line1[20] = "hello\0";
    char line2[20] = "123\0";
    char* dest = line1;
    const char* src = line2;
    char line3[20] = "hello\0";
    char line4[20] = "123\0";
    char* dest2 = line3;
    const char* src2 = line4;
    s21_size_t n = 2;
    ck_assert_str_eq(s21_strncpy(dest, src, n), strncpy(dest2, src2, n));
}
END_TEST

START_TEST(test_s21_strncpy_not_empty_lines_n15)
{
    char line1[20] = "hello\0";
    char line2[20] = "123\0";
    char* dest = line1;
    const char* src = line2;
    char line3[20] = "hello\0";
    char line4[20] = "123\0";
    char* dest2 = line3;
    const char* src2 = line4;
    s21_size_t n = 15;
    ck_assert_str_eq(s21_strncpy(dest, src, n), strncpy(dest2, src2, n));
}
END_TEST

START_TEST(test_s21_strncpy_first_line_is_empty)
{
    char line1[20] = "\0";
    char line2[20] = "1234567\0";
    char* dest = line1;
    const char* src = line2;
    char line3[20] = "\0";
    char line4[20] = "1234567\0";
    char* dest2 = line3;
    const char* src2 = line4;
    s21_size_t n = 3;
    ck_assert_str_eq(s21_strncpy(dest, src, n), strncpy(dest2, src2, n));
}
END_TEST

START_TEST(test_s21_strncpy_second_line_is_empty)
{
    char line1[20] = "1234567\0";
    char line2[20] = "\0";
    char* dest = line1;
    const char* src = line2;
    char line3[20] = "1234567\0";
    char line4[20] = "\0";
    char* dest2 = line3;
    const char* src2 = line4;
    s21_size_t n = 3;
    ck_assert_str_eq(s21_strncpy(dest, src, n), strncpy(dest2, src2, n));
}
END_TEST

START_TEST(test_s21_strpbrk_normal)
{
    char *str = (void *)"Hello world";
    char *str2 = (void *)"frse";
    ck_assert_str_eq(s21_strpbrk(str, str2), strpbrk(str, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_no_result)
{
    char *str = (void *)"Hello world";
    char *str2 = (void *)"fact";
    ck_assert_ptr_eq(s21_strpbrk(str, str2), strpbrk(str, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_empty_str)
{
    char *str = (void *)"Hello world";
    char *str2 = (void *)"";
    ck_assert_ptr_eq(s21_strpbrk(str, str2), strpbrk(str, str2));
}
END_TEST

START_TEST(test_s21_strrchr_can_find_match)
{
    const char* str = "1234567\0";
    const char* str2 = "1234567\0";
    int element = '3';
    ck_assert_str_eq(s21_strrchr(str, element), strrchr(str2, element));
}
END_TEST

START_TEST(test_s21_strrchr_several_matches)
{
    const char* str = "123123123\0";
    const char* str2 = "123123123\0";
    int element = '2';
    ck_assert_str_eq(s21_strrchr(str, element), strrchr(str2, element));
}
END_TEST

START_TEST(test_s21_strrchr_can_not_find_match)
{
    const char* str = "1234567\0";
    int element = '9';
    char* result_s21_strrchr = s21_strrchr(str, element);
    ck_assert(result_s21_strrchr == NULL);
}
END_TEST

START_TEST(s21_strspn_test_normal)
{
    char *str = "123 456";
    char *symbols = "321 "; 
    ck_assert_uint_eq(s21_strspn(str, symbols), strspn(str, symbols));
}
END_TEST

START_TEST(s21_strspn_test_zero)
{
    char *str = "456 123";
    char *symbol = "321 "; 
    ck_assert_uint_eq(s21_strspn(str, symbol), strspn(str, symbol));
}
END_TEST

START_TEST(s21_strspn_test_empty_symbols)
{
    char *str = "123 456";
    char *symbols = "\0"; 
    ck_assert_uint_eq(s21_strspn(str, symbols), strspn(str, symbols));
}
END_TEST

START_TEST(test_s21_strstr_normal)
{
    char *str = (void *)"Hello world, my friend!";
    char *str2 = (void *)"world";
    ck_assert_str_eq(s21_strstr(str, str2), strstr(str, str2));
}
END_TEST

START_TEST(test_s21_strstr_no_result)
{
    char *str = (void *)"Hello world, my friend!";
    char *str2 = (void *)"worlds";
    ck_assert_ptr_eq(s21_strstr(str, str2), strstr(str, str2));
}
END_TEST

START_TEST(test_s21_strstr_empty_str)
{
    char *str = (void *)"Hello world, my friend!";
    char *str2 = (void *)"";
    ck_assert_ptr_eq(s21_strstr(str, str2), strstr(str, str2));
}
END_TEST

START_TEST(s21_strtok_test_normal)
{
    char str1[] = "all work_and!no play_makes!jack a_dull!boy.";
    char str2[] = "all work_and!no play_makes!jack a_dull!boy.";
    char delims[] = " _!";
    char result_string[50] = ""; 
    char result_string1[50] = ""; 

    char *p = s21_strtok(str1, delims);
    strcat(result_string, p);
    while (p) {
        p = s21_strtok(S21_NULL, delims);
        if (p) strcat(result_string, p);
    }

    char *p1 = strtok(str2, delims);
    strcat(result_string1, p1);
    while (p1) {
        p1 = strtok(NULL, delims);
        if (p1) strcat(result_string1, p1);
    }
    ck_assert_str_eq(result_string, result_string1);       
}
END_TEST

START_TEST(s21_strtok_test_only_delims)
{
    char str1[] = "123123123";    
    char delims[] = "123"; 
    ck_assert_ptr_eq(s21_strtok(str1, delims), strtok(str1, delims));
// #test s21_strtok_test_null
//     char *str1 = NULL;    
//     char *str2 = NULL;
//     char delims[] = "123"; 
//     char *s1 = s21_strtok(str1, delims);
//     printf("OK\n");
//     char *s2 = strtok(str2, delims);
//     printf("OK\n");
//     ck_assert_ptr_eq(s1, s2);
}
END_TEST

START_TEST(s21_strtok_test_empty_delimeters)
{
    char str1[] = "all work and no play makes jack a dull boy. ";
    char str2[] = "all work and no play makes jack a dull boy. ";
    char delims[] = "";
    ck_assert_str_eq(s21_strtok(str1, delims), strtok(str2, delims));
}
END_TEST

START_TEST(s21_strtok_test_end_start_delims)
{
    char str1[] = " !_-, all work and no play makes jack - _-!,";
    char str2[] = " !_-, all work and no play makes jack - _-!,";
    char delims[] = "! -_,";
    char result_string[50] = ""; 
    char result_string1[50] = ""; 

    char *p = s21_strtok(str1, delims);
    strcat(result_string, p);
    while (p) {
        p = s21_strtok(S21_NULL, delims);
        if (p) strcat(result_string, p);
    }
    // printf("%s\n", result_string);
    char *p1 = strtok(str2, delims);
    strcat(result_string1, p1);
    while (p1) {
        p1 = strtok(NULL, delims);
        if (p1) strcat(result_string1, p1);
    }
    // printf("%s\n", result_string1);
    ck_assert_str_eq(result_string, result_string1);       
}
END_TEST

START_TEST(s21_strtok_test_checking_empty_string)
{
    char str1[] = "";
    char str2[] = "";
    char delims[] =" !,-=";
    ck_assert_ptr_eq(s21_strtok(str1, delims), strtok(str2, delims));
}
END_TEST

START_TEST(test_to_lower_regular_characters)
{
    char* str = "abc.ABC,123\0";
    char* str2 = "abc.abc,123\0";
    char* result_to_lower = s21_to_lower(str);
    ck_assert_str_eq(result_to_lower, str2);
    free(result_to_lower);
}
END_TEST

START_TEST(test_to_lower_control_characters)
{
    char* str = "123\b123\a123\n\0";
    char* str2 = "123\b123\a123\n\0";
    char* result_to_lower = s21_to_lower(str);
    ck_assert_str_eq(result_to_lower, str2);
    free(result_to_lower);
}
END_TEST

START_TEST(test_to_lower_empty_line)
{
    char* str = "\0";
    char* str2 = "\0";
    char* result_to_lower = s21_to_lower(str);
    ck_assert_str_eq(result_to_lower, str2);
    free(result_to_lower);
}
END_TEST

START_TEST(test_to_lower_null)
{
    char* str = NULL;
    char* result_to_lower = s21_to_lower(str);
    ck_assert_ptr_eq(result_to_lower, NULL);
    free(result_to_lower);
}
END_TEST

START_TEST(test_to_upper_regular_characters)
{
    char* str = "abc.ABC,123\0";
    char* result_to_upper = s21_to_upper(str);
    ck_assert_str_eq(result_to_upper, "ABC.ABC,123\0");
    free(result_to_upper);
}
END_TEST

START_TEST(test_to_upper_control_characters)
{
    char* str = "123\a123\b123\n\0";
    char* str2 = "123\a123\b123\n\0";
    char* result_to_upper = s21_to_upper(str);
    ck_assert_str_eq(result_to_upper, str2);
    free(result_to_upper);
}
END_TEST

START_TEST(test_to_upper_empty_str)
{
    char* str = "\0";
    char* str2 = "\0";
    char* result_to_upper = s21_to_upper(str);
    ck_assert_str_eq(result_to_upper, str2);
    free(result_to_upper);
}
END_TEST

START_TEST(test_to_upper_null_str)
{
    char* str = NULL;
    char* result_to_upper = s21_to_upper(str);
    ck_assert_ptr_eq(result_to_upper, NULL);
    free(result_to_upper);
}
END_TEST

START_TEST(test_trim_chars_on_margins)
{
    char *str = "***(string)***";
    char *trim = "*()";
    char *result = s21_trim(str, trim);
    ck_assert_str_eq(result, "string");
    free(result);
}
END_TEST

START_TEST(test_trim_chars_in_the_middle)
{
    char *str = "2 * 2 = 4";
    char *trim = " *=";
    char *result = s21_trim(str, trim);
    ck_assert_str_eq(result, "2 * 2 = 4");
    free(result);
}
END_TEST

START_TEST(test_trim_in_the_middle_and_margins)
{
    char *str = "   'Hi, Mark. What are you doing?'       ";
    char *trim = " '.,";
    char *result = s21_trim(str, trim);
    ck_assert_str_eq(result, "Hi, Mark. What are you doing?");
    free(result);
}
END_TEST

START_TEST(test_trim_no_trim_chars)
{
    char *str = "a string";
    char *trim = "'/,.&*()";
    char *result = s21_trim(str, trim);
    ck_assert_str_eq(result, "a string");
    free(result);
}
END_TEST

START_TEST(test_trim_all_chars_trimmed)
{
    char *str = "****(&&&||||)''''''";
    char *trim = "*&|+_'() ";
    char *result = s21_trim(str, trim);
    ck_assert_str_eq(result, "");
    free(result);
}
END_TEST

START_TEST(test_trim_null_src)
{
    char *result = s21_trim(NULL, "./,'");
    ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_trim_null_trim_chars)
{
    char *result = s21_trim("***(code)***", NULL);
    ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_trim_null_strings)
{
    char *result = s21_trim(NULL, NULL);
    ck_assert_ptr_eq(result, NULL);
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test_insert_zero_index);
    tcase_add_test(tc1_1, test_insert_last_index);
    tcase_add_test(tc1_1, test_insert_middle_index);
    tcase_add_test(tc1_1, test_insert_larger_index);
    tcase_add_test(tc1_1, test_insert_neg_index);
    tcase_add_test(tc1_1, test_insert_null_strings);
    tcase_add_test(tc1_1, test_insert_null_src);
    tcase_add_test(tc1_1, test_insert_null_dest);
    tcase_add_test(tc1_1, test_s21_memchr_normal);
    tcase_add_test(tc1_1, test_s21_memchr_zero_len);
    tcase_add_test(tc1_1, test_s21_memchr_min_len);
    tcase_add_test(tc1_1, test_s21_memchr_no_result);
    tcase_add_test(tc1_1, test_s21_memchr_null_char_in_the_middle);
    tcase_add_test(tc1_1, test_s21_memchr_empty_string);
    tcase_add_test(tc1_1, test_s21_memcmp_eq_str);
    tcase_add_test(tc1_1, test_s21_memcmp_neq_str);
    tcase_add_test(tc1_1, test_s21_memcmp_neq_str_diff_len);
    tcase_add_test(tc1_1, test_s21_memcmp_empty_str);
    tcase_add_test(tc1_1, test_s21_memcpy_full);
    tcase_add_test(tc1_1, test_s21_memcpy_partial);
    tcase_add_test(tc1_1, test_s21_memcpy_empty);
    tcase_add_test(tc1_1, s21_memmove_test_different_strings);
    tcase_add_test(tc1_1, s21_memmove_test_same_string_overlap);
    tcase_add_test(tc1_1, s21_memmove_test_same_string_non_overlap);
    tcase_add_test(tc1_1, s21_memmove_test_null);
    tcase_add_test(tc1_1, s21_memset_test_normal);
    tcase_add_test(tc1_1, s21_memset_test_null);
    tcase_add_test(tc1_1, s21_memset_test_newline);
    tcase_add_test(tc1_1, s21_memset_fill_empty_array);
    tcase_add_test(tc1_1, test_s21_sprintf_strings);
    tcase_add_test(tc1_1, test_s21_sprintf_null_char);
    tcase_add_test(tc1_1, test_s21_sprintf_wide_strings);
    tcase_add_test(tc1_1, test_s21_sprintf_float_values);
    tcase_add_test(tc1_1, test_s21_sprintf_nan);
    tcase_add_test(tc1_1, test_s21_sprintf_inf);
    tcase_add_test(tc1_1, test_s21_sprintf_int_values);
    tcase_add_test(tc1_1, s21_sprintf_int_max_values);
    tcase_add_test(tc1_1, s21_sprintf_int_min_values);
    tcase_add_test(tc1_1, test_s21_sprintf_uint_max_values);
    tcase_add_test(tc1_1, test_s21_sprintf_oct_values);
    tcase_add_test(tc1_1, test_s21_sprintf_uint_oct_max_values);
    tcase_add_test(tc1_1, test_s21_sprintf_hex_values);
    tcase_add_test(tc1_1, test_s21_sprintf_uint_hex_max_values);
    tcase_add_test(tc1_1, test_s21_sprintf_ptr);
    tcase_add_test(tc1_1, test_s21_sprintf_ptr_null);
    tcase_add_test(tc1_1, test_s21_sprintf_chars_printed);
    tcase_add_test(tc1_1, test_s21_sprintf_width_and_precision_from_arg);
    tcase_add_test(tc1_1, test_s21_sprintf_width_from_arg_neg);
    tcase_add_test(tc1_1, test_s21_sprintf_float_exp_format);
    tcase_add_test(tc1_1, test_s21_sprintf_float_exp_format_1);
    tcase_add_test(tc1_1, test_s21_sprintf_float_g_format);
    tcase_add_test(tc1_1, test_s21_strcat_s1_sum_s2_normal);
    tcase_add_test(tc1_1, test_s21_strcat_to_empty);
    tcase_add_test(tc1_1, test_s21_strcat_empty);
    tcase_add_test(tc1_1, test_s21_strcat_empty_to_empty);
    tcase_add_test(tc1_1, test_s21_strcat_null_in_the_middle);
    tcase_add_test(tc1_1, test_s21_strchr_normal);
    tcase_add_test(tc1_1, test_s21_strchr_no_result);
    tcase_add_test(tc1_1, test_s21_strchr_empty_str);
    tcase_add_test(tc1_1, test_s21_strcmp_1_equal);
    tcase_add_test(tc1_1, test_s21_strcmp_2_non_equal);
    tcase_add_test(tc1_1, test_s21_strcmp_1_littel);
    tcase_add_test(tc1_1, test_s21_strcpy_not_empty);
    tcase_add_test(tc1_1, test_s21_strcpy_empty);
    tcase_add_test(tc1_1, test_s21_strcspn_equal_lines);
    tcase_add_test(tc1_1, test_s21_strcspn_dif_start);
    tcase_add_test(tc1_1, test_s21_strcspn_dif_end);
    tcase_add_test(tc1_1, test_s21_strcspn_empty_lines);
    tcase_add_test(tc1_1, test_s21_strcspn_first_line_is_empty);
    tcase_add_test(tc1_1, test_s21_strcspn_second_line_is_empty);
    tcase_add_test(tc1_1, test_s21_strerror_true_codes);
    tcase_add_test(tc1_1, test_s21_strerror_wrong_code);
    tcase_add_test(tc1_1, test_s21_strlen_normal);
    tcase_add_test(tc1_1, test_s21_strlen_no_result);
    tcase_add_test(tc1_1, test_s21_strlen_empty_str);
    tcase_add_test(tc1_1, test_s21_strncat_normal);
    tcase_add_test(tc1_1, test_s21_strncat_to_empty);
    tcase_add_test(tc1_1, test_s21_strncat_empty);
    tcase_add_test(tc1_1, test_s21_strncat_empty_to_empty);
    tcase_add_test(tc1_1, test_s21_strncat_null_in_the_middle);
    tcase_add_test(tc1_1, test_s21_strncmp_1_same);
    tcase_add_test(tc1_1, test_s21_strncmp_2_big);
    tcase_add_test(tc1_1, test_s21_strncmp_1_littel);
    tcase_add_test(tc1_1, test_s21_strncpy_not_empty_lines_n0);
    tcase_add_test(tc1_1, test_s21_strncpy_not_empty_lines_n2);
    tcase_add_test(tc1_1, test_s21_strncpy_not_empty_lines_n15);
    tcase_add_test(tc1_1, test_s21_strncpy_first_line_is_empty);
    tcase_add_test(tc1_1, test_s21_strncpy_second_line_is_empty);
    tcase_add_test(tc1_1, test_s21_strpbrk_normal);
    tcase_add_test(tc1_1, test_s21_strpbrk_no_result);
    tcase_add_test(tc1_1, test_s21_strpbrk_empty_str);
    tcase_add_test(tc1_1, test_s21_strrchr_can_find_match);
    tcase_add_test(tc1_1, test_s21_strrchr_several_matches);
    tcase_add_test(tc1_1, test_s21_strrchr_can_not_find_match);
    tcase_add_test(tc1_1, s21_strspn_test_normal);
    tcase_add_test(tc1_1, s21_strspn_test_zero);
    tcase_add_test(tc1_1, s21_strspn_test_empty_symbols);
    tcase_add_test(tc1_1, test_s21_strstr_normal);
    tcase_add_test(tc1_1, test_s21_strstr_no_result);
    tcase_add_test(tc1_1, test_s21_strstr_empty_str);
    tcase_add_test(tc1_1, s21_strtok_test_normal);
    tcase_add_test(tc1_1, s21_strtok_test_only_delims);
    tcase_add_test(tc1_1, s21_strtok_test_empty_delimeters);
    tcase_add_test(tc1_1, s21_strtok_test_end_start_delims);
    tcase_add_test(tc1_1, s21_strtok_test_checking_empty_string);
    tcase_add_test(tc1_1, test_to_lower_regular_characters);
    tcase_add_test(tc1_1, test_to_lower_control_characters);
    tcase_add_test(tc1_1, test_to_lower_empty_line);
    tcase_add_test(tc1_1, test_to_lower_null);
    tcase_add_test(tc1_1, test_to_upper_regular_characters);
    tcase_add_test(tc1_1, test_to_upper_control_characters);
    tcase_add_test(tc1_1, test_to_upper_empty_str);
    tcase_add_test(tc1_1, test_to_upper_null_str);
    tcase_add_test(tc1_1, test_trim_chars_on_margins);
    tcase_add_test(tc1_1, test_trim_chars_in_the_middle);
    tcase_add_test(tc1_1, test_trim_in_the_middle_and_margins);
    tcase_add_test(tc1_1, test_trim_no_trim_chars);
    tcase_add_test(tc1_1, test_trim_all_chars_trimmed);
    tcase_add_test(tc1_1, test_trim_null_src);
    tcase_add_test(tc1_1, test_trim_null_trim_chars);
    tcase_add_test(tc1_1, test_trim_null_strings);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
