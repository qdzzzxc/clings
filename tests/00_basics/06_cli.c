/* Тесты к exercises/00_basics/06_cli.c. Запуск: make test 0 6 */

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/00_basics/06_cli.c"
#undef main

static void test_parse_positive(void)
{
    long value = 0;

    assert(parse_long("123", &value));
    assert(value == 123);
}

static void test_parse_negative(void)
{
    long value = 0;

    assert(parse_long("-42", &value));
    assert(value == -42);
}

static void test_parse_zero(void)
{
    long value = 123;

    assert(parse_long("0", &value));
    assert(value == 0);
}

static void test_parse_invalid_letters(void)
{
    long value = 0;

    assert(!parse_long("abc", &value));
}

static void test_parse_invalid_suffix(void)
{
    long value = 0;

    assert(!parse_long("12abc", &value));
}

static void test_parse_empty(void)
{
    long value = 0;

    assert(!parse_long("", &value));
}

static void test_analyze(void)
{
    char* argv[] = {
        "task",
        "10",
        "-3",
        "7",
        "5"
    };

    size_t count = 0;
    long sum = 0;
    long min = 0;
    long max = 0;

    assert(analyze_args(5, argv, &count, &sum, &min, &max));

    assert(count == 4);
    assert(sum == 19);
    assert(min == -3);
    assert(max == 10);
}

static void test_single(void)
{
    char* argv[] = {
        "task",
        "-7"
    };

    size_t count = 0;
    long sum = 0;
    long min = 0;
    long max = 0;

    assert(analyze_args(2, argv, &count, &sum, &min, &max));

    assert(count == 1);
    assert(sum == -7);
    assert(min == -7);
    assert(max == -7);
}

static void test_invalid_argument(void)
{
    char* argv[] = {
        "task",
        "10",
        "oops",
        "20"
    };

    size_t count = 0;
    long sum = 0;
    long min = 0;
    long max = 0;

    assert(!analyze_args(4, argv, &count, &sum, &min, &max));
}

static void test_no_numbers(void)
{
    char* argv[] = {
        "task"
    };

    size_t count = 0;
    long sum = 0;
    long min = 0;
    long max = 0;

    assert(!analyze_args(1, argv, &count, &sum, &min, &max));
}

static void test_parse_invalid_trailing_space(void)
{
    long value = 0;

    assert(!parse_long("12 ", &value));
}

static void test_parse_invalid_only_sign(void)
{
    long value = 0;

    assert(!parse_long("-", &value));
}

static void test_parse_invalid_fraction(void)
{
    long value = 0;

    assert(!parse_long("1.5", &value));
}

static void test_parse_limits(void)
{
    char text[32];
    long value = 0;

    snprintf(text, sizeof(text), "%ld", LONG_MAX);
    assert(parse_long(text, &value));
    assert(value == LONG_MAX);

    snprintf(text, sizeof(text), "%ld", LONG_MIN);
    assert(parse_long(text, &value));
    assert(value == LONG_MIN);
}

static void test_parse_out_of_range(void)
{
    long value = 0;

    assert(!parse_long("99999999999999999999999999", &value));
    assert(!parse_long("-99999999999999999999999999", &value));
}

static void test_overwrites_previous_values(void)
{
    char* argv[] = {
        "task",
        "1",
        "2"
    };

    size_t count = 777;
    long sum = 777;
    long min = -777;
    long max = 777;

    assert(analyze_args(3, argv, &count, &sum, &min, &max));

    assert(count == 2);
    assert(sum == 3);
    assert(min == 1);
    assert(max == 2);
}

static void test_single_long_max(void)
{
    char text[32];
    char* argv[] = {
        "task",
        text
    };

    size_t count = 0;
    long sum = 0;
    long min = 0;
    long max = 0;

    snprintf(text, sizeof(text), "%ld", LONG_MAX);

    assert(analyze_args(2, argv, &count, &sum, &min, &max));

    assert(count == 1);
    assert(sum == LONG_MAX);
    assert(min == LONG_MAX);
    assert(max == LONG_MAX);
}

static void test_single_long_min(void)
{
    char text[32];
    char* argv[] = {
        "task",
        text
    };

    size_t count = 0;
    long sum = 0;
    long min = 0;
    long max = 0;

    snprintf(text, sizeof(text), "%ld", LONG_MIN);

    assert(analyze_args(2, argv, &count, &sum, &min, &max));

    assert(count == 1);
    assert(sum == LONG_MIN);
    assert(min == LONG_MIN);
    assert(max == LONG_MIN);
}

static void test_invalid_last_argument(void)
{
    char* argv[] = {
        "task",
        "1",
        "2",
        "3x"
    };

    size_t count = 0;
    long sum = 0;
    long min = 0;
    long max = 0;

    assert(!analyze_args(4, argv, &count, &sum, &min, &max));
}

static void test_out_of_range_argument(void)
{
    char* argv[] = {
        "task",
        "1",
        "99999999999999999999999999"
    };

    size_t count = 0;
    long sum = 0;
    long min = 0;
    long max = 0;

    assert(!analyze_args(3, argv, &count, &sum, &min, &max));
}

int main(void)
{
    test_parse_positive();
    test_parse_negative();
    test_parse_zero();
    test_parse_invalid_letters();
    test_parse_invalid_suffix();
    test_parse_empty();

    test_analyze();
    test_single();
    test_invalid_argument();
    test_no_numbers();

    test_parse_invalid_trailing_space();
    test_parse_invalid_only_sign();
    test_parse_invalid_fraction();
    test_parse_limits();
    test_parse_out_of_range();
    test_overwrites_previous_values();
    test_single_long_max();
    test_single_long_min();
    test_invalid_last_argument();
    test_out_of_range_argument();

    puts("All tests passed");
    return 0;
}
