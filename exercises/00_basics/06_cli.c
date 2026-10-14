/*
# Task 6 — CLI statistics

Программа получает целые числа через аргументы командной строки.

## Example

Запуск:

./task 10 -3 7 5

Output:

count: 4
sum: 19
min: -3
max: 10

## Requirements

- Использовать `argc` и `argv`.
- `argv[0]` — имя программы, числовые аргументы начинаются с `argv[1]`.
- Для преобразования строки в число использовать `strtol`.
- Не использовать `atoi`.
- Проверять, что строка целиком является корректным числом.

Например:

"123"    -> корректно
"-42"    -> корректно
"12abc"  -> ошибка
"abc"    -> ошибка

- Если числовых аргументов нет — вернуть ошибку.
- Если хотя бы один аргумент некорректный — вернуть ошибку.
- Число, которое не помещается в `long`, тоже ошибка: `strtol` сообщает
  об этом через `errno == ERANGE`.
- Реализовать `parse_long`, которая преобразует одну строку.
- Реализовать `analyze_args`, которая обрабатывает массив аргументов.
- `analyze_args` не должна ничего печатать.
- Печать выполняется только в `main`.

## Interfaces

int parse_long(const char *str, long *value);

int analyze_args(int argc,
                 char **argv,
                 size_t *count,
                 long *sum,
                 long *min,
                 long *max);

Возвращаемое значение:

1 — успех
0 — ошибка
*/

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int parse_long(const char* str, long* value)
{
    char* endptr = NULL;
    errno = 0;

    long num = strtol(str, &endptr, 10);

    if ((errno == ERANGE) || (str == endptr) || (*endptr != '\0')) {
        return 0;
    } else {
        *value = num;
        return 1;
    }
}

int analyze_args(int argc,
    char** argv,
    size_t* count,
    long* sum,
    long* min,
    long* max)
{
    *sum = 0;
    *count = 0;
    *min = LONG_MAX;
    *max = LONG_MIN;

    for (int i = 1; i < argc; i++) {
        long value;
        int is_succes = parse_long(argv[i], &value);
        if (!is_succes) {
            return 0;
        }

        *sum += value;
        (*count)++;
        *min = (value < *min) ? value : *min;
        *max = (value > *max) ? value : *max;
    }

    if (!*count) {
        return 0;
    }

    return 1;
}

int main(int argc, char** argv)
{
    size_t count = 0;
    long sum = 0;
    long min = 0;
    long max = 0;

    if (!analyze_args(argc, argv, &count, &sum, &min, &max)) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }

    printf("count: %zu\n", count);
    printf("sum: %ld\n", sum);
    printf("min: %ld\n", min);
    printf("max: %ld\n", max);

    return 0;
}
