/*
# Task 1 — Matrix

Двумерный массив `int m[ROWS][COLS]` лежит в памяти одним куском: сначала
вся строка 0, за ней строка 1 и так далее. В функцию он передаётся как
указатель на строку, поэтому количество столбцов должно быть известно
заранее: `int m[][COLS]`.

## Нужно реализовать функции

matrix_sum:
    Сумма всех элементов.

row_sums:
    Записывает в `out[i]` сумму строки `i`.

max_position:
    Находит строку и столбец максимального элемента. Если максимумов
    несколько, выбирает первый при обходе по строкам слева направо.

transpose:
    Записывает в `out` транспонированную матрицу: `out[j][i] == m[i][j]`.
    Из матрицы ROWS x COLS получается матрица COLS x ROWS.

## Requirements

- Обходить матрицу вложенными циклами `for`.
- Исходную матрицу не изменять.
- Гарантируется, что `rows > 0`.

## Interfaces

long long matrix_sum(int m[][COLS], size_t rows);
void row_sums(int m[][COLS], size_t rows, long long *out);
void max_position(int m[][COLS], size_t rows, size_t *row, size_t *col);
void transpose(int m[ROWS][COLS], int out[COLS][ROWS]);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#define ROWS 3
#define COLS 4

long long matrix_sum(int m[][COLS], size_t rows)
{
    /* TODO: реализуйте matrix_sum. */
    (void)m;
    (void)rows;
    assert(!"TODO: matrix_sum");
    return 0;
}

void row_sums(int m[][COLS], size_t rows, long long* out)
{
    /* TODO: реализуйте row_sums. */
    (void)m;
    (void)rows;
    (void)out;
    assert(!"TODO: row_sums");
}

void max_position(int m[][COLS], size_t rows, size_t* row, size_t* col)
{
    /* TODO: реализуйте max_position. */
    (void)m;
    (void)rows;
    (void)row;
    (void)col;
    assert(!"TODO: max_position");
}

void transpose(int m[ROWS][COLS], int out[COLS][ROWS])
{
    /* TODO: реализуйте transpose. */
    (void)m;
    (void)out;
    assert(!"TODO: transpose");
}

int main(void)
{
    int m[ROWS][COLS] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
    };
    int t[COLS][ROWS];

    transpose(m, t);

    printf("sum: %lld\n", matrix_sum(m, ROWS));
    for (size_t i = 0; i < COLS; i++) {
        for (size_t j = 0; j < ROWS; j++) {
            printf("%3d", t[i][j]);
        }
        printf("\n");
    }
    return 0;
}
