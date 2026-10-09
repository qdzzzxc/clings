/*
# Task 2 — Function pointers

Указатель на функцию позволяет передать в функцию поведение: что именно
делать с каждым элементом, какие элементы считать, как объединять значения.

## Нужно реализовать функции

map:
    Заменяет каждый элемент массива на `fn(элемент)`.

count_if:
    Считает элементы, для которых `predicate` вернул не ноль.

reduce:
    Сворачивает массив в одно значение слева направо:
    result = initial;
    result = op(result, arr[0]);
    result = op(result, arr[1]);
    ...
    Для пустого массива возвращает `initial`.

operation_by_symbol:
    Возвращает указатель на функцию для символа операции:
    '+' — сложение, '-' — вычитание, '*' — умножение.
    Для остальных символов возвращает NULL.

calculate:
    Вычисляет `a <symbol> b` через `operation_by_symbol` и записывает
    ответ в `*result`. Для неизвестной операции возвращает 0
    и не меняет `*result`.

## Requirements

- Сами функции сложения, вычитания и умножения нужно написать
  в этом файле и сделать их `static`.
- В `calculate` не дублировать разбор символа: только вызвать
  `operation_by_symbol` и проверить результат.

## Interfaces

typedef int (*UnaryFn)(int value);
typedef int (*Predicate)(int value);
typedef int (*BinaryFn)(int left, int right);

void map(int *arr, size_t size, UnaryFn fn);
size_t count_if(const int *arr, size_t size, Predicate predicate);
int reduce(const int *arr, size_t size, int initial, BinaryFn op);
BinaryFn operation_by_symbol(char symbol);
int calculate(int a, char symbol, int b, int *result);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

typedef int (*UnaryFn)(int value);
typedef int (*Predicate)(int value);
typedef int (*BinaryFn)(int left, int right);

void map(int* arr, size_t size, UnaryFn fn)
{
    /* TODO: реализуйте map. */
    (void)arr;
    (void)size;
    (void)fn;
    assert(!"TODO: map");
}

size_t count_if(const int* arr, size_t size, Predicate predicate)
{
    /* TODO: реализуйте count_if. */
    (void)arr;
    (void)size;
    (void)predicate;
    assert(!"TODO: count_if");
    return 0;
}

int reduce(const int* arr, size_t size, int initial, BinaryFn op)
{
    /* TODO: реализуйте reduce. */
    (void)arr;
    (void)size;
    (void)initial;
    (void)op;
    assert(!"TODO: reduce");
    return 0;
}

BinaryFn operation_by_symbol(char symbol)
{
    /* TODO: реализуйте operation_by_symbol. */
    (void)symbol;
    assert(!"TODO: operation_by_symbol");
    return NULL;
}

int calculate(int a, char symbol, int b, int* result)
{
    /* TODO: реализуйте calculate. */
    (void)a;
    (void)symbol;
    (void)b;
    (void)result;
    assert(!"TODO: calculate");
    return 0;
}

static int twice(int value)
{
    return value * 2;
}

int main(void)
{
    int values[] = { 1, 2, 3, 4 };
    int result = 0;

    map(values, 4, twice);
    printf("%d %d %d %d\n", values[0], values[1], values[2], values[3]);

    if (calculate(6, '*', 7, &result)) {
        printf("6 * 7 = %d\n", result);
    }
    return 0;
}
