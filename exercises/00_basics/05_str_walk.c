/*
# Task 5 — String walk

Дана C-строка.

Нужно определить:

- длину строки;
- количество цифр;
- количество пробелов;
- количество букв.

## Requirements

- Реализовать функцию `analyze_string`.
- Нельзя использовать `strlen`.
- Нельзя использовать индексацию `str[i]`.
- Строку обходить только указателем.
- Остановиться по символу '\0'.
- Строку не изменять.
- Результаты вернуть через указатели.

## Interface

void analyze_string(const char *str,
                    size_t *length,
                    size_t *letters,
                    size_t *digits,
                    size_t *spaces);

## Notes

Для этой задачи считаем буквами только:

'a'..'z'
'A'..'Z'

Цифрами только:

'0'..'9'

Пробелом только символ ' '.
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

void analyze_string(const char* str,
    size_t* length,
    size_t* letters,
    size_t* digits,
    size_t* spaces)
{
    /* TODO: реализуйте analyze_string. */
    (void)str;
    (void)length;
    (void)letters;
    (void)digits;
    (void)spaces;
    assert(!"TODO: analyze_string");
}

int main(void)
{
    const char text[] = "Hello 123 World";

    size_t length = 0;
    size_t letters = 0;
    size_t digits = 0;
    size_t spaces = 0;

    analyze_string(text, &length, &letters, &digits, &spaces);

    printf("length: %zu\n", length);
    printf("letters: %zu\n", letters);
    printf("digits: %zu\n", digits);
    printf("spaces: %zu\n", spaces);

    return 0;
}
