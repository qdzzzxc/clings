/* Тесты к exercises/07_optimization/00_range_sums.c. Запуск: make test 7 0 */

#include <assert.h>
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/07_optimization/00_range_sums.c"
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
    int values[] = { 3, 1, 4, 1, 5 };
    size_t lefts[] = { 0, 1, 3 };
    size_t rights[] = { 4, 2, 3 };
    long long sums[3] = { 777, 777, 777 };

    range_sums(values, 5, lefts, rights, 3, sums);

    assert(sums[0] == 14);
    assert(sums[1] == 5);
    assert(sums[2] == 1);
}

static void test_single_elements_and_edges(void)
{
    int values[] = { -5, 7, 0, -2 };
    size_t lefts[] = { 0, 1, 2, 3, 0, 2 };
    size_t rights[] = { 0, 1, 2, 3, 3, 3 };
    long long sums[6];

    range_sums(values, 4, lefts, rights, 6, sums);

    assert(sums[0] == -5);
    assert(sums[1] == 7);
    assert(sums[2] == 0);
    assert(sums[3] == -2);
    assert(sums[4] == 0);
    assert(sums[5] == -2);
}

static void test_no_queries(void)
{
    int values[] = { 1, 2, 3 };
    size_t left = 0;
    size_t right = 0;
    long long sum = 777;

    range_sums(values, 3, &left, &right, 0, &sum);

    assert(sum == 777);
}

static void test_sums_larger_than_int(void)
{
    int values[] = { INT_MAX, INT_MAX, INT_MAX, INT_MIN };
    size_t lefts[] = { 0, 3 };
    size_t rights[] = { 2, 3 };
    long long sums[2];

    range_sums(values, 4, lefts, rights, 2, sums);

    assert(sums[0] == 3LL * INT_MAX);
    assert(sums[1] == INT_MIN);
}

static void test_many_queries_are_fast(void)
{
    size_t size = 200000;
    size_t query_count = 200000;
    int* values = malloc(size * sizeof(int));
    long long* prefix = malloc((size + 1) * sizeof(long long));
    size_t* lefts = malloc(query_count * sizeof(size_t));
    size_t* rights = malloc(query_count * sizeof(size_t));
    long long* sums = malloc(query_count * sizeof(long long));

    assert(values != NULL && prefix != NULL && lefts != NULL && rights != NULL && sums != NULL);

    prefix[0] = 0;
    for (size_t i = 0; i < size; i++) {
        values[i] = (int)(i % 7) - 3;
        prefix[i + 1] = prefix[i] + values[i];
    }

    /* Почти все запросы — длинные отрезки. */
    for (size_t i = 0; i < query_count; i++) {
        lefts[i] = i % 1000;
        rights[i] = size - 1 - i % 500;
    }

    start_timer();
    range_sums(values, size, lefts, rights, query_count, sums);
    stop_timer();

    for (size_t i = 0; i < query_count; i++) {
        assert(sums[i] == prefix[rights[i] + 1] - prefix[lefts[i]]);
    }

    free(values);
    free(prefix);
    free(lefts);
    free(rights);
    free(sums);
}

int main(void)
{
    test_example();
    test_single_elements_and_edges();
    test_no_queries();
    test_sums_larger_than_int();
    test_many_queries_are_fast();

    puts("All tests passed");
    return 0;
}
