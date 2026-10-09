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
    *min = arr[0];
    *max = arr[0];

    *sum = 0;
    *positive = 0;
    *negative = 0;
    *zeros = 0;

    for (size_t i = 0; i < size; i++) {
        *sum += arr[i];

        if (arr[i] < *min) {
            *min = arr[i];
        }

        if (arr[i] > *max) {
            *max = arr[i];
        }

        if (arr[i] > 0) {
            *positive += 1;
        } else if (arr[i] == 0) {
            *zeros += 1;
        } else {
            *negative += 1;
        }
    }
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
