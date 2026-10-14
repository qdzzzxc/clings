/*
# Task 8 — Array algorithms

Классические алгоритмы над массивами целых чисел.

## Нужно реализовать функции

is_sorted:
    Возвращает 1, если массив упорядочен по неубыванию (равные соседи
    допустимы), иначе 0. Пустой массив и массив из одного элемента
    упорядочены.

unique_sorted:
    Массив отсортирован. Удаляет повторы на месте: в начале массива
    остаются различные значения в том же порядке. Возвращает их
    количество. Что лежит в массиве после этих элементов — неважно.
    1 1 2 3 3 3 -> 1 2 3, вернуть 3

merge_sorted:
    Сливает два отсортированных массива в `out` так, чтобы результат
    тоже был отсортирован. Возвращает a_size + b_size.
    a = 1 4 9, b = 2 4 5  ->  out = 1 2 4 4 5 9

max_subarray:
    Наибольшая сумма непустого непрерывного куска массива.
    -2 1 -3 4 -1 2 1 -5 4  ->  6 (кусок 4 -1 2 1)
    Если все числа отрицательные — это наибольшее из них.
    Гарантируется, что size > 0.

## Requirements

- Каждая функция работает за один проход: O(size) или O(a_size + b_size).
  Без вложенных циклов и без сортировки.
- `unique_sorted` — двумя индексами (или указателями): один читает,
  другой показывает, куда писать следующее новое значение.
- `merge_sorted` — двумя индексами, по одному на каждый массив.
  `out` вмещает a_size + b_size элементов.
- В `max_subarray` сумма считается в `long long`. Подсказка: для каждой
  позиции помнить лучшую сумму куска, который на ней заканчивается.
- Тесты ограничены по времени.

## Interfaces

int is_sorted(const int *arr, size_t size);
size_t unique_sorted(int *arr, size_t size);
size_t merge_sorted(const int *a, size_t a_size,
                    const int *b, size_t b_size, int *out);
long long max_subarray(const int *arr, size_t size);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

int is_sorted(const int* arr, size_t size)
{
    if (size <= 1) {
        return 1;
    }

    const int* slow = arr;
    const int* fast = arr + 1;
    const int* const end = arr + size;

    while (fast < end) {
        if (*slow > *fast) {
            return 0;
        }
        slow++;
        fast++;
    }

    return 1;
}

size_t unique_sorted(int* arr, size_t size)
{
    if (size == 0) {
        return 0;
    }
    size_t counter = 1;
    int* slow = arr;
    const int* fast = arr + 1;
    const int* const end = arr + size;

    while (fast < end) {
        if (*slow != *fast) {
            slow++;
            *slow = *fast;
            counter += 1;
        }

        fast++;
    }

    return counter;
}

size_t merge_sorted(const int* a, size_t a_size,
    const int* b, size_t b_size, int* out)
{
    const int* a_ptr = a;
    const int* const a_end = a + a_size;
    const int* b_ptr = b;
    const int* const b_end = b + b_size;
    int* out_ptr = out;

    while (1) {
        if (a_ptr == a_end) {
            while (b_ptr != b_end) {
                *out_ptr = *b_ptr;
                b_ptr++;
                out_ptr++;
            }
            break;
        }

        if (b_ptr == b_end) {
            while (a_ptr != a_end) {
                *out_ptr = *a_ptr;
                a_ptr++;
                out_ptr++;
            }
            break;
        }

        if (*a_ptr <= *b_ptr) {
            *out_ptr = *a_ptr;
            a_ptr++;
        } else {
            *out_ptr = *b_ptr;
            b_ptr++;
        }
        out_ptr++;
    }

    return a_size + b_size;
}

long long max_subarray(const int* arr, size_t size)
{
    long long minimum_prefix_sum = 0;
    long long prefix_sum = 0;
    long long maximum_result = arr[0];

    for (size_t i = 0; i < size; i++) {
        prefix_sum += arr[i];
        maximum_result = ((prefix_sum - minimum_prefix_sum) > maximum_result) ? (prefix_sum - minimum_prefix_sum) : maximum_result;
        minimum_prefix_sum = (prefix_sum < minimum_prefix_sum) ? prefix_sum : minimum_prefix_sum;
    }

    return maximum_result;
}

int main(void)
{
    int sorted[] = { 1, 1, 2, 3, 3, 3 };
    int a[] = { 1, 4, 9 };
    int b[] = { 2, 4, 5 };
    int merged[6] = { 0 };
    int mixed[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    size_t unique = 0;

    printf("sorted: %d\n", is_sorted(sorted, 6));

    unique = unique_sorted(sorted, 6);
    printf("unique:");
    for (size_t i = 0; i < unique; i++) {
        printf(" %d", sorted[i]);
    }
    printf("\n");

    merge_sorted(a, 3, b, 3, merged);
    printf("merged:");
    for (size_t i = 0; i < 6; i++) {
        printf(" %d", merged[i]);
    }
    printf("\n");

    printf("max subarray: %lld\n", max_subarray(mixed, 9));
    return 0;
}
