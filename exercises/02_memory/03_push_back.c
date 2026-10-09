/*
# Task 3 — Growing array

Массив в динамической памяти, который растёт по мере добавления элементов.
Его состояние — три значения: указатель `data`, количество элементов `size`
и ёмкость `capacity` (под сколько элементов выделена память).

Пустой массив: data == NULL, size == 0, capacity == 0.

## Нужно реализовать функции

push_back:
    Добавляет `value` в конец массива и возвращает актуальный указатель
    на данные.

read_ints:
    Читает из потока все целые числа до конца данных и возвращает их
    в новом массиве. Количество записывает в `*size`.
    Если чисел нет — возвращает NULL и `*size == 0`.

## Requirements

- Если места нет (`*size == *capacity`), `push_back` увеличивает ёмкость
  через `realloc`: с 0 до 1, дальше каждый раз вдвое.
- `realloc` может переместить данные, поэтому вызывающий код обязан
  пользоваться возвращённым указателем.
- Если `realloc` вернул NULL — вернуть NULL и не терять старый массив:
  `data`, `*size` и `*capacity` остаются прежними.
- `read_ints` заранее не знает, сколько чисел в потоке, и добавляет
  их через `push_back`. Чтение останавливается на первом же значении,
  которое не является числом.
- Память освобождает вызывающий код через `free`.

## Interfaces

int *push_back(int *data, size_t *size, size_t *capacity, int value);
int *read_ints(FILE *in, size_t *size);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int* push_back(int* data, size_t* size, size_t* capacity, int value)
{
    /* TODO: реализуйте push_back. */
    (void)data;
    (void)size;
    (void)capacity;
    (void)value;
    assert(!"TODO: push_back");
    return NULL;
}

int* read_ints(FILE* in, size_t* size)
{
    /* TODO: реализуйте read_ints. */
    (void)in;
    (void)size;
    assert(!"TODO: read_ints");
    return NULL;
}

int main(void)
{
    size_t size = 0;
    int* numbers = read_ints(stdin, &size);

    printf("read %zu numbers, reversed:\n", size);
    for (size_t i = size; i > 0; i--) {
        printf("%d\n", numbers[i - 1]);
    }

    free(numbers);
    return 0;
}
