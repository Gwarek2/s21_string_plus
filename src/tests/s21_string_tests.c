/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "tests/headers.check" instead.
 */

#include <check.h>

#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

#include "../s21_string.h"
START_TEST(test_insert_zero_index) {
    char* str1 = "123456\0";
    char* str2 = "AB\0";
    size_t index = 0;
    char* expected_result = "AB123456\0";
    char* result_insert = s21_insert(str1, str2, index);
    ck_assert_str_eq(result_insert, expected_result);
    free(result_insert);
}
END_TEST

START_TEST(test_insert_last_index) {
    char* str1 = "123456\0";
    char* str2 = "AB\0";
    size_t index = 6;
    char* expected_result = "123456AB\0";
    char* result_insert = s21_insert(str1, str2, index);
    ck_assert_str_eq(result_insert, expected_result);
    free(result_insert);
}
END_TEST

START_TEST(test_insert_middle_index) {
    char* str1 = "123456\0";
    char* str2 = "AB\0";
    size_t index = 3;
    char* expected_result = "123AB456\0";
    char* result_insert = s21_insert(str1, str2, index);
    ck_assert_str_eq(result_insert, expected_result);
    free(result_insert);
}
END_TEST

START_TEST(test_insert_larger_index) {
    char* str1 = "123456\0";
    char* str2 = "AB\0";
    size_t index = 11;
    char* result_insert = s21_insert(str1, str2, index);
    ck_assert_ptr_eq(result_insert, NULL);
    free(result_insert);
}
END_TEST

START_TEST(test_s21_memchr_normal) {
    void *str = (void*) "Hello world";
    ck_assert_str_eq(s21_memchr(str, 111, 10), memchr(str, 111, 10));
}
END_TEST

START_TEST(test_s21_memchr_no_result) {
    void *str2 = (void*) "Hello world";
    void *str1 = (void*) "Hello world";
    ck_assert_ptr_eq(s21_memchr(str1, 107, 11), memchr(str2, 107, 11));
}
END_TEST

START_TEST(test_s21_memchr_empty_str) {
    void *str1 = (void*) "\0";
    void *str2 = (void*) "\0";
    ck_assert_ptr_eq(s21_memchr(str1, 12, 1), memchr(str2, 12, 1));
}
END_TEST

START_TEST(test_s21_memcmp_normal) {
    void *str1 = (void*) "Hello world";
    void *str2 = (void*) "Hello world";
    ck_assert_int_eq(s21_memcmp(str1, str2, 11), memcmp(str1, str2, 11));
}
END_TEST

START_TEST(test_s21_memcmp_not_equal) {
    void *str1 = (void*) "Hello world";
    void *str2 = (void*) "HELLO WORLD";
    ck_assert_int_eq(s21_memcmp(str1, str2, 11), memcmp(str1, str2, 11));
}
END_TEST

START_TEST(test_s21_memcmp_empty_str) {
    void *str1 = (void*) "\0";
    void *str2 = (void*) "\0";
    ck_assert_int_eq(s21_memcmp(str1, str2, 1), memcmp(str1, str2, 1));
}
END_TEST

START_TEST(test_s21_memcpy_full) {
    void *template = (void*) "Hello world";
    char buff1[50]; char buff2[50];
    void *str1 = (void*) buff1;
    void *str2 = (void*) buff2;
    memcpy(str1, template, 10);
    s21_memcpy(str2, template, 10);
    ck_assert_int_eq(memcmp(str1, str2, 10), 0);
}
END_TEST

START_TEST(test_s21_memcpy_partial) {
    void *template = (void*) "Text to copy";
    char buff1[50]; char buff2[50];
    void *str1 = (void*) buff1;
    void *str2 = (void*) buff2;
    memcpy(str1, template, 5);
    s21_memcpy(str2, template, 5);
    ck_assert_int_eq(memcmp(str1, str2, 5), 0);
}
END_TEST

START_TEST(test_s21_memcpy_empty) {
    void *template = (void*) "\0";
    char buff1[50]; char buff2[50];
    void *str1 = (void*) buff1;
    void *str2 = (void*) buff2;
    memcpy(str1, template, 1);
    s21_memcpy(str2, template, 1);
    ck_assert_int_eq(memcmp(str1, str2, 1), 0);
#include "../s21_string.h"
}
END_TEST

START_TEST(test_s21_sprintf_strings) {
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

START_TEST(test_s21_sprintf_wide_strings) {
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|5%%|, |%10lc|, |%-10.10ls|", L'n', L"hello");
    int c2 = sprintf(buff2, "|5%%|, |%10lc|, |%-10.10ls|", L'n', L"hello");
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_float_values) {
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%+.7f|, |% 10.2f|, |%012.1f|, |%#.0f|", 1234.12, 999.999, -125.56, 76456.9);
    int c2 = sprintf(buff2, "|%+.7f|, |% 10.2f|, |%012.1f|, |%#.0f|", 1234.12, 999.999, -125.56, 76456.9);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_int_values) {
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%-10.7d|, |%010d|, |%+4i|", 9512, -1234, 4219);
    int c2 = sprintf(buff2, "|%-10.7d|, |%010d|, |%+4i|", 9512, -1234, 4219);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_uint_values) {
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%-10.7u|, |%010u|, |%4u|", 9512, 1234, 4219);
    int c2 = sprintf(buff2, "|%-10.7u|, |%010u|, |%4u|", 9512, 1234, 4219);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_oct_values) {
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%-10.7o|, |%010o|, |%#o|", 9512, 1234, 4219);
    int c2 = sprintf(buff2, "|%-10.7o|, |%010o|, |%#o|", 9512, 1234, 4219);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_hex_values) {
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%-10.7x|, |%010X|, |%#7x|", 9512, 1234, 4219);
    int c2 = sprintf(buff2, "|%-10.7x|, |%010X|, |%#7x|", 9512, 1234, 4219);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_ptr) {
    char buff1[100000];
    char buff2[100000];
    int p1, p2, p3;
    int c1 = s21_sprintf(buff1, "|%-20p|, |%p|, |%15p|", &p1, &p2, &p3);
    int c2 = sprintf(buff2, "|%-20p|, |%p|, |%15p|", &p1, &p2, &p3);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_chars_printed) {
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

START_TEST(test_s21_sprintf_width_and_precision_from_arg) {
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%-*.*d|, |%0*i|, |%*s|", 20, 10, 12345, 10, 5782, 15, "string");
    int c2 = sprintf(buff2, "|%-*.*d|, |%0*i|, |%*s|", 20, 10, 12345, 10, 5782, 15, "string");
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
// #test test_s21_sprintf_float_exp_format
//     char buff1[100000];
//     char buff2[100000];
//     int c1 = s21_sprintf(buff1, "|%#.0E|, |%-10.2e|, |%+.4E|", 239.99, 0.001329, -99.99);
//     int c2 = sprintf(buff2, "|%#.0E|, |%-10.2e|, |%+.4E|", 239.99, 0.001329, -99.99);
//     ck_assert_str_eq(buff1, buff2);
//     ck_assert_int_eq(c1, c2);
// #test test_s21_sprintf_float_g_format
//     char buff1[100000];
//     char buff2[100000];
//     int c1 = s21_sprintf(buff1, "|%#.0G|, |%-10g|", 239.99, 0.001329);
//     int c2 = sprintf(buff2, "|%#.0G|, |%-10g|", 239.99, 0.001329);
//     ck_assert_str_eq(buff1, buff2);
//     ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_strcat_s1_sum_s2) {
    char str1[100] = "01234";
    char str2[100] = "56789";
    ck_assert_pstr_eq(s21_strcat(str1, str2), strcat(str1, str2));
}
END_TEST

START_TEST(test_s21_strchr_normal) {
    char *str = (void *)"Hello world";
    char *str2 = "o";
    ck_assert_str_eq(s21_strchr(str, *str2), strchr(str, *str2));
}
END_TEST

START_TEST(test_s21_strchr_no_result) {
    char *str = (void *)"Hello world";
    char *str2 = "f";
    ck_assert_ptr_eq(s21_strchr(str, *str2), strchr(str, *str2));
}
END_TEST

START_TEST(test_s21_strchr_empty_str) {
    char *str = (void *)"Hello world";
    char *str2 = "";
    ck_assert_str_eq(s21_strchr(str, *str2), strchr(str, *str2));
}
END_TEST

START_TEST(test_s21_strcmp_1_equal) {
    char str1[100] = "abc";
    char str2[100] = "abc";
    ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(test_s21_strcmp_2_non_equal) {
    char str1[100] = "abc";
    char str2[100] = "abd";
    ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(test_s21_strcmp_1_littel) {
    char str1[100] = "abd";
    char str2[100] = "abc";
    ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(test_s21_strcpy_not_empty) {
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

START_TEST(test_s21_strcpy_empty) {
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

START_TEST(test_s21_strcspn_equal_lines) {
    char* dest = "hello\0";
    const char* src = "hello\0";
    char* dest2 = "hello\0";
    const char* src2 = "hello\0";
    ck_assert_int_eq(s21_strcspn(dest, src), strcspn(dest2, src2));
}
END_TEST

START_TEST(test_s21_strcspn_dif_start) {
    char* dest = "hello\0";
    const char* src = "bello\0";
    char* dest2 = "hello\0";
    const char* src2 = "bello\0";
    ck_assert_int_eq(s21_strcspn(dest, src), strcspn(dest2, src2));
}
END_TEST

START_TEST(test_s21_strcspn_dif_end) {
    char* dest = "hello, friend\0";
    const char* src = "hello\0";
    char* dest2 = "hello, friend\0";
    const char* src2 = "hello\0";
    ck_assert_int_eq(s21_strcspn(dest, src), strcspn(dest2, src2));
}
END_TEST

START_TEST(test_s21_strcspn_empty_lines) {
    char* dest = "\0";
    const char* src = "\0";
    char* dest2 = "\0";
    const char* src2 = "\0";
    ck_assert_int_eq(s21_strcspn(dest, src), strcspn(dest2, src2));
}
END_TEST

START_TEST(test_s21_strcspn_first_line_is_empty) {
    char* dest = "\0";
    const char* src = "hello\0";
    char* dest2 = "\0";
    const char* src2 = "hello\0";
    ck_assert_int_eq(s21_strcspn(dest, src), strcspn(dest2, src2));
}
END_TEST

START_TEST(test_s21_strcspn_second_line_is_empty) {
    char* dest = "hello\0";
    const char* src = "\0";
    char* dest2 = "hello\0";
    const char* src2 = "\0";
    ck_assert_int_eq(s21_strcspn(dest, src), strcspn(dest2, src2));
}
END_TEST

START_TEST(test_s21_strerror_true_codes) {
    for (int i = 0; i <= 140; i++)
        ck_assert_str_eq(strerror(i), s21_strerror(i));
}
END_TEST

START_TEST(test_s21_strerror_wrong_code) {
    ck_assert_str_eq(strerror(-1), s21_strerror(-1));
}
END_TEST

START_TEST(test_s21_strlen_normal) {
    char *str = (void *)"Hello world";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strlen_no_result) {
    void *str = (void *)"";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strlen_empty_str) {
    void *str = (void *)"\n\0";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strncat_s1_sum_s2_3) {
    char str1[100] = "01234";
    char str2[100] = "56789";
    ck_assert_pstr_eq(s21_strncat(str1, str2, 3), strncat(str1, str2, 3));
}
END_TEST

START_TEST(test_s21_strncmp_1_same) {
    char str1[100] = "abc";
    char str2[100] = "abc";
    long unsigned n = 3;
    ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_s21_strncmp_2_big) {
    char str1[100] = "abc";
    char str2[100] = "abd";
    long unsigned n = 3;
    ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_s21_strncmp_1_littel) {
    char str1[100] = "abd";
    char str2[100] = "abc";
    long unsigned n = 3;
    ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_s21_strncpy_not_empty_lines_n0) {
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

START_TEST(test_s21_strncpy_not_empty_lines_n2) {
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

START_TEST(test_s21_strncpy_not_empty_lines_n15) {
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

START_TEST(test_s21_strncpy_first_line_is_empty) {
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

START_TEST(test_s21_strncpy_second_line_is_empty) {
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

START_TEST(test_s21_strpbrk_normal) {
    char *str = (void *)"Hello world";
    char *str2 = (void *)"frse";
    ck_assert_str_eq(s21_strpbrk(str, str2), strpbrk(str, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_no_result) {
    char *str = (void *)"Hello world";
    char *str2 = (void *)"fact";
    ck_assert_ptr_eq(s21_strpbrk(str, str2), strpbrk(str, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_empty_str) {
    char *str = (void *)"Hello world";
    char *str2 = (void *)"";
    ck_assert_ptr_eq(s21_strpbrk(str, str2), strpbrk(str, str2));
}
END_TEST

START_TEST(test_s21_strrchr_can_find_match) {
    const char* str = "1234567\0";
    const char* str2 = "1234567\0";
    int element = '3';
    ck_assert_str_eq(s21_strrchr(str, element), strrchr(str2, element));
}
END_TEST

START_TEST(test_s21_strrchr_several_matches) {
    const char* str = "123123123\0";
    const char* str2 = "123123123\0";
    int element = '2';
    ck_assert_str_eq(s21_strrchr(str, element), strrchr(str2, element));
}
END_TEST

START_TEST(test_s21_strrchr_can_not_find_match) {
    const char* str = "1234567\0";
    int element = '9';
    char* result_s21_strrchr = s21_strrchr(str, element);
    ck_assert(result_s21_strrchr == NULL);
}
END_TEST

START_TEST(test_s21_strstr_normal) {
    char *str = (void *)"Hello world, my friend!";
    char *str2 = (void *)"world";
    ck_assert_str_eq(s21_strstr(str, str2), strstr(str, str2));
}
END_TEST

START_TEST(test_s21_strstr_no_result) {
    char *str = (void *)"Hello world, my friend!";
    char *str2 = (void *)"worlds";
    ck_assert_ptr_eq(s21_strstr(str, str2), strstr(str, str2));
}
END_TEST

START_TEST(test_s21_strstr_empty_str) {
    char *str = (void *)"Hello world, my friend!";
    char *str2 = (void *)"";
    ck_assert_ptr_eq(s21_strstr(str, str2), strstr(str, str2));
}
END_TEST

START_TEST(test_to_lower_regular_characters) {
    char* str = "abc.ABC,123\0";
    char* str2 = "abc.abc,123\0";
    char* result_to_lower = s21_to_lower(str);
    ck_assert_str_eq(result_to_lower, str2);
    free(result_to_lower);
}
END_TEST

START_TEST(test_to_lower_control_characters) {
    char* str = "123\b123\a123\n\0";
    char* str2 = "123\b123\a123\n\0";
    char* result_to_lower = s21_to_lower(str);
    ck_assert_str_eq(result_to_lower, str2);
    free(result_to_lower);
}
END_TEST

START_TEST(test_to_lower_empty_line) {
    char* str = "\0";
    char* str2 = "\0";
    char* result_to_lower = s21_to_lower(str);
    ck_assert_str_eq(result_to_lower, str2);
    free(result_to_lower);
}
END_TEST

START_TEST(test_to_lower_null) {
    char* str = NULL;
    char* result_to_lower = s21_to_lower(str);
    ck_assert_ptr_eq(result_to_lower, NULL);
    free(result_to_lower);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test_insert_zero_index);
    tcase_add_test(tc1_1, test_insert_last_index);
    tcase_add_test(tc1_1, test_insert_middle_index);
    tcase_add_test(tc1_1, test_insert_larger_index);
    tcase_add_test(tc1_1, test_s21_memchr_normal);
    tcase_add_test(tc1_1, test_s21_memchr_no_result);
    tcase_add_test(tc1_1, test_s21_memchr_empty_str);
    tcase_add_test(tc1_1, test_s21_memcmp_normal);
    tcase_add_test(tc1_1, test_s21_memcmp_not_equal);
    tcase_add_test(tc1_1, test_s21_memcmp_empty_str);
    tcase_add_test(tc1_1, test_s21_memcpy_full);
    tcase_add_test(tc1_1, test_s21_memcpy_partial);
    tcase_add_test(tc1_1, test_s21_memcpy_empty);
    tcase_add_test(tc1_1, test_s21_sprintf_strings);
    tcase_add_test(tc1_1, test_s21_sprintf_wide_strings);
    tcase_add_test(tc1_1, test_s21_sprintf_float_values);
    tcase_add_test(tc1_1, test_s21_sprintf_int_values);
    tcase_add_test(tc1_1, test_s21_sprintf_uint_values);
    tcase_add_test(tc1_1, test_s21_sprintf_oct_values);
    tcase_add_test(tc1_1, test_s21_sprintf_hex_values);
    tcase_add_test(tc1_1, test_s21_sprintf_ptr);
    tcase_add_test(tc1_1, test_s21_sprintf_chars_printed);
    tcase_add_test(tc1_1, test_s21_sprintf_width_and_precision_from_arg);
    tcase_add_test(tc1_1, test_s21_strcat_s1_sum_s2);
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
    tcase_add_test(tc1_1, test_s21_strncat_s1_sum_s2_3);
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
    tcase_add_test(tc1_1, test_s21_strstr_normal);
    tcase_add_test(tc1_1, test_s21_strstr_no_result);
    tcase_add_test(tc1_1, test_s21_strstr_empty_str);
    tcase_add_test(tc1_1, test_to_lower_regular_characters);
    tcase_add_test(tc1_1, test_to_lower_control_characters);
    tcase_add_test(tc1_1, test_to_lower_empty_line);
    tcase_add_test(tc1_1, test_to_lower_null);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
