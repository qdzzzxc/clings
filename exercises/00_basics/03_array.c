/*
# Task 3 — Array statistics

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
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

void analyze(const int* arr,
    size_t size,
    int* min,
    int* max,
    long long* sum,
    size_t* positive,
    size_t* negative,
    size_t* zeros)
{
    /* TODO: реализуйте analyze. */
    (void)arr;
    (void)size;
    (void)min;
    (void)max;
    (void)sum;
    (void)positive;
    (void)negative;
    (void)zeros;
    assert(!"TODO: analyze");
}

int main(void)
{
    int values[] = { 3, -2, 0, 7, -5, 0, 10 };

    int min = INT_MAX;
    int max = INT_MIN;
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
