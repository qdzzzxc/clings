/*
# Task 2 — String copies

Функции, которые создают новые строки в динамической памяти.

## Нужно реализовать функции

str_dup:
    Возвращает новую копию строки.

str_concat:
    Возвращает новую строку: сначала `a`, сразу за ней `b`.

str_repeat:
    Возвращает строку `s`, повторённую `times` раз.
    При `times == 0` возвращает пустую строку "", а не NULL.

## Requirements

- Память выделять через `malloc`. Не использовать `strdup`.
- Выделять ровно столько, сколько нужно: длина строки плюс '\0'.
  Запись за границу выделенной памяти ловит санитайзер.
- Если `malloc` вернул NULL — вернуть NULL.
- Исходные строки не изменять.
- Результат освобождает вызывающий код через `free`.

## Interfaces

char *str_dup(const char *s);
char *str_concat(const char *a, const char *b);
char *str_repeat(const char *s, size_t times);
*/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* str_dup(const char* s)
{
    char* s_copy = malloc(strlen(s) + 1);
    if (s_copy == NULL) {
        return NULL;
    }
    strcpy(s_copy, s);
    return s_copy;
}

char* str_concat(const char* a, const char* b)
{
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    char* result = malloc(len_a + len_b + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, a, len_a);
    memcpy(result + len_a, b, len_b + 1);
    return result;
}

char* str_repeat(const char* s, size_t times)
{
    size_t len = strlen(s);

    if ((len != 0) && (times > (SIZE_MAX - 1) / len)) {
        return NULL;
    }

    char* result = malloc(len * times + 1);
    if (result == NULL) {
        return NULL;
    }

    if (len == 0) {
        result[0] = '\0';
        return result;
    }

    for (size_t i = 0; i < times; i++) {
        memcpy(result + len * i, s, len);
    }
    result[len * times] = '\0';

    return result;
}

int main(void)
{
    char* hello = str_concat("Hello, ", "world");
    char* line = str_repeat("-=", 6);

    if (hello == NULL || line == NULL) {
        free(hello);
        free(line);
        return 1;
    }

    printf("%s\n%s\n", hello, line);

    free(hello);
    free(line);
    return 0;
}
