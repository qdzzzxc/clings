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
    *min = arr[0];
    *max = arr[0];
    *sum = 0;

    const int* end = arr + size;

    while (arr < end) {
        *sum += *arr;

        if (*arr < *min) {
            *min = *arr;
        }

        if (*arr > *max) {
            *max = *arr;
        }

        arr++;
    }
}

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
