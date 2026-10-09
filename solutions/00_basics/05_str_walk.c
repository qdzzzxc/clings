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
    *length = 0;
    *letters = 0;
    *digits = 0;
    *spaces = 0;

    while (*str) {
        char c = *str;

        (*length)++;
        if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) {
            (*letters)++;
        } else if ('0' <= c && c <= '9') {
            (*digits)++;
        } else if (c == ' ') {
            (*spaces)++;
        }

        str++;
    }
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

static void test_overwrites_previous_values(void)
{
    const char text[] = "a 1";

    size_t length = 777;
    size_t letters = 777;
    size_t digits = 777;
    size_t spaces = 777;

    analyze_string(text, &length, &letters, &digits, &spaces);

    assert(length == 3);
    assert(letters == 1);
    assert(digits == 1);
    assert(spaces == 1);
}

static void test_range_edges(void)
{
    const char text[] = "azAZ09";

    size_t length = 0;
    size_t letters = 0;
    size_t digits = 0;
    size_t spaces = 0;

    analyze_string(text, &length, &letters, &digits, &spaces);

    assert(length == 6);
    assert(letters == 4);
    assert(digits == 2);
    assert(spaces == 0);
}

static void test_neighbours_of_ranges(void)
{
    const char text[] = "@[`{/:";

    size_t length = 0;
    size_t letters = 0;
    size_t digits = 0;
    size_t spaces = 0;

    analyze_string(text, &length, &letters, &digits, &spaces);

    assert(length == 6);
    assert(letters == 0);
    assert(digits == 0);
    assert(spaces == 0);
}

static void test_punctuation(void)
{
    const char text[] = "a-b_c!?";

    size_t length = 0;
    size_t letters = 0;
    size_t digits = 0;
    size_t spaces = 0;

    analyze_string(text, &length, &letters, &digits, &spaces);

    assert(length == 7);
    assert(letters == 3);
    assert(digits == 0);
    assert(spaces == 0);
}

static void test_other_whitespace(void)
{
    const char text[] = "a\tb\n";

    size_t length = 0;
    size_t letters = 0;
    size_t digits = 0;
    size_t spaces = 0;

    analyze_string(text, &length, &letters, &digits, &spaces);

    assert(length == 4);
    assert(letters == 2);
    assert(digits == 0);
    assert(spaces == 0);
}

int main(void)
{
    test_empty();
    test_letters();
    test_mixed();
    test_only_digits();
    test_spaces();

    test_overwrites_previous_values();
    test_range_edges();
    test_neighbours_of_ranges();
    test_punctuation();
    test_other_whitespace();

    puts("All tests passed");
    return 0;
}

#endif
