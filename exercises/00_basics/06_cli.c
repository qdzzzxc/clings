/*
# Task 6 — CLI statistics

Программа получает целые числа через аргументы командной строки.

## Example

Запуск:

./task 10 -3 7 5

Output:

count: 4
sum: 19
min: -3
max: 10

## Requirements

- Использовать `argc` и `argv`.
- `argv[0]` — имя программы, числовые аргументы начинаются с `argv[1]`.
- Для преобразования строки в число использовать `strtol`.
- Не использовать `atoi`.
- Проверять, что строка целиком является корректным числом.

Например:

"123"    -> корректно
"-42"    -> корректно
"12abc"  -> ошибка
"abc"    -> ошибка

- Если числовых аргументов нет — вернуть ошибку.
- Если хотя бы один аргумент некорректный — вернуть ошибку.
- Число, которое не помещается в `long`, тоже ошибка: `strtol` сообщает
  об этом через `errno == ERANGE`.
- Реализовать `parse_long`, которая преобразует одну строку.
- Реализовать `analyze_args`, которая обрабатывает массив аргументов.
- `analyze_args` не должна ничего печатать.
- Печать выполняется только в `main`.

## Interfaces

int parse_long(const char *str, long *value);

int analyze_args(int argc,
                 char **argv,
                 size_t *count,
                 long *sum,
                 long *min,
                 long *max);

Возвращаемое значение:

1 — успех
0 — ошибка
*/

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int parse_long(const char* str, long* value)
{
    /* TODO: реализуйте parse_long. */
    (void)str;
    (void)value;
    assert(!"TODO: parse_long");
    return 0;
}

int analyze_args(int argc,
    char** argv,
    size_t* count,
    long* sum,
    long* min,
    long* max)
{
    /* TODO: реализуйте analyze_args. */
    (void)argc;
    (void)argv;
    (void)count;
    (void)sum;
    (void)min;
    (void)max;
    assert(!"TODO: analyze_args");
    return 0;
}

#ifndef TEST

int main(int argc, char** argv)
{
    size_t count = 0;
    long sum = 0;
    long min = 0;
    long max = 0;

    if (!analyze_args(argc, argv, &count, &sum, &min, &max)) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }

    printf("count: %zu\n", count);
    printf("sum: %ld\n", sum);
    printf("min: %ld\n", min);
    printf("max: %ld\n", max);

    return 0;
}

#else

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

#endif
