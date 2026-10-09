/* Тесты к exercises/04_structs/00_stats.c. Запуск: make test 4 0 */

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/04_structs/00_stats.c"
#undef main

static int stats_are(Stats stats, int min, int max, long long sum, size_t count)
{
    return stats.min == min && stats.max == max && stats.sum == sum && stats.count == count;
}

static void test_stats_of(void)
{
    int mixed[] = { 3, -2, 7, -5, 10 };
    int negative[] = { -4, -1, -7 };
    int single[] = { 42 };

    assert(stats_are(stats_of(mixed, 5), -5, 10, 13, 5));
    assert(stats_are(stats_of(negative, 3), -7, -1, -12, 3));
    assert(stats_are(stats_of(single, 1), 42, 42, 42, 1));
}

static void test_stats_of_large_values(void)
{
    int values[] = { INT_MAX, INT_MAX, INT_MIN };

    assert(stats_are(stats_of(values, 3), INT_MIN, INT_MAX, 2LL * INT_MAX + INT_MIN, 3));
}

static void test_add(void)
{
    Stats stats = { 5, 5, 5, 1 };

    stats_add(&stats, 9);
    assert(stats_are(stats, 5, 9, 14, 2));

    stats_add(&stats, -3);
    assert(stats_are(stats, -3, 9, 11, 3));

    stats_add(&stats, 4);
    assert(stats_are(stats, -3, 9, 15, 4));
}

static void test_merge(void)
{
    Stats a = { 1, 10, 30, 4 };
    Stats b = { -5, 3, -2, 2 };

    assert(stats_are(stats_merge(a, b), -5, 10, 28, 6));
    assert(stats_are(stats_merge(b, a), -5, 10, 28, 6));
    assert(stats_are(stats_merge(a, a), 1, 10, 60, 8));
}

static void test_merge_matches_whole_array(void)
{
    int values[] = { 8, -1, 4, 4, 0, 15, -9 };
    Stats whole = stats_of(values, 7);
    Stats merged = stats_merge(stats_of(values, 3), stats_of(values + 3, 4));

    assert(stats_are(merged, whole.min, whole.max, whole.sum, whole.count));
}

static void test_average(void)
{
    Stats exact = { 1, 3, 6, 3 };
    Stats half = { 1, 2, 3, 2 };
    Stats negative = { -3, 0, -3, 4 };

    assert(stats_average(&exact) == 2.0);
    assert(stats_average(&half) == 1.5);
    assert(stats_average(&negative) == -0.75);
}

int main(void)
{
    test_stats_of();
    test_stats_of_large_values();
    test_add();
    test_merge();
    test_merge_matches_whole_array();
    test_average();

    puts("All tests passed");
    return 0;
}
