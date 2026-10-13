/* Тесты к exercises/00_basics/09_tokens.c. Запуск: make test 0 9 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/00_basics/09_tokens.c"
#undef main

static void test_replace_all(void)
{
    char path[] = "a/b/c";
    char none[] = "abc";
    char all[] = "xxx";
    char empty[] = "";

    assert(replace_all(path, '/', '-') == 2);
    assert(strcmp(path, "a-b-c") == 0);
    assert(replace_all(none, '/', '-') == 0);
    assert(strcmp(none, "abc") == 0);
    assert(replace_all(all, 'x', 'y') == 3);
    assert(strcmp(all, "yyy") == 0);
    assert(replace_all(empty, 'x', 'y') == 0);
}

static void test_replace_same_char(void)
{
    char text[] = "aaa";

    /* Замена на тот же символ не должна зациклиться. */
    assert(replace_all(text, 'a', 'a') == 3);
    assert(strcmp(text, "aaa") == 0);
}

static void test_is_identifier(void)
{
    assert(is_identifier("x") == 1);
    assert(is_identifier("_") == 1);
    assert(is_identifier("_tmp1") == 1);
    assert(is_identifier("camelCase") == 1);
    assert(is_identifier("snake_case_2") == 1);
    assert(is_identifier("") == 0);
    assert(is_identifier("1x") == 0);
    assert(is_identifier("a b") == 0);
    assert(is_identifier("a-b") == 0);
    assert(is_identifier("x!") == 0);
    assert(is_identifier("имя") == 0);
}

static void test_count_sentences(void)
{
    assert(count_sentences("Hi. How are you?! Fine...") == 3);
    assert(count_sentences("") == 0);
    assert(count_sentences("No end") == 0);
    assert(count_sentences("...") == 1);
    assert(count_sentences("One. Two") == 1);
    assert(count_sentences("A!B?C.") == 3);
    assert(count_sentences("Wait... what?!?") == 2);
}

static void test_split_words(void)
{
    char text[] = "red, green;blue";
    char* words[8] = { NULL };

    assert(split_words(text, " ,;", words, 8) == 3);
    assert(strcmp(words[0], "red") == 0);
    assert(strcmp(words[1], "green") == 0);
    assert(strcmp(words[2], "blue") == 0);
    assert(words[0] >= text && words[2] < text + sizeof(text));
}

static void test_split_edges(void)
{
    char spaces[] = "  one   two  ";
    char only_delimiters[] = " ,, ";
    char empty[] = "";
    char* words[4] = { NULL };

    assert(split_words(spaces, " ", words, 4) == 2);
    assert(strcmp(words[0], "one") == 0 && strcmp(words[1], "two") == 0);
    assert(split_words(only_delimiters, " ,", words, 4) == 0);
    assert(split_words(empty, " ", words, 4) == 0);
}

static void test_split_limit(void)
{
    char text[] = "a b c d e";
    char* words[3] = { NULL };

    assert(split_words(text, " ", words, 2) == 2);
    assert(strcmp(words[0], "a") == 0 && strcmp(words[1], "b") == 0);
    assert(words[2] == NULL);
}

int main(void)
{
    test_replace_all();
    test_replace_same_char();
    test_is_identifier();
    test_count_sentences();
    test_split_words();
    test_split_edges();
    test_split_limit();

    puts("All tests passed");
    return 0;
}
