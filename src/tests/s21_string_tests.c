/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "tests/headers.check" instead.
 */

#include <check.h>
#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>
#include <float.h>

#include "../s21_string.h"
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
    int c1 = s21_sprintf(buff1, "|5%%|, |%10c|, |%-10.10s|", 'n', "hello");
    int c2 = sprintf(buff2, "|5%%|, |%10c|, |%-10.10s|", 'n', "hello");
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sprintf_float_values) {
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%+.7f|, |% 10.2f|, |%012.1f|", 1234.12, 999.999, -125.56); 
    int c2 = sprintf(buff2, "|%+.7f|, |% 10.2f|, |%012.1f|", 1234.12, 999.999, -125.56); 
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
    int c1 = s21_sprintf(buff1, "|%-20d|, |%n| |%s|, |%n| |%.2f||%n|", 1234, &p1, "string", &p2, 234.564, &p3);
    int c2 = sprintf(buff2, "|%-20d|, |%n| |%s|, |%n| |%.2f||%n|", 1234, &p4, "string", &p5, 234.564, &p6);
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2); 
    ck_assert_int_eq(p1, p4); 
    ck_assert_int_eq(p2, p5); 
    ck_assert_int_eq(p3, p6);
}
END_TEST

START_TEST(test_s21_sprintf_custom_width_and_precision) {
    char buff1[100000];
    char buff2[100000];
    int c1 = s21_sprintf(buff1, "|%-*.*d|, |%0*i|, |%*s|", 20, 10, 12345, 10, 5782, 15, "string");
    int c2 = sprintf(buff2, "|%-*.*d|, |%0*i|, |%*s|", 20, 10, 12345, 10, 5782, 15, "string");
    ck_assert_str_eq(buff1, buff2);
    ck_assert_int_eq(c1, c2);
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

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
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
    tcase_add_test(tc1_1, test_s21_sprintf_float_values);
    tcase_add_test(tc1_1, test_s21_sprintf_int_values);
    tcase_add_test(tc1_1, test_s21_sprintf_uint_values);
    tcase_add_test(tc1_1, test_s21_sprintf_oct_values);
    tcase_add_test(tc1_1, test_s21_sprintf_hex_values);
    tcase_add_test(tc1_1, test_s21_sprintf_ptr);
    tcase_add_test(tc1_1, test_s21_sprintf_chars_printed);
    tcase_add_test(tc1_1, test_s21_sprintf_custom_width_and_precision);
    tcase_add_test(tc1_1, test_s21_strerror_true_codes);
    tcase_add_test(tc1_1, test_s21_strerror_wrong_code);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
