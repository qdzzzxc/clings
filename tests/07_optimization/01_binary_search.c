/* Тесты к exercises/07_optimization/01_binary_search.c. Запуск: make test 7 1 */

#include <assert.h>
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/07_optimization/01_binary_search.c"
#undef main

#define TIME_LIMIT_SECONDS 2

static void too_slow(int signal_number)
{
    static const char message[] = "Too slow: time limit exceeded\n";
    ssize_t written = write(STDERR_FILENO, message, sizeof(message) - 1);

    (void)signal_number;
    (void)written;
    _exit(1);
}

/* Если до stop_timer пройдёт больше TIME_LIMIT_SECONDS, тест завершится. */
static void start_timer(void)
{
    signal(SIGALRM, too_slow);
    alarm(TIME_LIMIT_SECONDS);
}

static void stop_timer(void)
{
    alarm(0);
}

static void test_count_less(void)
{
    int sorted[] = { 1, 3, 3, 5, 8 };

    assert(count_less(sorted, 5, 0) == 0);
    assert(count_less(sorted, 5, 1) == 0);
    assert(count_less(sorted, 5, 2) == 1);
    assert(count_less(sorted, 5, 3) == 1);
    assert(count_less(sorted, 5, 4) == 3);
    assert(count_less(sorted, 5, 5) == 3);
    assert(count_less(sorted, 5, 8) == 4);
    assert(count_less(sorted, 5, 9) == 5);
}

static void test_count_less_small_arrays(void)
{
    int one[] = { 5 };
    int two[] = { 5, 7 };

    assert(count_less(one, 0, 5) == 0);
    assert(count_less(one, 1, 4) == 0);
    assert(count_less(one, 1, 5) == 0);
    assert(count_less(one, 1, 6) == 1);
    assert(count_less(two, 2, 6) == 1);
    assert(count_less(two, 2, 7) == 1);
    assert(count_less(two, 2, 8) == 2);
}

static void test_count_less_all_equal(void)
{
    int same[] = { 4, 4, 4, 4, 4, 4, 4 };

    assert(count_less(same, 7, 4) == 0);
    assert(count_less(same, 7, 5) == 7);
    assert(count_less(same, 7, 3) == 0);
}

static void test_count_less_limits(void)
{
    int sorted[] = { INT_MIN, INT_MIN, -1, 0, INT_MAX, INT_MAX };

    assert(count_less(sorted, 6, INT_MIN) == 0);
    assert(count_less(sorted, 6, INT_MIN + 1) == 2);
    assert(count_less(sorted, 6, INT_MAX) == 4);
}

static void test_count_in_range(void)
{
    int sorted[] = { 1, 3, 3, 5, 8 };

    assert(count_in_range(sorted, 5, 3, 5) == 3);
    assert(count_in_range(sorted, 5, 3, 3) == 2);
    assert(count_in_range(sorted, 5, 4, 4) == 0);
    assert(count_in_range(sorted, 5, 0, 100) == 5);
    assert(count_in_range(sorted, 5, 6, 7) == 0);
    assert(count_in_range(sorted, 5, 8, 8) == 1);
    assert(count_in_range(sorted, 0, 0, 100) == 0);
}

static void test_count_in_empty_range(void)
{
    int sorted[] = { 1, 3, 3, 5, 8 };

    assert(count_in_range(sorted, 5, 5, 3) == 0);
    assert(count_in_range(sorted, 5, 100, -100) == 0);
}

static void test_count_in_range_limits(void)
{
    int sorted[] = { INT_MIN, INT_MIN, -1, 0, INT_MAX, INT_MAX };

    assert(count_in_range(sorted, 6, INT_MIN, INT_MAX) == 6);
    assert(count_in_range(sorted, 6, INT_MAX, INT_MAX) == 2);
    assert(count_in_range(sorted, 6, INT_MIN, INT_MIN) == 2);
    assert(count_in_range(sorted, 6, 0, INT_MAX) == 3);
    assert(count_in_range(sorted, 6, INT_MIN, -1) == 3);
}

static void test_many_queries_are_fast(void)
{
    size_t size = 1000000;
    int* sorted = malloc(size * sizeof(int));

    /* 0 0 0 2 2 2 4 4 4 ...: каждое чётное число по три раза. */
    assert(sorted != NULL);
    for (size_t i = 0; i < size; i++) {
        sorted[i] = (int)(i / 3) * 2;
    }

    start_timer();
    for (int value = -10; value < 300000; value++) {
        size_t expected = 0;

        if (value > 0) {
            expected = 3 * (((size_t)value + 1) / 2);
        }
        assert(count_less(sorted, size, value) == expected);
    }
    for (int low = 0; low < 300000; low += 2) {
        assert(count_in_range(sorted, size, low, low + 3) == 6);
    }
    stop_timer();

    free(sorted);
}

int main(void)
{
    test_count_less();
    test_count_less_small_arrays();
    test_count_less_all_equal();
    test_count_less_limits();
    test_count_in_range();
    test_count_in_empty_range();
    test_count_in_range_limits();
    test_many_queries_are_fast();

    puts("All tests passed");
    return 0;
}
