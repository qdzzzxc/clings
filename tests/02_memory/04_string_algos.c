/* Тесты к exercises/02_memory/04_string_algos.c. Запуск: make test 2 4 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/02_memory/04_string_algos.c"
#undef main

static int reverse_gives(const char* text, const char* expected)
{
    char buffer[64];

    strcpy(buffer, text);
    reverse(buffer);
    return strcmp(buffer, expected) == 0;
}

static void test_reverse(void)
{
    assert(reverse_gives("abc", "cba"));
    assert(reverse_gives("abcd", "dcba"));
    assert(reverse_gives("stressed", "desserts"));
    assert(reverse_gives("a b", "b a"));
}

static void test_reverse_short(void)
{
    assert(reverse_gives("", ""));
    assert(reverse_gives("x", "x"));
    assert(reverse_gives("xy", "yx"));
}

static void test_reverse_stays_inside_the_string(void)
{
    /* Строка лежит в куче вплотную к границам: выход за них поймает санитайзер. */
    char* text = malloc(4);

    assert(text != NULL);
    strcpy(text, "abc");
    reverse(text);
    assert(strcmp(text, "cba") == 0);

    text[0] = '\0';
    reverse(text);
    assert(text[0] == '\0');

    free(text);
}

static void test_palindromes(void)
{
    assert(is_palindrome("level"));
    assert(is_palindrome("abba"));
    assert(is_palindrome("a"));
    assert(is_palindrome("12321"));
}

static void test_not_palindromes(void)
{
    assert(!is_palindrome("hello"));
    assert(!is_palindrome("ab"));
    assert(!is_palindrome("abca"));
    assert(!is_palindrome("1231"));
}

static void test_palindrome_ignores_case_and_punctuation(void)
{
    assert(is_palindrome("Level"));
    assert(is_palindrome("A man, a plan, a canal: Panama"));
    assert(is_palindrome("No 'x' in Nixon"));
    assert(!is_palindrome("A man, a plan, a canoe: Panama"));
    assert(!is_palindrome("ab, "));
}

static void test_palindrome_without_letters(void)
{
    assert(is_palindrome(""));
    assert(is_palindrome(" "));
    assert(is_palindrome(".,!"));
    assert(is_palindrome("..a.."));
}

static int trim_gives(const char* text, const char* expected)
{
    char* result = trim(text);
    int ok = result != NULL && result != text && strcmp(result, expected) == 0;

    free(result);
    return ok;
}

static void test_trim(void)
{
    assert(trim_gives("  hello  ", "hello"));
    assert(trim_gives("hello", "hello"));
    assert(trim_gives("  hello", "hello"));
    assert(trim_gives("hello  ", "hello"));
    assert(trim_gives("\t\n hello world \n", "hello world"));
}

static void test_trim_keeps_inner_spaces(void)
{
    assert(trim_gives("  a  b  ", "a  b"));
}

static void test_trim_to_empty(void)
{
    assert(trim_gives("", ""));
    assert(trim_gives("   ", ""));
    assert(trim_gives(" \t\n", ""));
}

static void test_trim_keeps_original(void)
{
    char text[] = "  keep  ";
    char* result = trim(text);

    assert(result != NULL);
    assert(strcmp(text, "  keep  ") == 0);

    free(result);
}

int main(void)
{
    test_reverse();
    test_reverse_short();
    test_reverse_stays_inside_the_string();
    test_palindromes();
    test_not_palindromes();
    test_palindrome_ignores_case_and_punctuation();
    test_palindrome_without_letters();
    test_trim();
    test_trim_keeps_inner_spaces();
    test_trim_to_empty();
    test_trim_keeps_original();

    puts("All tests passed");
    return 0;
}
