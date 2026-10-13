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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum_numbers_in_string(const char* s, long* sum, size_t* count)
{
    /* TODO: реализуйте sum_numbers_in_string. */
    (void)s;
    (void)sum;
    (void)count;
    assert(!"TODO: sum_numbers_in_string");
    return 0;
}

int format_list(char* buffer, size_t size, const int* values, size_t count)
{
    /* TODO: реализуйте format_list. */
    (void)buffer;
    (void)size;
    (void)values;
    (void)count;
    assert(!"TODO: format_list");
    return 0;
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
