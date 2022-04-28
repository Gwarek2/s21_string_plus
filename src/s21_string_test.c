#include <stdlib.h>
#include <string.h>
#include <check.h>

#include "s21_string.h"


START_TEST(test_s21_memchr_normal) {
    void *str = (void*) "Hello world";
    void *res1;
    void *res2;
    ck_assert_msg((res1 = s21_memchr(str, 111, 10)) == (res2 = memchr(str, 111, 10)),
                  "Result: %s. Expected: %s.", res1, res2);
    
} END_TEST

START_TEST(test_s21_memchr_no_result) {
    void *str = (void*) "Hello world";
    void *res1;
    void *res2;
    ck_assert_msg((res1 = s21_memchr(str, 107, 11)) == (res2 = memchr(str, 107, 11)),
                  "Result: %s. Expected: %s.", res1, res2);
    
} END_TEST

START_TEST(test_s21_memchr_empty_str) {
    void *str = (void*) "\n\0";
    void *res1;
    void *res2;
    ck_assert_msg((res1 = s21_memchr(str, 12, 1)) == (res2 = memchr(str, 12, 1)),
                  "Result: %s. Expected: %s.", res1, res2);
    
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

START_TEST(test_s21_memcmp_normal) {
    void *str1 = (void*) "Hello world";
    void *str2 = (void*) "Hello world";
    int res1;
    int res2;
    ck_assert_msg((res1 = s21_memcmp(str1, str2, 11)) == (res2 = memcmp(str1, str2, 11)),
                  "Result: %i. Expected: %i.", res1, res2);
} END_TEST

START_TEST(test_s21_memcmp_not_equal) {
    void *str1 = (void*) "Hello world";
    void *str2 = (void*) "HELLO WORLD";
    int res1;
    int res2;
    ck_assert_msg((res1 = s21_memcmp(str1, str2, 11)) == (res2 = memcmp(str1, str2, 11)),
                  "Result: %i. Expected: %i.", res1, res2);
} END_TEST

START_TEST(test_s21_memcmp_empty_str) {
    void *str1 = (void*) "\0";
    void *str2 = (void*) "\0";
    int res1;
    int res2;
    ck_assert_msg((res1 = s21_memcmp(str1, str2, 1)) == (res2 = memcmp(str1, str2, 1)),
                  "Result: %i. Expected: %i.", res1, res2);
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

START_TEST(test_s21_memcpy_full) {
    const void *str = (void*) "Hello world";
    char buff1[20]; char buff2[20];
    void *buffer1 = (void*) buff1;
    void *buffer2 = (void*) buff2;
    s21_memcpy(buffer1, str, 11);
    memcpy(buffer2, str, 11);
    ck_assert_msg(memcmp(buffer1, buffer2, 11) == 0, "Result: %s. Expected: %s.", buffer1, buffer2);
} END_TEST

START_TEST(test_s21_memcpy_partial) {
    const void *str = (void*) "Text to copy";
    char buff1[20]; char buff2[20];
    void *buffer1 = (void*) buff1;
    void *buffer2 = (void*) buff2;
    s21_memcpy(buffer1, str, 6);
    memcpy(buffer2, str, 6);
    ck_assert_msg(memcmp(buffer1, buffer2, 6) == 0, "Result: %s. Expected: %s.", buffer1, buffer2);
} END_TEST

START_TEST(test_s21_memcpy_empty) {
    const void *str = (void*) "\0";
    char buff1[20]; char buff2[20];
    void *buffer1 = (void*) buff1;
    void *buffer2 = (void*) buff2;
    s21_memcpy(buffer1, str, 1);
    memcpy(buffer2, str, 1);
    ck_assert_msg(memcmp(buffer1, buffer2, 1) == 0, "Result: %s. Expected: %s.", buffer1, buffer2);
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

START_TEST(test_s21_strerror_1) {
} END_TEST

START_TEST(test_s21_strerror_2) {
} END_TEST

START_TEST(test_s21_strerror_3) {
} END_TEST

Suite * s21_string_strerror_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("S21_string_strerror");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_s21_strerror_1);
    tcase_add_test(tc_core, test_s21_strerror_2);
    tcase_add_test(tc_core, test_s21_strerror_3);
    suite_add_tcase(s, tc_core);

    return s;
}

int main() {
    int number_failed;
    Suite *s_memchr;
    Suite *s_memcmp;
    Suite *s_memcpy;
    SRunner *sr;

    s_memchr = s21_string_memchr_suite();
    s_memcmp = s21_string_memcmp_suite();
    s_memcpy = s21_string_memcpy_suite();
    sr = srunner_create(s_memchr);
    srunner_add_suite(sr, s_memcmp);
    srunner_add_suite(sr, s_memcpy);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
