/*
# Task 5 — File as an array

Двоичный файл из чисел `int`, записанных подряд, можно читать как массив,
не загружая его в память целиком: элемент с номером `i` лежит со смещения
`i * sizeof(int)` байт. До него можно сразу «перепрыгнуть» через `fseek`.

Все функции получают уже открытый файл в режиме "r+b" (или "w+b").

## Нужно реализовать функции

file_int_count:
    Количество чисел в файле. Узнать размер файла через
    `fseek(file, 0, SEEK_END)` и `ftell`. Если размер не делится
    на `sizeof(int)` или произошла ошибка — вернуть -1.

file_get:
    Читает элемент номер `index` в `*value`.

file_set:
    Записывает `value` на место элемента номер `index`.
    Файл не растёт: записывать можно только в существующие элементы.

file_reverse:
    Разворачивает числа в файле, как массив: первое меняется
    с последним, второе — с предпоследним и так далее.

## Requirements

- Не читать файл целиком в память: каждая функция работает
  с одним-двумя элементами за раз через `fseek` + `fread`/`fwrite`.
- `file_get` и `file_set` возвращают 0, если `index` вне файла
  (отрицательный или не меньше количества) или чтение/запись не удались.
- Между чтением и записью в одном и том же файле обязателен `fseek`
  (или `fflush`): иначе стандарт не гарантирует результат.
  Если каждая операция начинается с `fseek`, это выполняется само.
- `file_reverse` — двумя индексами навстречу друг другу, через
  `file_get` и `file_set`.

## Interfaces

long file_int_count(FILE *file);
int file_get(FILE *file, long index, int *value);
int file_set(FILE *file, long index, int value);
int file_reverse(FILE *file);

Возвращаемое значение `file_get`, `file_set` и `file_reverse`:

1 — успех
0 — ошибка
*/

#include <assert.h>
#include <stdio.h>

long file_int_count(FILE* file)
{
    /* TODO: реализуйте file_int_count. */
    (void)file;
    assert(!"TODO: file_int_count");
    return -1;
}

int file_get(FILE* file, long index, int* value)
{
    /* TODO: реализуйте file_get. */
    (void)file;
    (void)index;
    (void)value;
    assert(!"TODO: file_get");
    return 0;
}

int file_set(FILE* file, long index, int value)
{
    /* TODO: реализуйте file_set. */
    (void)file;
    (void)index;
    (void)value;
    assert(!"TODO: file_set");
    return 0;
}

int file_reverse(FILE* file)
{
    /* TODO: реализуйте file_reverse. */
    (void)file;
    assert(!"TODO: file_reverse");
    return 0;
}

int main(void)
{
    FILE* file = tmpfile();
    int values[] = { 10, 20, 30, 40 };
    int value = 0;

    if (file == NULL || fwrite(values, sizeof(int), 4, file) != 4) {
        return 1;
    }

    printf("count: %ld\n", file_int_count(file));
    file_set(file, 1, 25);
    file_reverse(file);
    for (long i = 0; file_get(file, i, &value); i++) {
        printf("%d\n", value);
    }
    fclose(file);
    return 0;
}
