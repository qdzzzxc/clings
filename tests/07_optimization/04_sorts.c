/* Тесты к exercises/07_optimization/04_sorts.c. Запуск: make test 7 4 */

#include <assert.h>
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/07_optimization/04_sorts.c"
#undef main

#define TIME_LIMIT_SECONDS 3
#define BIG 500000
#define SMALL_CASES 7

typedef enum {
    INSERTION,
    MERGE,
    QUICK,
    COUNTING
} Sort;

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

static int compare_ints(const void* a, const void* b)
{
    int x = *(const int*)a;
    int y = *(const int*)b;

    return (x > y) - (x < y);
}

static void run_sort(Sort sort, int* arr, size_t size, int max_value)
{
    switch (sort) {
    case INSERTION:
        insertion_sort(arr, size);
        break;
    case MERGE:
        assert(merge_sort(arr, size) == 1);
        break;
    case QUICK:
        quick_sort(arr, size);
        break;
    case COUNTING:
        assert(counting_sort(arr, size, max_value) == 1);
        break;
    }
}

/* Сортирует копию с запасом по краям и сравнивает с qsort. */
static void check(Sort sort, const int* input, size_t size, int max_value)
{
    int* actual = malloc((size + 2) * sizeof(int));
    int* expected = malloc((size + 1) * sizeof(int));

    assert(actual != NULL && expected != NULL);
    actual[0] = -777;
    actual[size + 1] = -777;
    memcpy(actual + 1, input, size * sizeof(int));
    memcpy(expected, input, size * sizeof(int));
    qsort(expected, size, sizeof(int), compare_ints);

    run_sort(sort, actual + 1, size, max_value);

    assert(actual[0] == -777 && actual[size + 1] == -777);
    assert(memcmp(actual + 1, expected, size * sizeof(int)) == 0);
    free(actual);
    free(expected);
}

static void check_small(Sort sort)
{
    static const int one[] = { 5 };
    static const int two[] = { 2, 1 };
    static const int sorted[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    static const int reversed[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    static const int repeats[] = { 3, 1, 3, 0, 1, 3, 0, 0, 3 };
    static const int equal[] = { 4, 4, 4, 4, 4 };
    static const int mixed[] = { 5, 2, 9, 1, 5, 6, 0, 9, 7, 3, 8 };
    static const int* const cases[SMALL_CASES] = { one, two, sorted, reversed, repeats, equal, mixed };
    static const size_t sizes[SMALL_CASES] = { 1, 2, 8, 10, 9, 5, 11 };
    int empty[1] = { 42 };

    for (size_t i = 0; i < SMALL_CASES; i++) {
        check(sort, cases[i], sizes[i], 9);
    }
    run_sort(sort, empty, 0, 9);
    assert(empty[0] == 42);
}

/* BIG чисел из [0, max_value] разного вида. */
static void check_big(Sort sort, int max_value)
{
    int* arr = malloc(BIG * sizeof(int));
    unsigned int seed = 12345;

    assert(arr != NULL);
    for (size_t i = 0; i < BIG; i++) {
        seed = seed * 1103515245u + 12345u;
        arr[i] = (int)((seed >> 8) % ((unsigned int)max_value + 1));
    }
    start_timer();
    check(sort, arr, BIG, max_value);

    for (size_t i = 0; i < BIG; i++) {
        arr[i] = (int)((long long)i * max_value / BIG);
    }
    check(sort, arr, BIG, max_value);

    for (size_t i = 0; i < BIG; i++) {
        arr[i] = (int)((long long)(BIG - i) * max_value / BIG);
    }
    check(sort, arr, BIG, max_value);

    for (size_t i = 0; i < BIG; i++) {
        arr[i] = max_value / 2;
    }
    check(sort, arr, BIG, max_value);
    stop_timer();
    free(arr);
}

static void test_insertion(void)
{
    static const int negatives[] = { -3, INT_MAX, 0, INT_MIN, -1, 7 };
    int* nearly = malloc(20000 * sizeof(int));

    check_small(INSERTION);
    check(INSERTION, negatives, 6, 0);

    /* Почти отсортированный массив вставками сортируется быстро. */
    assert(nearly != NULL);
    for (size_t i = 0; i < 20000; i++) {
        nearly[i] = (int)i;
    }
    nearly[0] = 20000;
    nearly[19999] = -1;
    start_timer();
    check(INSERTION, nearly, 20000, 0);
    stop_timer();
    free(nearly);
}

static void test_merge(void)
{
    static const int negatives[] = { -3, INT_MAX, 0, INT_MIN, -1, 7 };

    check_small(MERGE);
    check(MERGE, negatives, 6, 0);
    check_big(MERGE, INT_MAX - 1);
    check_big(MERGE, 10);
}

static void test_quick(void)
{
    static const int negatives[] = { -3, INT_MAX, 0, INT_MIN, -1, 7 };

    check_small(QUICK);
    check(QUICK, negatives, 6, 0);
    check_big(QUICK, INT_MAX - 1);
    check_big(QUICK, 10);
}

static void test_counting(void)
{
    static const int zeros[] = { 0, 0, 0 };
    static const int top[] = { 1000000, 0, 1000000, 500000 };

    check_small(COUNTING);
    check(COUNTING, zeros, 3, 0);
    check(COUNTING, top, 4, 1000000);
    check_big(COUNTING, 1000);
    check_big(COUNTING, 1000000);
}

int main(void)
{
    test_insertion();
    test_merge();
    test_quick();
    test_counting();

    puts("All tests passed");
    return 0;
}
