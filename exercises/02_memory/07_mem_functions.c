/*
# Task 7 — mem functions and void*

Функции из `string.h`, которые работают с памятью побайтно, а не со
строками: им всё равно, что лежит в памяти, и '\0' для них не конец.

- `memcpy(dst, src, n)` — скопировать n байт. Области не должны
  перекрываться, иначе поведение не определено (ASan это ловит).
- `memmove(dst, src, n)` — то же, но области могут перекрываться.
- `memset(p, byte, n)` — заполнить n байт одним значением.
- `calloc(count, size)` — как `malloc(count * size)`, но память
  обнулена, а переполнение `count * size` проверяется за тебя.

`void *` — указатель на что угодно. Разыменовать его и прибавлять
к нему число нельзя: неизвестен размер элемента. Для арифметики его
приводят к `unsigned char *` и считают в байтах.

## Нужно реализовать функции

insert_at:
    В массиве `size` элементов, места хватает на `size + 1`.
    Вставляет `value` на позицию `index` (0 <= index <= size),
    остальные сдвигаются вправо.
    1 2 4, index 2, value 3  ->  1 2 3 4

remove_at:
    Удаляет элемент с позиции `index` (index < size), остальные
    сдвигаются влево. Что окажется в последней ячейке — неважно.

duplicate:
    Возвращает копию массива в новой памяти. Результат освобождает
    вызывающий код. Если память не выделилась — NULL.
    Гарантируется, что size > 0.

zeros:
    Возвращает новый массив из `count` нулей. Если память не
    выделилась — NULL. Гарантируется, что count > 0.

swap_bytes:
    Меняет местами содержимое двух объектов по `size` байт.
    Работает для любого типа: int, double, структуры.

reverse_any:
    Разворачивает массив из `count` элементов по `size` байт каждый,
    как `qsort` не зная типа элементов.

## Requirements

- Сдвиги в `insert_at` и `remove_at` — одним вызовом `memmove`,
  без цикла. `memcpy` тут не годится: области перекрываются.
- `duplicate` — `malloc` и `memcpy`, `zeros` — `calloc`.
- `swap_bytes` не выделяет память: меняет байты по одному через
  `unsigned char *`.
- `reverse_any` двумя индексами навстречу, через `swap_bytes`.
  Адрес i-го элемента: `(unsigned char *)base + i * size`.
- Размер массива всегда передаётся отдельно. В параметре `int arr[]`
  на самом деле лежит указатель, и `sizeof(arr)` внутри функции —
  размер указателя (8), а не массива.

## Interfaces

void insert_at(int *arr, size_t size, size_t index, int value);
void remove_at(int *arr, size_t size, size_t index);
int *duplicate(const int *src, size_t size);
int *zeros(size_t count);
void swap_bytes(void *a, void *b, size_t size);
void reverse_any(void *base, size_t count, size_t size);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_at(int* arr, size_t size, size_t index, int value)
{
    /* TODO: реализуйте insert_at. */
    (void)arr;
    (void)size;
    (void)index;
    (void)value;
    assert(!"TODO: insert_at");
}

void remove_at(int* arr, size_t size, size_t index)
{
    /* TODO: реализуйте remove_at. */
    (void)arr;
    (void)size;
    (void)index;
    assert(!"TODO: remove_at");
}

int* duplicate(const int* src, size_t size)
{
    /* TODO: реализуйте duplicate. */
    (void)src;
    (void)size;
    assert(!"TODO: duplicate");
    return NULL;
}

int* zeros(size_t count)
{
    /* TODO: реализуйте zeros. */
    (void)count;
    assert(!"TODO: zeros");
    return NULL;
}

void swap_bytes(void* a, void* b, size_t size)
{
    /* TODO: реализуйте swap_bytes. */
    (void)a;
    (void)b;
    (void)size;
    assert(!"TODO: swap_bytes");
}

void reverse_any(void* base, size_t count, size_t size)
{
    /* TODO: реализуйте reverse_any. */
    (void)base;
    (void)count;
    (void)size;
    assert(!"TODO: reverse_any");
}

int main(void)
{
    int arr[5] = { 1, 2, 4, 5 };
    double values[] = { 1.5, 2.5, 3.5 };

    insert_at(arr, 4, 2, 3);
    remove_at(arr, 5, 0);
    for (size_t i = 0; i < 4; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    reverse_any(values, 3, sizeof(values[0]));
    printf("%.1f %.1f %.1f\n", values[0], values[1], values[2]);
    return 0;
}
