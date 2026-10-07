/*
# Task 6 — String walk

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

#ifndef TEST

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

#else

static void test_empty(void)
{
    const char text[] = "";

    size_t length = 0;
    size_t letters = 0;
    size_t digits = 0;
    size_t spaces = 0;

    analyze_string(text, &length, &letters, &digits, &spaces);

    assert(length == 0);
    assert(letters == 0);
    assert(digits == 0);
    assert(spaces == 0);
}

static void test_letters(void)
{
    const char text[] = "Hello";

    size_t length = 0;
    size_t letters = 0;
    size_t digits = 0;
    size_t spaces = 0;

    analyze_string(text, &length, &letters, &digits, &spaces);

    assert(length == 5);
    assert(letters == 5);
    assert(digits == 0);
    assert(spaces == 0);
}

static void test_mixed(void)
{
    const char text[] = "Hello 123 World";

    size_t length = 0;
    size_t letters = 0;
    size_t digits = 0;
    size_t spaces = 0;

    analyze_string(text, &length, &letters, &digits, &spaces);

    assert(length == 15);
    assert(letters == 10);
    assert(digits == 3);
    assert(spaces == 2);
}

static void test_only_digits(void)
{
    const char text[] = "12345";

    size_t length = 0;
    size_t letters = 0;
    size_t digits = 0;
    size_t spaces = 0;

    analyze_string(text, &length, &letters, &digits, &spaces);

    assert(length == 5);
    assert(letters == 0);
    assert(digits == 5);
    assert(spaces == 0);
}

static void test_spaces(void)
{
    const char text[] = "   ";

    size_t length = 0;
    size_t letters = 0;
    size_t digits = 0;
    size_t spaces = 0;

    analyze_string(text, &length, &letters, &digits, &spaces);

    assert(length == 3);
    assert(letters == 0);
    assert(digits == 0);
    assert(spaces == 3);
}

int main(void)
{
    test_empty();
    test_letters();
    test_mixed();
    test_only_digits();
    test_spaces();

    puts("All tests passed");
    return 0;
}

#endif
