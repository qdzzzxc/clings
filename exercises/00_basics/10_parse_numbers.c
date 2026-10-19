/*
# Task 10 — Numbers in a string

`strtol` не только переводит строку в число, но и сообщает через
`endptr`, где число закончилось. Так по строке можно идти от числа
к числу, не разбирая её вручную.

С основанием 0 `strtol` сам понимает запись числа, как в C:
"42" — десятичное, "0x1F" — шестнадцатеричное, "017" — восьмеричное.

## Нужно реализовать функции

sum_numbers_in_string:
    Строка — целые числа, разделённые запятыми и пробельными символами:
    "12, 0x1F, -7". Записывает сумму в `*sum` и количество чисел
    в `*count`. Пустая строка и строка из одних разделителей — успех
    с нулями.
    "12, 0x1F, -7"  ->  sum = 36, count = 3

format_list:
    Обратная операция: записывает числа массива в `buffer` через ", ":
    { 1, -2, 3 }  ->  "1, -2, 3". Для пустого массива — пустая строка.
    `size` — размер буфера. Возвращает 1, если строка поместилась
    целиком, и 0, если нет. В обоих случаях в буфере корректная строка
    с '\0', за границу буфера писать нельзя.

## Requirements

- `sum_numbers_in_string`: разделители пропускать через `strspn`,
  числа читать через `strtol(p, &end, 0)`.
- Ошибка (вернуть 0), если на месте числа не число (`end == p`),
  если число не помещается в `long` (`errno == ERANGE`, перед вызовом
  обнулить `errno`) или если сразу после числа не разделитель и не конец
  строки: "12abc" — ошибка.
- При ошибке `*sum` и `*count` не меняются.
- `format_list` дописывает числа через `snprintf`: он возвращает,
  сколько символов записал бы при достаточном буфере, — так видно,
  что место кончилось.
- Гарантируется, что `size > 0`.

## Interfaces

int sum_numbers_in_string(const char *s, long *sum, size_t *count);
int format_list(char *buffer, size_t size, const int *values, size_t count);

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
#include <string.h>

int sum_numbers_in_string(const char* s, long* sum, size_t* count)
{
    static const char space_symbols[] = ", \t\n\r\v\f";

    size_t local_count = 0;
    long local_sum = 0;

    while (1) {
        size_t space_count = strspn(s, space_symbols);
        s += space_count;

        if (*s == '\0') {
            *count = local_count;
            *sum = local_sum;

            return 1;
        }

        char* endptr = NULL;
        errno = 0;
        long num = strtol(s, &endptr, 0);

        if ((errno == ERANGE) || (s == endptr) || (strchr(space_symbols, *endptr) == NULL)) {
            return 0;
        }
        s = endptr;

        if (((num >= 0) && (local_sum > LONG_MAX - num)) || ((num < 0) && (local_sum < LONG_MIN - num))) {
            return 0;
        }
        local_count++;
        local_sum += num;
    }
}

int format_list(char* buffer, size_t size, const int* values, size_t count)
{
    size_t pos = 0;
    buffer[0] = '\0';

    for (size_t i = 0; i < count; i++) {
        int n = snprintf(buffer + pos, size - pos, i == 0 ? "%d" : ", %d", values[i]);

        if ((n < 0) || ((size_t)n >= size - pos)) {
            return 0;
        }
        pos += (size_t)n;
    }
    return 1;
}

int main(void)
{
    long sum = 0;
    size_t count = 0;
    int values[] = { 1, -2, 3 };
    char buffer[32] = "";

    if (sum_numbers_in_string("12, 0x1F, -7", &sum, &count)) {
        printf("sum: %ld, count: %zu\n", sum, count);
    }
    if (format_list(buffer, sizeof(buffer), values, 3)) {
        printf("list: %s\n", buffer);
    }
    return 0;
}
