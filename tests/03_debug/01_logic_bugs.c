/* Тесты к exercises/03_debug/01_logic_bugs.c. Запуск: make test 3 1 */

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/03_debug/01_logic_bugs.c"
#undef main

static void test_average(void)
{
    int simple[] = { 2, 4, 6 };
    int rounded[] = { 1, 2 };
    int negative[] = { -3, -4 };

    assert(average(simple, 3) == 4);
    assert(average(rounded, 2) == 1);
    assert(average(negative, 2) == -3);
    assert(average(simple, 1) == 2);
}

static void test_average_of_large_values(void)
{
    int large[] = { INT_MAX, INT_MAX, INT_MAX };
    int small[] = { INT_MIN, INT_MIN };
    int mixed[] = { INT_MAX, INT_MIN };

    assert(average(large, 3) == INT_MAX);
    assert(average(small, 2) == INT_MIN);
    assert(average(mixed, 2) == 0);
}

static void test_max_of(void)
{
    int mixed[] = { 3, -2, 7, -5 };
    int negative[] = { -4, -1, -7 };
    int single[] = { -42 };

    assert(max_of(mixed, 4) == 7);
    assert(max_of(negative, 3) == -1);
    assert(max_of(single, 1) == -42);
}

static void test_find_last(void)
{
    int values[] = { 5, 1, 5, 2, 5, 3 };

    assert(find_last(values, 6, 5) == 4);
    assert(find_last(values, 6, 3) == 5);
    assert(find_last(values, 6, 1) == 1);
    assert(find_last(values, 6, 9) == -1);
}

static void test_find_last_at_index_zero(void)
{
    int values[] = { 7, 1, 2 };

    assert(find_last(values, 3, 7) == 0);
    assert(find_last(values, 1, 7) == 0);
}

static void test_find_last_in_empty_array(void)
{
    /* Массив в куче: чтение за его границей увидит санитайзер. */
    int* values = malloc(2 * sizeof(int));

    assert(values != NULL);
    values[0] = 1;
    values[1] = 1;

    assert(find_last(values, 0, 1) == -1);

    free(values);
}

static void test_is_power_of_two(void)
{
    assert(is_power_of_two(1));
    assert(is_power_of_two(2));
    assert(is_power_of_two(1024));
    assert(is_power_of_two(1U << 31));

    assert(!is_power_of_two(3));
    assert(!is_power_of_two(6));
    assert(!is_power_of_two(1023));
    assert(!is_power_of_two(UINT_MAX));
}

static void test_zero_is_not_a_power_of_two(void)
{
    assert(!is_power_of_two(0));
}

int main(void)
{
    test_average();
    test_average_of_large_values();
    test_max_of();
    test_find_last();
    test_find_last_at_index_zero();
    test_find_last_in_empty_array();
    test_is_power_of_two();
    test_zero_is_not_a_power_of_two();

    puts("All tests passed");
    return 0;
}
