/*
# Task 5 — Dynamic matrix

Матрица, размеры которой известны только во время работы программы.
Она хранится как массив указателей: `m[i]` указывает на строку `i`,
а каждая строка — отдельный массив `int`.

## Нужно реализовать функции

matrix_create:
    Создаёт матрицу rows x cols, заполненную нулями.

matrix_free:
    Освобождает все строки и сам массив указателей.
    `matrix_free(NULL, rows)` ничего не делает.

matrix_transpose:
    Возвращает новую матрицу cols x rows: `out[j][i] == m[i][j]`.

matrix_multiply:
    Умножает матрицу `a` размера n x m на матрицу `b` размера m x k
    и возвращает новую матрицу n x k:
    out[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + ...

## Requirements

- Память выделять через `calloc` или `malloc`.
- Если какое-то выделение не удалось, освободить всё, что уже успели
  выделить, и вернуть NULL.
- Исходные матрицы не изменять.
- Гарантируется, что все размеры больше нуля.
- Утечки памяти тесты считают ошибкой.

## Interfaces

int **matrix_create(size_t rows, size_t cols);
void matrix_free(int **m, size_t rows);
int **matrix_transpose(int **m, size_t rows, size_t cols);
int **matrix_multiply(int **a, size_t n, size_t m, int **b, size_t k);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void matrix_free(int** m, size_t rows)
{
    /* TODO: реализуйте matrix_free. */
    (void)m;
    (void)rows;
    assert(!"TODO: matrix_free");
}

int** matrix_create(size_t rows, size_t cols)
{
    /* TODO: реализуйте matrix_create. */
    (void)rows;
    (void)cols;
    assert(!"TODO: matrix_create");
    return NULL;
}

int** matrix_transpose(int** m, size_t rows, size_t cols)
{
    /* TODO: реализуйте matrix_transpose. */
    (void)m;
    (void)rows;
    (void)cols;
    assert(!"TODO: matrix_transpose");
    return NULL;
}

int** matrix_multiply(int** a, size_t n, size_t m, int** b, size_t k)
{
    /* TODO: реализуйте matrix_multiply. */
    (void)a;
    (void)n;
    (void)m;
    (void)b;
    (void)k;
    assert(!"TODO: matrix_multiply");
    return NULL;
}

int main(void)
{
    int** m = matrix_create(2, 3);
    int** t;

    if (m == NULL) {
        return 1;
    }

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            m[i][j] = (int)(i * 3 + j);
        }
    }

    t = matrix_transpose(m, 2, 3);
    if (t != NULL) {
        for (size_t i = 0; i < 3; i++) {
            printf("%d %d\n", t[i][0], t[i][1]);
        }
    }

    matrix_free(t, 3);
    matrix_free(m, 2);
    return 0;
}
