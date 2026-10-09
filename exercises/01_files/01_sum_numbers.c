/*
# Task 1 — Sum numbers

В потоке записаны целые числа, разделённые пробелами и переводами строк.
Нужно посчитать их количество и сумму.

## Example

Input:
10 20
-5

Результат: count = 3, sum = 25

## Requirements

- Читать числа через `fscanf` с форматом "%ld".
- Различать три результата `fscanf`:
    - 1   — число прочитано;
    - EOF — данные закончились;
    - 0   — встретилось что-то, что не является числом.
- Если встретилось не число — вернуть ошибку.
- Пустой поток и поток из одних пробелов — это успех: count = 0, sum = 0.

## Interface

int sum_numbers(FILE *in, size_t *count, long *sum);

Возвращаемое значение:

1 — успех
0 — ошибка
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

int sum_numbers(FILE* in, size_t* count, long* sum)
{
    /* TODO: реализуйте sum_numbers. */
    (void)in;
    (void)count;
    (void)sum;
    assert(!"TODO: sum_numbers");
    return 0;
}

int main(void)
{
    size_t count = 0;
    long sum = 0;

    if (!sum_numbers(stdin, &count, &sum)) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("count: %zu\nsum: %ld\n", count, sum);
    return 0;
}
