/* Тесты к exercises/07_optimization/02_pair_sum.c. Запуск: make test 7 2 */

#include <assert.h>
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/07_optimization/02_pair_sum.c"
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

static void test_example(void)
{
    int values[] = { 8, 1, 5, 3 };

    assert(has_pair_with_sum(values, 4, 9));
    assert(has_pair_with_sum(values, 4, 4));
    assert(has_pair_with_sum(values, 4, 13));
    assert(has_pair_with_sum(values, 4, 8));
    assert(!has_pair_with_sum(values, 4, 10));
    assert(!has_pair_with_sum(values, 4, 100));
    assert(!has_pair_with_sum(values, 4, 2));
}

static void test_small_arrays(void)
{
    int values[] = { 5, 7 };

    assert(!has_pair_with_sum(values, 0, 0));
    assert(!has_pair_with_sum(values, 1, 5));
    assert(!has_pair_with_sum(values, 1, 10));
    assert(has_pair_with_sum(values, 2, 12));
    assert(!has_pair_with_sum(values, 2, 14));
}

static void test_equal_elements(void)
{
    int values[] = { 5, 2, 5 };
    int same[] = { 3, 3, 3, 3 };

    assert(has_pair_with_sum(values, 3, 10));
    assert(!has_pair_with_sum(values, 3, 4));
    assert(has_pair_with_sum(same, 4, 6));
    assert(!has_pair_with_sum(same, 4, 3));
}

static void test_negative_numbers(void)
{
    int values[] = { -8, 4, -1, 10, 0 };

    assert(has_pair_with_sum(values, 5, -9));
    assert(has_pair_with_sum(values, 5, 2));
    assert(has_pair_with_sum(values, 5, 0) == 0);
    assert(has_pair_with_sum(values, 5, -1));
    assert(!has_pair_with_sum(values, 5, -16));
}

static void test_sums_larger_than_int(void)
{
    int values[] = { INT_MAX, 1, INT_MAX, INT_MIN, INT_MIN };

    assert(has_pair_with_sum(values, 5, 2LL * INT_MAX));
    assert(has_pair_with_sum(values, 5, 2LL * INT_MIN));
    assert(has_pair_with_sum(values, 5, -1));
    assert(!has_pair_with_sum(values, 5, 2LL * INT_MAX + 1));
    assert(!has_pair_with_sum(values, 3, INT_MIN));
}

static void test_array_is_not_modified(void)
{
    int values[] = { 9, 1, 8, 2, 7 };

    assert(has_pair_with_sum(values, 5, 3));
    assert(values[0] == 9 && values[1] == 1 && values[2] == 8 && values[3] == 2 && values[4] == 7);
}

static void test_large_array_is_fast(void)
{
    size_t size = 300000;
    int* values = malloc(size * sizeof(int));

    /* Все чётные числа от 0 до 2 * (size - 1) в перемешанном порядке. */
    assert(values != NULL);
    for (size_t i = 0; i < size; i++) {
        values[i] = (int)(2 * (i * 7919 % size));
    }

    start_timer();
    assert(!has_pair_with_sum(values, size, 300001));
    assert(!has_pair_with_sum(values, size, 4LL * (long long)size));
    assert(has_pair_with_sum(values, size, 4LL * (long long)size - 6));
    assert(has_pair_with_sum(values, size, 2));
    stop_timer();

    free(values);
}

int main(void)
{
    test_example();
    test_small_arrays();
    test_equal_elements();
    test_negative_numbers();
    test_sums_larger_than_int();
    test_array_is_not_modified();
    test_large_array_is_fast();

    puts("All tests passed");
    return 0;
}
