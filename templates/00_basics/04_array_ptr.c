/*
# Task 4 — Pointer walk

Дан массив целых чисел.

Нужно найти:

- сумму элементов;
- минимальный элемент;
- максимальный элемент.

## Requirements

- Реализовать функцию `analyze_ptr`.
- Нельзя использовать индексацию `arr[i]`.
- Нельзя использовать отдельный индекс `i`.
- Массив нужно обходить только указателями.
- Можно использовать:
    - `ptr`
    - `ptr++`
    - `ptr + size`
    - `*ptr`
    - сравнение указателей
- Массив не изменять.
- Гарантируется, что `size > 0`.

## Interface

void analyze_ptr(const int *arr,
                 size_t size,
                 int *min,
                 int *max,
                 long long *sum);
*/

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

void analyze_ptr(const int* arr,
    size_t size,
    int* min,
    int* max,
    long long* sum)
{
    /* TODO: реализуйте analyze_ptr. */
    (void)arr;
    (void)size;
    (void)min;
    (void)max;
    (void)sum;
    assert(!"TODO: analyze_ptr");
}

#ifndef TEST

int main(void)
{
    int values[] = { 3, -2, 7, -5, 10 };

    int min = 0;
    int max = 0;
    long long sum = 0;

    size_t size = sizeof(values) / sizeof(values[0]);

    analyze_ptr(values, size, &min, &max, &sum);

    printf("min: %d\n", min);
    printf("max: %d\n", max);
    printf("sum: %lld\n", sum);

    return 0;
}

#else

static void test_single(void)
{
    int values[] = { 42 };

    int min = 0;
    int max = 0;
    long long sum = 0;

    analyze_ptr(values, 1, &min, &max, &sum);

    assert(min == 42);
    assert(max == 42);
    assert(sum == 42);
}

static void test_mixed(void)
{
    int values[] = { 3, -2, 7, -5, 10 };

    int min = 0;
    int max = 0;
    long long sum = 0;

    analyze_ptr(values, 5, &min, &max, &sum);

    assert(min == -5);
    assert(max == 10);
    assert(sum == 13);
}

static void test_negative(void)
{
    int values[] = { -4, -1, -7, -2 };

    int min = 0;
    int max = 0;
    long long sum = 0;

    analyze_ptr(values, 4, &min, &max, &sum);

    assert(min == -7);
    assert(max == -1);
    assert(sum == -14);
}

static void test_overwrites_previous_values(void)
{
    int values[] = { 1, -1, 0 };

    int min = INT_MIN;
    int max = INT_MAX;
    long long sum = 777;

    analyze_ptr(values, 3, &min, &max, &sum);

    assert(min == -1);
    assert(max == 1);
    assert(sum == 0);
}

static void test_descending(void)
{
    int values[] = { 9, 4, 1, -3 };

    int min = 0;
    int max = 0;
    long long sum = 0;

    analyze_ptr(values, 4, &min, &max, &sum);

    assert(min == -3);
    assert(max == 9);
    assert(sum == 11);
}

static void test_int_limits(void)
{
    int values[] = { INT_MAX, 0, INT_MIN };

    int min = 0;
    int max = 0;
    long long sum = 0;

    analyze_ptr(values, 3, &min, &max, &sum);

    assert(min == INT_MIN);
    assert(max == INT_MAX);
    assert(sum == -1);
}

static void test_sum_larger_than_int(void)
{
    int values[] = { INT_MAX, INT_MAX, INT_MAX };

    int min = 0;
    int max = 0;
    long long sum = 0;

    analyze_ptr(values, 3, &min, &max, &sum);

    assert(min == INT_MAX);
    assert(max == INT_MAX);
    assert(sum == 3LL * INT_MAX);
}

int main(void)
{
    test_single();
    test_mixed();
    test_negative();

    test_overwrites_previous_values();
    test_descending();
    test_int_limits();
    test_sum_larger_than_int();

    puts("All tests passed");
    return 0;
}

#endif
