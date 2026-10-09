/* Тесты к exercises/02_memory/02_str_copy.c. Запуск: make test 2 2 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/02_memory/02_str_copy.c"
#undef main

static void test_dup(void)
{
    const char* original = "hello";
    char* copy = str_dup(original);

    assert(copy != NULL);
    assert(copy != original);
    assert(strcmp(copy, "hello") == 0);

    free(copy);
}

static void test_dup_is_independent(void)
{
    char original[] = "hello";
    char* copy = str_dup(original);

    assert(copy != NULL);
    copy[0] = 'j';
    original[1] = 'u';

    assert(strcmp(copy, "jello") == 0);
    assert(strcmp(original, "hullo") == 0);

    free(copy);
}

static void test_dup_empty(void)
{
    char* copy = str_dup("");

    assert(copy != NULL);
    assert(copy[0] == '\0');

    free(copy);
}

static int concat_gives(const char* a, const char* b, const char* expected)
{
    char* result = str_concat(a, b);
    int ok = result != NULL && strcmp(result, expected) == 0;

    free(result);
    return ok;
}

static void test_concat(void)
{
    assert(concat_gives("Hello, ", "world", "Hello, world"));
    assert(concat_gives("", "world", "world"));
    assert(concat_gives("Hello", "", "Hello"));
    assert(concat_gives("", "", ""));
    assert(concat_gives("a", "b", "ab"));
}

static void test_concat_keeps_arguments(void)
{
    char a[] = "left";
    char b[] = "right";
    char* result = str_concat(a, b);

    assert(result != NULL);
    assert(result != a && result != b);
    assert(strcmp(a, "left") == 0);
    assert(strcmp(b, "right") == 0);

    free(result);
}

static int repeat_gives(const char* s, size_t times, const char* expected)
{
    char* result = str_repeat(s, times);
    int ok = result != NULL && strcmp(result, expected) == 0;

    free(result);
    return ok;
}

static void test_repeat(void)
{
    assert(repeat_gives("ab", 3, "ababab"));
    assert(repeat_gives("x", 1, "x"));
    assert(repeat_gives("-=", 4, "-=-=-=-="));
}

static void test_repeat_empty_results(void)
{
    assert(repeat_gives("abc", 0, ""));
    assert(repeat_gives("", 5, ""));
    assert(repeat_gives("", 0, ""));
}

static void test_repeat_long(void)
{
    char* result = str_repeat("abc", 1000);

    assert(result != NULL);
    assert(strlen(result) == 3000);
    assert(strncmp(result, "abcabc", 6) == 0);
    assert(strcmp(result + 2994, "abcabc") == 0);

    free(result);
}

int main(void)
{
    test_dup();
    test_dup_is_independent();
    test_dup_empty();
    test_concat();
    test_concat_keeps_arguments();
    test_repeat();
    test_repeat_empty_results();
    test_repeat_long();

    puts("All tests passed");
    return 0;
}
