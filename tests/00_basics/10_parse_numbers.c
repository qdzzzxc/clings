/* Тесты к exercises/00_basics/10_parse_numbers.c. Запуск: make test 0 10 */

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/00_basics/10_parse_numbers.c"
#undef main

static void check_sum(const char* s, long expected_sum, size_t expected_count)
{
    long sum = 123;
    size_t count = 456;

    assert(sum_numbers_in_string(s, &sum, &count) == 1);
    assert(sum == expected_sum);
    assert(count == expected_count);
}

static void check_error(const char* s)
{
    long sum = 123;
    size_t count = 456;

    assert(sum_numbers_in_string(s, &sum, &count) == 0);
    assert(sum == 123);
    assert(count == 456);
}

static void test_example(void)
{
    check_sum("12, 0x1F, -7", 36, 3);
}

static void test_bases(void)
{
    check_sum("0x10", 16, 1);
    check_sum("0XfF", 255, 1);
    check_sum("017", 15, 1);
    check_sum("0", 0, 1);
    check_sum("-0x10, +5", -11, 2);
}

static void test_separators(void)
{
    check_sum("", 0, 0);
    check_sum("  , ,\t\n ", 0, 0);
    check_sum("1 2\t3\n4,5", 15, 5);
    check_sum(",,1,,2,,", 3, 2);
}

static void test_errors(void)
{
    check_error("abc");
    check_error("12abc");
    check_error("1, x, 2");
    check_error("1; 2");
    check_error("1.5");
    check_error("-");
    check_error("099");
}

static void test_range(void)
{
    char text[64] = "";

    snprintf(text, sizeof(text), "%ld", LONG_MAX);
    check_sum(text, LONG_MAX, 1);
    check_error("99999999999999999999999");
    check_error("1, -99999999999999999999999");
}

static void test_errno_from_before(void)
{
    /* Старое значение errno не должно влиять на результат. */
    errno = ERANGE;
    check_sum("5", 5, 1);
}

static void test_format_list(void)
{
    char buffer[32] = "";
    int values[] = { 1, -2, 3 };
    int one[] = { 42 };

    assert(format_list(buffer, sizeof(buffer), values, 3) == 1);
    assert(strcmp(buffer, "1, -2, 3") == 0);
    assert(format_list(buffer, sizeof(buffer), one, 1) == 1);
    assert(strcmp(buffer, "42") == 0);
    assert(format_list(buffer, sizeof(buffer), values, 0) == 1);
    assert(strcmp(buffer, "") == 0);
}

static void test_format_exact_fit(void)
{
    char buffer[9] = "";
    int values[] = { 1, -2, 3 };

    /* "1, -2, 3" — 8 символов и '\0'. */
    assert(format_list(buffer, sizeof(buffer), values, 3) == 1);
    assert(strcmp(buffer, "1, -2, 3") == 0);
}

static void test_format_too_small(void)
{
    char buffer[16] = "";
    int values[] = { 100, 200, 300, 400, 500 };

    memset(buffer, 'x', sizeof(buffer));
    assert(format_list(buffer, 8, values, 5) == 0);
    assert(strlen(buffer) < 8);
    assert(strncmp(buffer, "100, 20", strlen(buffer)) == 0);
    assert(buffer[8] == 'x');
    assert(format_list(buffer, 1, values, 1) == 0);
    assert(buffer[0] == '\0');
}

int main(void)
{
    test_example();
    test_bases();
    test_separators();
    test_errors();
    test_range();
    test_errno_from_before();
    test_format_list();
    test_format_exact_fit();
    test_format_too_small();

    puts("All tests passed");
    return 0;
}
