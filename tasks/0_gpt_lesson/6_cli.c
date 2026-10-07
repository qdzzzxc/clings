/*
# Task 7 — CLI statistics

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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int parse_long(const char *str, long *value)
{
    /* TODO */
}

int analyze_args(int argc,
    char **argv,
    size_t *count,
    long *sum,
    long *min,
    long *max)
{
    /* TODO */
}

#ifndef TEST

int main(int argc, char **argv)
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
    char *argv[] = {
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
    char *argv[] = {
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
    char *argv[] = {
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
    char *argv[] = {
        "task"
    };

    size_t count = 0;
    long sum = 0;
    long min = 0;
    long max = 0;

    assert(!analyze_args(1, argv, &count, &sum, &min, &max));
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

    puts("All tests passed");
    return 0;
}

#endif
