/*
# Task 3 — Binary file

Сохранить массив `int` в двоичный файл и прочитать его обратно.

## Формат файла

- сначала количество элементов — одно значение `uint32_t`;
- затем сами элементы типа `int`, подряд, без разделителей.

Массив из трёх элементов занимает 4 + 3 * sizeof(int) байт.

## Requirements

- Открывать файл в режимах "wb" и "rb".
- Писать через `fwrite`, читать через `fread` и проверять,
  сколько элементов они на самом деле обработали.
- Закрывать файл на всех путях, включая ошибки. Незакрытый файл
  тесты считают утечкой.
- `save_ints` возвращает 0, если файл не открылся или запись не удалась.
- `load_ints` возвращает 0, если файл не открылся, оборвался раньше времени
  или в нём больше элементов, чем `capacity`.
- При успехе `load_ints` записывает количество элементов в `*count`.

## Interfaces

int save_ints(const char *path, const int *values, size_t count);

int load_ints(const char *path, int *values, size_t capacity, size_t *count);

Возвращаемое значение:

1 — успех
0 — ошибка
*/

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int save_ints(const char* path, const int* values, size_t count)
{
    /* TODO: реализуйте save_ints. */
    (void)path;
    (void)values;
    (void)count;
    assert(!"TODO: save_ints");
    return 0;
}

int load_ints(const char* path, int* values, size_t capacity, size_t* count)
{
    /* TODO: реализуйте load_ints. */
    (void)path;
    (void)values;
    (void)capacity;
    (void)count;
    assert(!"TODO: load_ints");
    return 0;
}

int main(void)
{
    const char* path = ".build/numbers.bin";
    int values[] = { 10, -20, 30 };
    int loaded[8];
    size_t count = 0;

    if (!save_ints(path, values, 3) || !load_ints(path, loaded, 8, &count)) {
        fprintf(stderr, "File error\n");
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%d\n", loaded[i]);
    }
    return 0;
}
