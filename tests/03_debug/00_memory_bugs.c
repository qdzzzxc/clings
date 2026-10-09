/* Тесты к exercises/03_debug/00_memory_bugs.c. Запуск: make test 3 0 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/03_debug/00_memory_bugs.c"
#undef main

static void test_sum_array(void)
{
    /* Массив в куче: чтение за его границей увидит санитайзер. */
    int* values = malloc(4 * sizeof(int));

    assert(values != NULL);
    values[0] = 1;
    values[1] = 2;
    values[2] = 3;
    values[3] = 4;

    assert(sum_array(values, 4) == 10);
    assert(sum_array(values, 1) == 1);
    assert(sum_array(values, 0) == 0);

    free(values);
}

static void test_copy_string(void)
{
    char* copy = copy_string("hello");
    char* empty = copy_string("");

    assert(copy != NULL && empty != NULL);
    assert(strcmp(copy, "hello") == 0);
    assert(strcmp(empty, "") == 0);

    free(copy);
    free(empty);
}

static void test_split_digits(void)
{
    int digits[4] = { 777, 777, 777, 777 };

    split_digits(1234, digits);
    assert(digits[0] == 4);
    assert(digits[1] == 3);
    assert(digits[2] == 2);
    assert(digits[3] == 1);

    split_digits(7, digits);
    assert(digits[0] == 7);
    assert(digits[1] == 0);
    assert(digits[2] == 0);
    assert(digits[3] == 0);

    split_digits(987654, digits);
    assert(digits[0] == 4);
    assert(digits[3] == 7);
}

static void test_join_words(void)
{
    char* joined = join_words("hello", "world");
    char* empty = join_words("", "");

    assert(joined != NULL && empty != NULL);
    assert(strcmp(joined, "hello world") == 0);
    assert(strcmp(empty, " ") == 0);

    free(joined);
    free(empty);
}

int main(void)
{
    test_sum_array();
    test_copy_string();
    test_split_digits();
    test_join_words();

    /* Утечки санитайзер проверяет после выхода из main. */
    puts("All tests passed");
    return 0;
}
