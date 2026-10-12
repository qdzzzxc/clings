/* Тесты к exercises/algo/03_same_letters.c. Запуск: make test algo 3 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/algo/03_same_letters.c"
#undef main

#include "rules.h"

static int run(const char* input)
{
    FILE* in = tmpfile();
    int result = 0;

    assert(in != NULL);
    fputs(input, in);
    rewind(in);
    result = countSameLetters(in);
    fclose(in);
    return result;
}

static void test_example(void)
{
    assert(run("ab\nabab ba aaaab abc a\n") == 3);
}

static void test_single_word(void)
{
    assert(run("abc\nabc\n") == 1);
    assert(run("abc\nab\n") == 0);
    assert(run("abc\nabcd\n") == 0);
    assert(run("a\naaaaaaaa\n") == 1);
}

static void test_order_and_repeats_do_not_matter(void)
{
    assert(run("listen\nsilent enlist tinsel inlets listens lists\n") == 5);
    assert(run("zzz\nz zz zzzz za az\n") == 3);
}

static void test_subset_and_superset(void)
{
    assert(run("abc\na b c ab bc ca abcd abcabc\n") == 1);
}

static void test_spaces(void)
{
    assert(run("ab\n  ab   ba  \n") == 2);
    assert(run("ab\n     \n") == 0);
    assert(run("ab\nba") == 1);
    assert(run("ab\nab ba") == 2);
}

static void test_all_letters(void)
{
    assert(run("abcdefghijklmnopqrstuvwxyz\nzyxwvutsrqponmlkjihgfedcba abcdefghijklmnopqrstuvwxy\n") == 1);
}

static void test_long_line(void)
{
    char input[1200] = "qwerty\n";
    int expected = 0;

    for (int i = 0; strlen(input) + 12 < sizeof(input) - 1; i++) {
        const char* word = i % 3 == 0 ? "ytrewq " : i % 3 == 1 ? "qqwweerrtty "
                                                               : "qwertyu ";

        strcat(input, word);
        expected += i % 3 != 2;
    }
    strcat(input, "\n");
    assert(run(input) == expected);
}

int main(void)
{
    CHECK_RULES();

    test_example();
    test_single_word();
    test_order_and_repeats_do_not_matter();
    test_subset_and_superset();
    test_spaces();
    test_all_letters();
    test_long_line();

    puts("All tests passed");
    return 0;
}
