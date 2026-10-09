/* Тесты к exercises/02_memory/01_matrix.c. Запуск: make test 2 1 */

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/02_memory/01_matrix.c"
#undef main

static void test_sum(void)
{
    int m[ROWS][COLS] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
    };

    assert(matrix_sum(m, ROWS) == 78);
    assert(matrix_sum(m, 1) == 10);
    assert(matrix_sum(m, 2) == 36);
}

static void test_sum_larger_than_int(void)
{
    int m[2][COLS] = {
        { INT_MAX, INT_MAX, INT_MAX, INT_MAX },
        { INT_MAX, INT_MAX, INT_MAX, INT_MAX },
    };

    assert(matrix_sum(m, 2) == 8LL * INT_MAX);
}

static void test_row_sums(void)
{
    int m[ROWS][COLS] = {
        { 1, 2, 3, 4 },
        { -1, -2, -3, -4 },
        { 0, 0, 0, 5 },
    };
    long long sums[ROWS] = { 777, 777, 777 };

    row_sums(m, ROWS, sums);

    assert(sums[0] == 10);
    assert(sums[1] == -10);
    assert(sums[2] == 5);
}

static void test_row_sums_does_not_touch_extra_rows(void)
{
    int m[ROWS][COLS] = {
        { 1, 1, 1, 1 },
        { 2, 2, 2, 2 },
        { 3, 3, 3, 3 },
    };
    long long sums[ROWS] = { 777, 777, 777 };

    row_sums(m, 2, sums);

    assert(sums[0] == 4);
    assert(sums[1] == 8);
    assert(sums[2] == 777);
}

static int max_is_at(int m[][COLS], size_t rows, size_t expected_row, size_t expected_col)
{
    size_t row = 777;
    size_t col = 777;

    max_position(m, rows, &row, &col);
    return row == expected_row && col == expected_col;
}

static void test_max_position(void)
{
    int middle[ROWS][COLS] = {
        { 1, 2, 3, 4 },
        { 5, 60, 7, 8 },
        { 9, 10, 11, 12 },
    };
    int last[ROWS][COLS] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
    };
    int negative[2][COLS] = {
        { -5, -6, -7, -8 },
        { -9, -1, -3, -4 },
    };

    assert(max_is_at(middle, ROWS, 1, 1));
    assert(max_is_at(last, ROWS, 2, 3));
    assert(max_is_at(last, 1, 0, 3));
    assert(max_is_at(negative, 2, 1, 1));
}

static void test_first_maximum_wins(void)
{
    int m[ROWS][COLS] = {
        { 1, 9, 3, 9 },
        { 9, 6, 7, 8 },
        { 9, 9, 9, 9 },
    };

    assert(max_is_at(m, ROWS, 0, 1));
}

static void test_transpose(void)
{
    int m[ROWS][COLS] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
    };
    int out[COLS][ROWS];

    for (size_t i = 0; i < COLS; i++) {
        for (size_t j = 0; j < ROWS; j++) {
            out[i][j] = 777;
        }
    }

    transpose(m, out);

    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            assert(out[j][i] == m[i][j]);
        }
    }

    assert(out[3][0] == 4);
    assert(out[0][2] == 9);
    assert(m[2][3] == 12);
}

int main(void)
{
    test_sum();
    test_sum_larger_than_int();
    test_row_sums();
    test_row_sums_does_not_touch_extra_rows();
    test_max_position();
    test_first_maximum_wins();
    test_transpose();

    puts("All tests passed");
    return 0;
}
