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
    /* TODO: реализуйте is_sorted. */
    (void)arr;
    (void)size;
    assert(!"TODO: is_sorted");
    return 0;
}

size_t unique_sorted(int* arr, size_t size)
{
    /* TODO: реализуйте unique_sorted. */
    (void)arr;
    (void)size;
    assert(!"TODO: unique_sorted");
    return 0;
}

size_t merge_sorted(const int* a, size_t a_size,
    const int* b, size_t b_size, int* out)
{
    /* TODO: реализуйте merge_sorted. */
    (void)a;
    (void)a_size;
    (void)b;
    (void)b_size;
    (void)out;
    assert(!"TODO: merge_sorted");
    return 0;
}

long long max_subarray(const int* arr, size_t size)
{
    /* TODO: реализуйте max_subarray. */
    (void)arr;
    (void)size;
    assert(!"TODO: max_subarray");
    return 0;
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
