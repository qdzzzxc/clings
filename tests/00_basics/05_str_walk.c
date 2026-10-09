/* Тесты к exercises/00_basics/05_str_walk.c. Запуск: make test 0 5 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/00_basics/05_str_walk.c"
#undef main

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
