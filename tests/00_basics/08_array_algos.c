/* Тесты к exercises/00_basics/08_array_algos.c. Запуск: make test 0 8 */

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
#include "../../exercises/00_basics/08_array_algos.c"
#undef main

#define TIME_LIMIT_SECONDS 1

static void too_slow(int signal_number)
{
    static const char message[] = "Too slow: time limit exceeded\n";
    ssize_t written = write(STDERR_FILENO, message, sizeof(message) - 1);

    (void)signal_number;
    (void)written;
    _exit(1);
}

static unsigned random_state = 12345;

static int random_int(int low, int high)
{
    random_state = random_state * 1103515245u + 12345u;
    return low + (int)((random_state >> 8) % (unsigned)(high - low + 1));
}

static int compare_ints(const void* left, const void* right)
{
    int a = *(const int*)left;
    int b = *(const int*)right;

    return (a > b) - (a < b);
}

/* Эталон: перебор всех кусков. */
static long long reference_max_subarray(const int* arr, size_t size)
{
    long long best = arr[0];

    for (size_t i = 0; i < size; i++) {
        long long sum = 0;

        for (size_t j = i; j < size; j++) {
            sum += arr[j];
            if (sum > best) {
                best = sum;
            }
        }
    }
    return best;
}

static void test_is_sorted(void)
{
    int empty[] = { 5 };
    int equal[] = { 2, 2, 2 };
    int sorted[] = { -3, 0, 0, 7 };
    int unsorted_tail[] = { 1, 2, 3, 2 };
    int unsorted_head[] = { 2, 1, 3, 4 };

    assert(is_sorted(empty, 0) == 1);
    assert(is_sorted(empty, 1) == 1);
    assert(is_sorted(equal, 3) == 1);
    assert(is_sorted(sorted, 4) == 1);
    assert(is_sorted(unsorted_tail, 4) == 0);
    assert(is_sorted(unsorted_head, 4) == 0);
}

static void test_unique_sorted(void)
{
    int example[] = { 1, 1, 2, 3, 3, 3 };
    int distinct[] = { -1, 0, 5 };
    int same[] = { 4, 4, 4, 4 };
    int empty[] = { 42 };

    assert(unique_sorted(example, 6) == 3);
    assert(example[0] == 1 && example[1] == 2 && example[2] == 3);
    assert(unique_sorted(distinct, 3) == 3);
    assert(distinct[0] == -1 && distinct[1] == 0 && distinct[2] == 5);
    assert(unique_sorted(same, 4) == 1);
    assert(same[0] == 4);
    assert(unique_sorted(empty, 0) == 0);
    assert(empty[0] == 42);
}

static void test_unique_random(void)
{
    int values[50] = { 0 };
    int expected[50] = { 0 };

    for (int round = 0; round < 200; round++) {
        size_t size = (size_t)random_int(1, 50);
        size_t count = 0;

        for (size_t i = 0; i < size; i++) {
            values[i] = random_int(-5, 5);
        }
        qsort(values, size, sizeof(int), compare_ints);
        for (size_t i = 0; i < size; i++) {
            if (i == 0 || values[i] != values[i - 1]) {
                expected[count++] = values[i];
            }
        }
        assert(unique_sorted(values, size) == count);
        assert(memcmp(values, expected, count * sizeof(int)) == 0);
    }
}

static void test_merge_example(void)
{
    int a[] = { 1, 4, 9 };
    int b[] = { 2, 4, 5 };
    int out[6] = { 0 };

    assert(merge_sorted(a, 3, b, 3, out) == 6);
    assert(memcmp(out, (int[]) { 1, 2, 4, 4, 5, 9 }, sizeof(out)) == 0);
}

static void test_merge_edges(void)
{
    int a[] = { 1, 2, 3 };
    int b[] = { 10, 20 };
    int out[6] = { 0 };

    assert(merge_sorted(a, 3, b, 0, out) == 3);
    assert(memcmp(out, a, sizeof(a)) == 0);
    assert(merge_sorted(a, 0, b, 2, out) == 2);
    assert(out[0] == 10 && out[1] == 20);
    assert(merge_sorted(b, 2, a, 3, out) == 5);
    assert(memcmp(out, (int[]) { 1, 2, 3, 10, 20 }, 5 * sizeof(int)) == 0);
}

static void test_merge_random(void)
{
    int a[40] = { 0 };
    int b[40] = { 0 };
    int out[81] = { 0 };
    int expected[80] = { 0 };

    for (int round = 0; round < 200; round++) {
        size_t a_size = (size_t)random_int(0, 40);
        size_t b_size = (size_t)random_int(0, 40);

        for (size_t i = 0; i < a_size; i++) {
            a[i] = expected[i] = random_int(-20, 20);
        }
        for (size_t i = 0; i < b_size; i++) {
            b[i] = expected[a_size + i] = random_int(-20, 20);
        }
        qsort(a, a_size, sizeof(int), compare_ints);
        qsort(b, b_size, sizeof(int), compare_ints);
        qsort(expected, a_size + b_size, sizeof(int), compare_ints);
        out[a_size + b_size] = 777;

        assert(merge_sorted(a, a_size, b, b_size, out) == a_size + b_size);
        assert(memcmp(out, expected, (a_size + b_size) * sizeof(int)) == 0);
        assert(out[a_size + b_size] == 777);
    }
}

static void test_max_subarray(void)
{
    int example[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    int negative[] = { -8, -3, -6 };
    int positive[] = { 1, 2, 3 };
    int one[] = { -7 };
    int big[] = { INT_MAX, INT_MAX, INT_MIN, INT_MAX };

    assert(max_subarray(example, 9) == 6);
    assert(max_subarray(negative, 3) == -3);
    assert(max_subarray(positive, 3) == 6);
    assert(max_subarray(one, 1) == -7);
    assert(max_subarray(big, 4) == 2LL * INT_MAX);
}

static void test_max_subarray_random(void)
{
    int values[30] = { 0 };

    for (int round = 0; round < 500; round++) {
        size_t size = (size_t)random_int(1, 30);

        for (size_t i = 0; i < size; i++) {
            values[i] = random_int(-10, 10);
        }
        assert(max_subarray(values, size) == reference_max_subarray(values, size));
    }
}

static void test_large_is_fast(void)
{
    size_t size = 1000000;
    int* values = malloc(size * sizeof(int));
    int* out = malloc(2 * size * sizeof(int));

    assert(values != NULL && out != NULL);
    for (size_t i = 0; i < size; i++) {
        values[i] = (int)(i / 3);
    }

    signal(SIGALRM, too_slow);
    alarm(TIME_LIMIT_SECONDS);
    assert(is_sorted(values, size) == 1);
    assert(merge_sorted(values, size, values, size, out) == 2 * size);
    assert(out[0] == 0 && out[5] == 0 && out[6] == 1 && out[2 * size - 1] == values[size - 1]);
    assert(max_subarray(values, size) > 0);
    assert(unique_sorted(values, size) == (size + 2) / 3);
    alarm(0);

    free(values);
    free(out);
}

int main(void)
{
    test_is_sorted();
    test_unique_sorted();
    test_unique_random();
    test_merge_example();
    test_merge_edges();
    test_merge_random();
    test_max_subarray();
    test_max_subarray_random();
    test_large_is_fast();

    puts("All tests passed");
    return 0;
}
