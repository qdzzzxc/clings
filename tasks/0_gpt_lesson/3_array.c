/*
# Task 4 — Array statistics

Дан массив целых чисел.

Нужно найти:

- минимальный элемент;
- максимальный элемент;
- сумму элементов;
- количество положительных элементов;
- количество отрицательных элементов;
- количество нулей.

## Requirements

- Реализовать функцию `analyze`.
- Массив передавать в функцию вместе с его размером.
- Использовать обычный цикл `for`.
- Индексацию `arr[i]` использовать можно.
- Массив внутри функции не изменять.
- Результаты вернуть через указатели.
- Дополнительные массивы не использовать.
- Гарантируется, что `size > 0`.

## Interface

void analyze(const int *arr,
             size_t size,
             int *min,
             int *max,
             long long *sum,
             size_t *positive,
             size_t *negative,
             size_t *zeros);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

void analyze(const int *arr,
    size_t size,
    int *min,
    int *max,
    long long *sum,
    size_t *positive,
    size_t *negative,
    size_t *zeros)
{
    /* TODO */
}

#ifndef TEST

int main(void)
{
    int values[] = {3, -2, 0, 7, -5, 0, 10};

    int min = 0;
    int max = 0;
    long long sum = 0;

    size_t positive = 0;
    size_t negative = 0;
    size_t zeros = 0;

    size_t size = sizeof(values) / sizeof(values[0]);

    analyze(values,
        size,
        &min,
        &max,
        &sum,
        &positive,
        &negative,
        &zeros);

    printf("min: %d\n", min);
    printf("max: %d\n", max);
    printf("sum: %lld\n", sum);
    printf("positive: %zu\n", positive);
    printf("negative: %zu\n", negative);
    printf("zeros: %zu\n", zeros);

    return 0;
}

#else

static void test_single_positive(void)
{
    int values[] = {5};

    int min = 0;
    int max = 0;
    long long sum = 0;

    size_t positive = 0;
    size_t negative = 0;
    size_t zeros = 0;

    analyze(values, 1, &min, &max, &sum, &positive, &negative, &zeros);

    assert(min == 5);
    assert(max == 5);
    assert(sum == 5);
    assert(positive == 1);
    assert(negative == 0);
    assert(zeros == 0);
}

static void test_mixed(void)
{
    int values[] = {3, -2, 0, 7, -5, 0, 10};

    int min = 0;
    int max = 0;
    long long sum = 0;

    size_t positive = 0;
    size_t negative = 0;
    size_t zeros = 0;

    analyze(values, 7, &min, &max, &sum, &positive, &negative, &zeros);

    assert(min == -5);
    assert(max == 10);
    assert(sum == 13);
    assert(positive == 3);
    assert(negative == 2);
    assert(zeros == 2);
}

static void test_all_negative(void)
{
    int values[] = {-4, -1, -7, -2};

    int min = 0;
    int max = 0;
    long long sum = 0;

    size_t positive = 0;
    size_t negative = 0;
    size_t zeros = 0;

    analyze(values, 4, &min, &max, &sum, &positive, &negative, &zeros);

    assert(min == -7);
    assert(max == -1);
    assert(sum == -14);
    assert(positive == 0);
    assert(negative == 4);
    assert(zeros == 0);
}

static void test_all_zero(void)
{
    int values[] = {0, 0, 0};

    int min = 0;
    int max = 0;
    long long sum = 0;

    size_t positive = 0;
    size_t negative = 0;
    size_t zeros = 0;

    analyze(values, 3, &min, &max, &sum, &positive, &negative, &zeros);

    assert(min == 0);
    assert(max == 0);
    assert(sum == 0);
    assert(positive == 0);
    assert(negative == 0);
    assert(zeros == 3);
}

static void test_extremes_at_edges(void)
{
    int values[] = {-100, 3, 8, 2, 100};

    int min = 0;
    int max = 0;
    long long sum = 0;

    size_t positive = 0;
    size_t negative = 0;
    size_t zeros = 0;

    analyze(values, 5, &min, &max, &sum, &positive, &negative, &zeros);

    assert(min == -100);
    assert(max == 100);
    assert(sum == 13);
    assert(positive == 4);
    assert(negative == 1);
    assert(zeros == 0);
}

int main(void)
{
    test_single_positive();
    test_mixed();
    test_all_negative();
    test_all_zero();
    test_extremes_at_edges();

    puts("All tests passed");
    return 0;
}

#endif
