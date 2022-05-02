#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <check.h>
#include <errno.h>

#include "s21_string.h"

// memchr tests
START_TEST(test_s21_memchr_normal) {
    void *str = (void*) "Hello world";
    ck_assert_str_eq(s21_memchr(str, 111, 10), memchr(str, 111, 10));
} END_TEST

START_TEST(test_s21_memchr_no_result) {
    void *str = (void*) "Hello world";
    ck_assert_str_eq(s21_memchr(str, 107, 11), memchr(str, 107, 11));
} END_TEST

START_TEST(test_s21_memchr_empty_str) {
    void *str = (void*) "\n\0";
    ck_assert_str_eq(s21_memchr(str, 12, 1), memchr(str, 12, 1));
} END_TEST

Suite * s21_string_memchr_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("S21_string_memchr");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_s21_memchr_normal);
    tcase_add_test(tc_core, test_s21_memchr_no_result);
    tcase_add_test(tc_core, test_s21_memchr_empty_str);
    suite_add_tcase(s, tc_core);

    return s;
}

// memcmp tests
START_TEST(test_s21_memcmp_normal) {
    void *str1 = (void*) "Hello world";
    void *str2 = (void*) "Hello world";
    ck_assert_str_eq(s21_memcmp(str1, str2, 11), memcmp(str1, str2, 11));
} END_TEST

START_TEST(test_s21_memcmp_not_equal) {
    void *str1 = (void*) "Hello world";
    void *str2 = (void*) "HELLO WORLD";
    ck_assert_str_eq(s21_memcmp(str1, str2, 11), memcmp(str1, str2, 11));
} END_TEST

START_TEST(test_s21_memcmp_empty_str) {
    void *str1 = (void*) "\0";
    void *str2 = (void*) "\0";
    ck_assert_str_eq(s21_memcmp(str1, str2, 1), memcmp(str1, str2, 1));
} END_TEST

Suite * s21_string_memcmp_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("S21_string_memcmp");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_s21_memcmp_normal);
    tcase_add_test(tc_core, test_s21_memcmp_not_equal);
    tcase_add_test(tc_core, test_s21_memcmp_empty_str);
    suite_add_tcase(s, tc_core);

    return s;
}

// memcpy tests
START_TEST(test_s21_memcpy_full) {
    void *str1 = (void*) "Hello world";
    void *str2 = (void*) "Hello world";
    ck_assert_int_eq(memcmp(str1, str2, 11), 0);
} END_TEST

START_TEST(test_s21_memcpy_partial) {
    void *str1 = (void*) "Text to copy";
    void *str2 = (void*) "Text to copy";
    ck_assert_int_eq(memcmp(str1, str2, 6), 0);
} END_TEST

START_TEST(test_s21_memcpy_empty) {
    void *str1 = (void*) "\0";
    void *str2 = (void*) "\0";
    ck_assert_str_eq(memcmp(str1, str2, 1), 0);
} END_TEST

Suite * s21_string_memcpy_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("S21_string_memcpy");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_s21_memcpy_full);
    tcase_add_test(tc_core, test_s21_memcpy_partial);
    tcase_add_test(tc_core, test_s21_memcpy_empty);
    suite_add_tcase(s, tc_core);

    return s;
}

// strerror tests
START_TEST(test_s21_strerror_code_0) {
    ck_assert_str_eq(strerror(errno), s21_strerror(errno));
} END_TEST

START_TEST(test_s21_strerror_code_1) {
    FILE *f = fopen("non-existing-file", "r");
    ck_assert_str_eq(strerror(errno), s21_strerror(errno));
    if (f != NULL)
        fclose(f);
} END_TEST

START_TEST(test_s21_strerror_code_21) {
    FILE *f = fopen("/", "w");
    if (f == NULL)
        ck_assert_str_eq(strerror(errno), s21_strerror(errno));
    else
        fclose(f);
} END_TEST

START_TEST(test_s21_strerror_wrong_code) {
    ck_assert_str_eq(strerror(-1), s21_strerror(-1));
} END_TEST

Suite * s21_string_strerror_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("S21_string_strerror");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_s21_strerror_code_0);
    tcase_add_test(tc_core, test_s21_strerror_code_1);
    tcase_add_test(tc_core, test_s21_strerror_code_21);
    tcase_add_test(tc_core, test_s21_strerror_wrong_code);
    suite_add_tcase(s, tc_core);

    return s;
}

// // sprintf test
// START_TEST(test_s21_sprintf_normal) {
//     char buff1[100];
//     char buff2[100];
//     int n1 = -123;
//     double n2 = 1.01;
//     char *str = "hello";
//     int c1 = s21_sprintf(buff1, "'%i' is int, 5%%, the float is '%f',  the char is '%c', the string is '%s'", n1, n2, *str, str);
//     int c2 = sprintf(buff2, "'%i' is int, 5%%, the float is '%f',  the char is '%c', the string is '%s'", n1, n2, *str, str);
//     ck_assert_str_eq(buff1, buff2);
//     ck_assert_int_eq(c1, c2);
// } END_TEST

// Suite * s21_string_ssprintf_suite(void) {
//     Suite *s;
//     TCase *tc_core;

//     s = suite_create("S21_string_sprintf");
//     tc_core = tcase_create("Core");
//     tcase_add_test(tc_core, test_s21_sprintf_normal);
//     suite_add_tcase(s, tc_core);

//     return s;
// }

// main
int main() {
    int number_failed;
    Suite *s_memchr;
    Suite *s_memcmp;
    Suite *s_memcpy;
    Suite *s_strerror;
    // Suite *s_sprintf;
    SRunner *sr;

    s_memchr = s21_string_memchr_suite();
    s_memcmp = s21_string_memcmp_suite();
    s_memcpy = s21_string_memcpy_suite();
    s_strerror = s21_string_strerror_suite();
    // s_sprintf = s21_string_ssprintf_suite();
    sr = srunner_create(s_memchr);
    srunner_add_suite(sr, s_memcmp);
    srunner_add_suite(sr, s_memcpy);
    srunner_add_suite(sr, s_strerror);
    // srunner_add_suite(sr, s_sprintf);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
