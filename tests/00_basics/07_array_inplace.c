/* Тесты к exercises/00_basics/07_array_inplace.c. Запуск: make test 0 7 */

#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/00_basics/07_array_inplace.c"
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

static int equal(const int* a, const int* b, size_t size)
{
    return size == 0 || memcmp(a, b, size * sizeof(int)) == 0;
}

static void test_reverse(void)
{
    int even[] = { 1, 2, 3, 4 };
    int odd[] = { 1, 2, 3, 4, 5 };
    int one[] = { 7 };
    int empty[] = { 42 };

    reverse_array(even, 4);
    assert(equal(even, (int[]) { 4, 3, 2, 1 }, 4));
    reverse_array(odd, 5);
    assert(equal(odd, (int[]) { 5, 4, 3, 2, 1 }, 5));
    reverse_array(one, 1);
    assert(one[0] == 7);
    reverse_array(empty, 0);
    assert(empty[0] == 42);
}

static void test_reverse_part(void)
{
    int values[] = { 1, 2, 3, 4, 5, 6 };

    /* Разворот куска не трогает соседей. */
    reverse_array(values + 1, 3);
    assert(equal(values, (int[]) { 1, 4, 3, 2, 5, 6 }, 6));
}

static void test_rotate_example(void)
{
    int values[] = { 1, 2, 3, 4, 5 };

    rotate_right(values, 5, 2);
    assert(equal(values, (int[]) { 4, 5, 1, 2, 3 }, 5));
}

static void test_rotate_special_k(void)
{
    int zero[] = { 1, 2, 3 };
    int full[] = { 1, 2, 3 };
    int big[] = { 1, 2, 3 };
    int empty[] = { 42 };

    rotate_right(zero, 3, 0);
    assert(equal(zero, (int[]) { 1, 2, 3 }, 3));
    rotate_right(full, 3, 3);
    assert(equal(full, (int[]) { 1, 2, 3 }, 3));
    rotate_right(big, 3, 7);
    assert(equal(big, (int[]) { 3, 1, 2 }, 3));
    rotate_right(empty, 0, 5);
    assert(empty[0] == 42);
}

static void test_rotate_against_reference(void)
{
    int values[12] = { 0 };
    int expected[12] = { 0 };

    for (size_t size = 1; size <= 12; size++) {
        for (size_t k = 0; k <= 30; k++) {
            for (size_t i = 0; i < size; i++) {
                values[i] = (int)i * 10 - 30;
                expected[(i + k) % size] = values[i];
            }
            rotate_right(values, size, k);
            assert(equal(values, expected, size));
        }
    }
}

static void test_move_zeros(void)
{
    int example[] = { 0, 3, 0, 1, 2 };
    int none[] = { 5, -1, 2 };
    int all[] = { 0, 0, 0 };
    int tail[] = { 4, 0, 0 };
    int empty[] = { 42 };

    assert(move_zeros(example, 5) == 3);
    assert(equal(example, (int[]) { 3, 1, 2, 0, 0 }, 5));
    assert(move_zeros(none, 3) == 3);
    assert(equal(none, (int[]) { 5, -1, 2 }, 3));
    assert(move_zeros(all, 3) == 0);
    assert(equal(all, (int[]) { 0, 0, 0 }, 3));
    assert(move_zeros(tail, 3) == 1);
    assert(equal(tail, (int[]) { 4, 0, 0 }, 3));
    assert(move_zeros(empty, 0) == 0);
    assert(empty[0] == 42);
}

static void test_large_is_fast(void)
{
    size_t size = 1000000;
    int* values = malloc(size * sizeof(int));

    assert(values != NULL);
    for (size_t i = 0; i < size; i++) {
        values[i] = i % 3 == 1 ? 0 : (int)i;
    }

    signal(SIGALRM, too_slow);
    alarm(TIME_LIMIT_SECONDS);
    rotate_right(values, size, size / 2 + 1);
    rotate_right(values, size, size - size / 2 - 1);
    assert(values[0] == 0 && values[2] == 2 && values[size - 1] == (int)(size - 1));
    reverse_array(values, size);
    assert(values[0] == (int)(size - 1) && values[size - 3] == 2);
    reverse_array(values, size);
    /* Нули: элемент 0 и все i с остатком 1 от деления на 3. */
    assert(move_zeros(values, size) == size - 1 - size / 3);
    assert(values[0] == 2 && values[1] == 3 && values[2] == 5);
    assert(values[size - 1] == 0);
    alarm(0);

    free(values);
}

int main(void)
{
    test_reverse();
    test_reverse_part();
    test_rotate_example();
    test_rotate_special_k();
    test_rotate_against_reference();
    test_move_zeros();
    test_large_is_fast();

    puts("All tests passed");
    return 0;
}
