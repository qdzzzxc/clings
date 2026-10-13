/* Тесты к exercises/02_memory/06_convolution.c. Запуск: make test 2 6 */

#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/02_memory/06_convolution.c"
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

static const int identity[] = { 0, 0, 0, 0, 1, 0, 0, 0, 0 };
static const int cross[] = { 0, 1, 0, 1, 1, 1, 0, 1, 0 };

/* Эталон: формула из условия. */
static int reference(const int* image, size_t cols, const int* kernel, size_t i, size_t j)
{
    long long sum = 0;

    for (size_t a = 0; a < 3; a++) {
        for (size_t b = 0; b < 3; b++) {
            sum += (long long)image[(i + a) * cols + j + b] * kernel[a * 3 + b];
        }
    }
    return (int)sum;
}

static void check(const int* image, size_t rows, size_t cols, const int* kernel)
{
    int* copy = malloc(rows * cols * sizeof(int));
    int* out = NULL;

    assert(copy != NULL);
    memcpy(copy, image, rows * cols * sizeof(int));
    out = convolve(image, rows, cols, kernel);
    assert(out != NULL);
    for (size_t i = 0; i + 2 < rows; i++) {
        for (size_t j = 0; j + 2 < cols; j++) {
            assert(out[i * (cols - 2) + j] == reference(image, cols, kernel, i, j));
        }
    }
    assert(memcmp(copy, image, rows * cols * sizeof(int)) == 0);
    free(out);
    free(copy);
}

static void test_example(void)
{
    const int image[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    int* out = convolve(image, 4, 4, cross);

    assert(out != NULL);
    assert(out[0] == 30 && out[1] == 35 && out[2] == 50 && out[3] == 55);
    free(out);
}

static void test_identity_kernel(void)
{
    const int image[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    int* out = convolve(image, 3, 4, identity);

    /* Ядро с единицей в центре вырезает середину матрицы. */
    assert(out != NULL);
    assert(out[0] == 6 && out[1] == 7);
    free(out);
}

static void test_smallest(void)
{
    const int image[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    const int kernel[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int* out = convolve(image, 3, 3, kernel);

    /* Ядро не переворачивается: 1*9 + 2*8 + ... + 9*1. */
    assert(out != NULL);
    assert(out[0] == 165);
    free(out);
}

static void test_too_small(void)
{
    const int image[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    assert(convolve(image, 2, 3, cross) == NULL);
    assert(convolve(image, 3, 2, cross) == NULL);
    assert(convolve(image, 1, 9, cross) == NULL);
}

static void test_not_square(void)
{
    int image[5 * 7] = { 0 };
    const int edges[] = { -1, -1, -1, -1, 8, -1, -1, -1, -1 };

    for (size_t i = 0; i < 5 * 7; i++) {
        image[i] = (int)(i * 7 % 11) - 5;
    }
    check(image, 5, 7, edges);
    check(image, 7, 5, edges);
    check(image, 5, 7, cross);
}

static void test_large_is_fast(void)
{
    size_t rows = 2000;
    size_t cols = 2000;
    int* image = malloc(rows * cols * sizeof(int));
    int* out = NULL;

    assert(image != NULL);
    for (size_t i = 0; i < rows * cols; i++) {
        image[i] = (int)(i % 251);
    }

    signal(SIGALRM, too_slow);
    alarm(TIME_LIMIT_SECONDS);
    out = convolve(image, rows, cols, cross);
    alarm(0);

    assert(out != NULL);
    assert(out[0] == reference(image, cols, cross, 0, 0));
    assert(out[(rows - 3) * (cols - 2) + cols - 3] == reference(image, cols, cross, rows - 3, cols - 3));
    free(out);
    free(image);
}

int main(void)
{
    test_example();
    test_identity_kernel();
    test_smallest();
    test_too_small();
    test_not_square();
    test_large_is_fast();

    puts("All tests passed");
    return 0;
}
