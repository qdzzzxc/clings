/* Тесты к exercises/02_memory/05_dyn_matrix.c. Запуск: make test 2 5 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/02_memory/05_dyn_matrix.c"
#undef main

/* Создаёт матрицу и заполняет её значениями из обычного массива, строка за строкой. */
static int** matrix_from(size_t rows, size_t cols, const int* values)
{
    int** m = matrix_create(rows, cols);

    assert(m != NULL);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            m[i][j] = values[i * cols + j];
        }
    }
    return m;
}

static int matrix_equals(int** m, size_t rows, size_t cols, const int* expected)
{
    if (m == NULL) {
        return 0;
    }
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (m[i][j] != expected[i * cols + j]) {
                return 0;
            }
        }
    }
    return 1;
}

static void test_create_is_zero_filled(void)
{
    const int zeros[12] = { 0 };
    int** m = matrix_create(3, 4);

    assert(matrix_equals(m, 3, 4, zeros));

    matrix_free(m, 3);
}

static void test_rows_are_separate(void)
{
    int** m = matrix_create(2, 2);

    assert(m != NULL);
    assert(m[0] != m[1]);

    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    assert(m[0][0] == 1 && m[0][1] == 2 && m[1][0] == 3 && m[1][1] == 4);

    matrix_free(m, 2);
}

static void test_one_by_one(void)
{
    int** m = matrix_create(1, 1);

    assert(m != NULL);
    assert(m[0][0] == 0);

    matrix_free(m, 1);
}

static void test_free_null(void)
{
    matrix_free(NULL, 0);
    matrix_free(NULL, 5);
}

static void test_transpose(void)
{
    const int values[] = { 1, 2, 3, 4, 5, 6 };
    const int expected[] = { 1, 4, 2, 5, 3, 6 };
    int** m = matrix_from(2, 3, values);
    int** t = matrix_transpose(m, 2, 3);

    assert(t != m);
    assert(matrix_equals(t, 3, 2, expected));
    assert(matrix_equals(m, 2, 3, values));

    matrix_free(t, 3);
    matrix_free(m, 2);
}

static void test_transpose_row_to_column(void)
{
    const int values[] = { 7, 8, 9 };
    int** m = matrix_from(1, 3, values);
    int** t = matrix_transpose(m, 1, 3);

    assert(matrix_equals(t, 3, 1, values));

    matrix_free(t, 3);
    matrix_free(m, 1);
}

static void test_multiply(void)
{
    const int a_values[] = { 1, 2, 3, 4, 5, 6 };
    const int b_values[] = { 7, 8, 9, 10, 11, 12 };
    const int expected[] = { 58, 64, 139, 154 };
    int** a = matrix_from(2, 3, a_values);
    int** b = matrix_from(3, 2, b_values);
    int** product = matrix_multiply(a, 2, 3, b, 2);

    assert(matrix_equals(product, 2, 2, expected));
    assert(matrix_equals(a, 2, 3, a_values));
    assert(matrix_equals(b, 3, 2, b_values));

    matrix_free(product, 2);
    matrix_free(a, 2);
    matrix_free(b, 3);
}

static void test_multiply_by_identity(void)
{
    const int values[] = { 1, -2, 3, 4 };
    const int identity_values[] = { 1, 0, 0, 1 };
    int** m = matrix_from(2, 2, values);
    int** identity = matrix_from(2, 2, identity_values);
    int** left = matrix_multiply(identity, 2, 2, m, 2);
    int** right = matrix_multiply(m, 2, 2, identity, 2);

    assert(matrix_equals(left, 2, 2, values));
    assert(matrix_equals(right, 2, 2, values));

    matrix_free(left, 2);
    matrix_free(right, 2);
    matrix_free(identity, 2);
    matrix_free(m, 2);
}

static void test_multiply_row_by_column(void)
{
    const int row_values[] = { 1, 2, 3 };
    const int column_values[] = { 4, 5, 6 };
    const int dot[] = { 32 };
    const int outer[] = { 4, 8, 12, 5, 10, 15, 6, 12, 18 };
    int** row = matrix_from(1, 3, row_values);
    int** column = matrix_from(3, 1, column_values);
    int** small = matrix_multiply(row, 1, 3, column, 1);
    int** big = matrix_multiply(column, 3, 1, row, 3);

    assert(matrix_equals(small, 1, 1, dot));
    assert(matrix_equals(big, 3, 3, outer));

    matrix_free(small, 1);
    matrix_free(big, 3);
    matrix_free(row, 1);
    matrix_free(column, 3);
}

int main(void)
{
    test_create_is_zero_filled();
    test_rows_are_separate();
    test_one_by_one();
    test_free_null();
    test_transpose();
    test_transpose_row_to_column();
    test_multiply();
    test_multiply_by_identity();
    test_multiply_row_by_column();

    puts("All tests passed");
    return 0;
}
