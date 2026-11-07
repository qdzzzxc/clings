/* Тесты к exercises/02_memory/08_dp.c. Запуск: make test 2 8 */

#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/02_memory/08_dp.c"
#undef main

#define TIME_LIMIT_SECONDS 3
#define BIG_ROWS 34
#define BIG_COLS 35

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

static void test_grid_example(void)
{
    const char* grid[] = { "...", ".#.", "..." };

    assert(grid_paths(grid, 3, 3) == 2);
}

static void test_grid_small(void)
{
    const char* one[] = { "." };
    const char* row[] = { "......" };
    const char* column[] = { ".", ".", "." };
    const char* square[] = { "..", ".." };
    const char* free3[] = { "...", "...", "..." };

    assert(grid_paths(one, 1, 1) == 1);
    assert(grid_paths(row, 1, 6) == 1);
    assert(grid_paths(column, 3, 1) == 1);
    assert(grid_paths(square, 2, 2) == 2);
    assert(grid_paths(free3, 3, 3) == 6);
}

static void test_grid_walls(void)
{
    const char* blocked_start[] = { "#.", ".." };
    const char* blocked_end[] = { "..", ".#" };
    const char* cut[] = { "..#", ".#.", "#.." };
    const char* corridor[] = { ".#..", ".#.#", "...." };
    const char* wall_in_row[] = { "..#.." };

    assert(grid_paths(blocked_start, 2, 2) == 0);
    assert(grid_paths(blocked_end, 2, 2) == 0);
    assert(grid_paths(cut, 3, 3) == 0);
    assert(grid_paths(corridor, 3, 4) == 1);
    assert(grid_paths(wall_in_row, 1, 5) == 0);
}

static void test_grid_big(void)
{
    static char rows[BIG_ROWS][BIG_COLS + 1];
    const char* grid[BIG_ROWS] = { NULL };

    for (size_t i = 0; i < BIG_ROWS; i++) {
        memset(rows[i], '.', BIG_COLS);
        rows[i][BIG_COLS] = '\0';
        grid[i] = rows[i];
    }
    /* C(67, 33): больше LLONG_MAX, но меньше ULLONG_MAX. */
    start_timer();
    assert(grid_paths(grid, BIG_ROWS, BIG_COLS) == 14226520737620288370ULL);
    stop_timer();
}

static void test_levenshtein_small(void)
{
    assert(levenshtein("kitten", "sitting") == 3);
    assert(levenshtein("sitting", "kitten") == 3);
    assert(levenshtein("", "") == 0);
    assert(levenshtein("", "abc") == 3);
    assert(levenshtein("abc", "") == 3);
    assert(levenshtein("same", "same") == 0);
    assert(levenshtein("flaw", "lawn") == 2);
    assert(levenshtein("abc", "xyz") == 3);
    assert(levenshtein("intention", "execution") == 5);
}

static char* repeat(const char* pattern, size_t length)
{
    size_t pattern_length = strlen(pattern);
    char* s = malloc(length + 1);

    assert(s != NULL);
    for (size_t i = 0; i < length; i++) {
        s[i] = pattern[i % pattern_length];
    }
    s[length] = '\0';
    return s;
}

static void test_levenshtein_long(void)
{
    char* a = repeat("ab", 4000);
    char* b = repeat("ab", 4000);

    /* b отличается от a одной заменой, b + 1 — одним удалением. */
    b[0] = 'b';
    start_timer();
    assert(levenshtein(a, a) == 0);
    assert(levenshtein(a, b) == 1);
    assert(levenshtein(a, b + 1) == 1);
    assert(levenshtein(a + 1, a) == 1);
    stop_timer();
    free(a);
    free(b);
}

static void test_subset_small(void)
{
    int values[] = { 3, 34, 4, 12, 5, 2 };
    int one[] = { 7 };

    assert(subset_sum(values, 6, 9) == 1);
    assert(subset_sum(values, 6, 30) == 0);
    assert(subset_sum(values, 6, 60) == 1);
    assert(subset_sum(values, 6, 61) == 0);
    assert(subset_sum(values, 6, 0) == 1);
    assert(subset_sum(one, 1, 7) == 1);
    assert(subset_sum(one, 1, 14) == 0);
    assert(subset_sum(one, 0, 0) == 1);
    assert(subset_sum(one, 0, 7) == 0);
}

static void test_subset_each_once(void)
{
    int values[] = { 5, 5 };
    int single[] = { 5 };

    assert(subset_sum(single, 1, 10) == 0);
    assert(subset_sum(values, 2, 10) == 1);
    assert(subset_sum(values, 2, 15) == 0);
}

static void test_subset_zeros(void)
{
    int values[] = { 0, 4, 0, 6, 0 };

    start_timer();
    assert(subset_sum(values, 5, 10) == 1);
    assert(subset_sum(values, 5, 5) == 0);
    assert(subset_sum(values, 5, 0) == 1);
    stop_timer();
}

static void test_subset_big(void)
{
    size_t count = 200;
    int* values = malloc(count * sizeof(int));
    int total = 0;

    assert(values != NULL);
    for (size_t i = 0; i < count; i++) {
        values[i] = 2 * (int)(i * 7919 % 4001) + 2;
        total += values[i];
    }
    /* Все числа чётные: нечётную сумму не набрать. */
    start_timer();
    assert(subset_sum(values, count, total) == 1);
    assert(subset_sum(values, count, total - 1) == 0);
    assert(subset_sum(values, count, total - values[7]) == 1);
    assert(subset_sum(values, count, 999999) == 0);
    stop_timer();
    free(values);
}

int main(void)
{
    test_grid_example();
    test_grid_small();
    test_grid_walls();
    test_grid_big();
    test_levenshtein_small();
    test_levenshtein_long();
    test_subset_small();
    test_subset_each_once();
    test_subset_zeros();
    test_subset_big();

    puts("All tests passed");
    return 0;
}
