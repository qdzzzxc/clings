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

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* str_dup(const char* s)
{
    /* TODO: реализуйте str_dup. */
    (void)s;
    assert(!"TODO: str_dup");
    return NULL;
}

char* str_concat(const char* a, const char* b)
{
    /* TODO: реализуйте str_concat. */
    (void)a;
    (void)b;
    assert(!"TODO: str_concat");
    return NULL;
}

char* str_repeat(const char* s, size_t times)
{
    /* TODO: реализуйте str_repeat. */
    (void)s;
    (void)times;
    assert(!"TODO: str_repeat");
    return NULL;
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
