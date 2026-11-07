/*
# Task 4 — Sorts

Четыре сортировки по возрастанию, на месте. Алгоритмы известные;
в C в них свои ловушки: индексы типа `size_t` не бывают
отрицательными, а вспомогательную память надо выделить и освободить.

## Нужно реализовать функции

insertion_sort:
    Сортировка вставками. O(size^2), но быстрая на почти
    отсортированных массивах. Устойчивая.

merge_sort:
    Сортировка слиянием. O(size log size) всегда. Устойчивая.
    Возвращает 1, или 0, если не хватило памяти (массив тогда
    не меняется).

quick_sort:
    Быстрая сортировка. O(size log size) в среднем, без доп. памяти.

counting_sort:
    Сортировка подсчётом. Все числа в диапазоне [0, max_value].
    O(size + max_value). Возвращает 1, или 0, если не хватило памяти.

## Requirements

- `insertion_sort`: цикл вида `for (size_t j = i - 1; j >= 0; j--)`
  бесконечный: `size_t` всегда >= 0, а 0 - 1 — это SIZE_MAX.
  Сдвигай, пока `j > 0 && arr[j - 1] > key`.
- `merge_sort`: один буфер на `size` элементов через `malloc` на весь
  вызов (а не на каждое слияние), рекурсия во вспомогательной
  `static`-функции, `free` в конце.
- `quick_sort`: опорный элемент — средний, `arr[(size - 1) / 2]`,
  разбиение Хоара двумя индексами навстречу; потом рекурсия на
  `arr[0..j]` и `arr[j+1..size-1]`. Именно нижняя середина: с
  `arr[size / 2]` на массиве { 1, 2 } левая часть получается снова
  длины 2, и рекурсия не кончается. На уже отсортированном массиве
  первый элемент в роли опорного даёт O(size^2) и глубину рекурсии
  size, а разбиение Ломуто — то же на массиве из одинаковых чисел.
  Индекс `j` идёт вниз: следи, чтобы `size_t` не ушёл ниже 0.
- `counting_sort`: массив счётчиков на `max_value + 1` элементов
  через `calloc`, `free` в конце.
- Для пустого массива функции ничего не делают (и возвращают 1).
- Тесты ограничены по времени: сортировка вставками проверяется
  на маленьких массивах, остальные — на полумиллионе элементов.

## Interfaces

void insertion_sort(int *arr, size_t size);
int merge_sort(int *arr, size_t size);
void quick_sort(int *arr, size_t size);
int counting_sort(int *arr, size_t size, int max_value);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertion_sort(int* arr, size_t size)
{
    /* TODO: реализуйте insertion_sort. */
    (void)arr;
    (void)size;
    assert(!"TODO: insertion_sort");
}

int merge_sort(int* arr, size_t size)
{
    /* TODO: реализуйте merge_sort. */
    (void)arr;
    (void)size;
    assert(!"TODO: merge_sort");
    return 0;
}

void quick_sort(int* arr, size_t size)
{
    /* TODO: реализуйте quick_sort. */
    (void)arr;
    (void)size;
    assert(!"TODO: quick_sort");
}

int counting_sort(int* arr, size_t size, int max_value)
{
    /* TODO: реализуйте counting_sort. */
    (void)arr;
    (void)size;
    (void)max_value;
    assert(!"TODO: counting_sort");
    return 0;
}

static void print(const int* arr, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    int a[] = { 5, 2, 9, 1, 5, 6 };
    int b[] = { 5, 2, 9, 1, 5, 6 };
    int c[] = { 5, 2, 9, 1, 5, 6 };
    int d[] = { 5, 2, 9, 1, 5, 6 };

    insertion_sort(a, 6);
    print(a, 6);
    merge_sort(b, 6);
    print(b, 6);
    quick_sort(c, 6);
    print(c, 6);
    counting_sort(d, 6, 9);
    print(d, 6);
    return 0;
}
