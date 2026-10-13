/* Тесты к exercises/01_files/05_file_array.c. Запуск: make test 1 5 */

#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/01_files/05_file_array.c"
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

static FILE* file_with(const int* values, size_t count)
{
    FILE* file = tmpfile();

    assert(file != NULL);
    assert(fwrite(values, sizeof(int), count, file) == count);
    return file;
}

/* Читает весь файл обычным способом и сравнивает с ожидаемым. */
static void assert_contents(FILE* file, const int* expected, size_t count)
{
    int buffer[64] = { 0 };

    assert(count <= 64);
    assert(fseek(file, 0, SEEK_SET) == 0);
    assert(fread(buffer, sizeof(int), 64, file) == count);
    assert(memcmp(buffer, expected, count * sizeof(int)) == 0);
}

static void test_count(void)
{
    const int values[] = { 1, 2, 3 };
    FILE* empty = file_with(values, 0);
    FILE* three = file_with(values, 3);

    assert(file_int_count(empty) == 0);
    assert(file_int_count(three) == 3);
    fclose(empty);
    fclose(three);
}

static void test_count_broken_size(void)
{
    const int values[] = { 1, 2 };
    FILE* file = file_with(values, 2);

    /* Лишний байт: файл не состоит из целых int. */
    assert(fputc('x', file) != EOF);
    assert(file_int_count(file) == -1);
    fclose(file);
}

static void test_get(void)
{
    const int values[] = { 10, -20, 30 };
    FILE* file = file_with(values, 3);
    int value = 0;

    assert(file_get(file, 0, &value) == 1 && value == 10);
    assert(file_get(file, 2, &value) == 1 && value == 30);
    assert(file_get(file, 1, &value) == 1 && value == -20);
    value = 777;
    assert(file_get(file, 3, &value) == 0);
    assert(file_get(file, -1, &value) == 0);
    assert(file_get(file, 100, &value) == 0);
    assert(value == 777);
    fclose(file);
}

static void test_set(void)
{
    const int values[] = { 1, 2, 3 };
    FILE* file = file_with(values, 3);
    int value = 0;

    assert(file_set(file, 1, 42) == 1);
    assert(file_get(file, 1, &value) == 1 && value == 42);
    assert(file_set(file, 0, -5) == 1);
    assert(file_set(file, 2, 99) == 1);
    assert_contents(file, (int[]) { -5, 42, 99 }, 3);
    fclose(file);
}

static void test_set_out_of_range(void)
{
    const int values[] = { 1, 2, 3 };
    FILE* file = file_with(values, 3);

    assert(file_set(file, 3, 7) == 0);
    assert(file_set(file, -1, 7) == 0);
    assert(file_int_count(file) == 3);
    assert_contents(file, values, 3);
    fclose(file);
}

static void test_reverse(void)
{
    const int even[] = { 1, 2, 3, 4 };
    const int odd[] = { 1, 2, 3, 4, 5 };
    const int one[] = { 7 };
    FILE* file = file_with(even, 4);

    assert(file_reverse(file) == 1);
    assert_contents(file, (int[]) { 4, 3, 2, 1 }, 4);
    fclose(file);

    file = file_with(odd, 5);
    assert(file_reverse(file) == 1);
    assert_contents(file, (int[]) { 5, 4, 3, 2, 1 }, 5);
    fclose(file);

    file = file_with(one, 1);
    assert(file_reverse(file) == 1);
    assert_contents(file, one, 1);
    fclose(file);

    file = file_with(one, 0);
    assert(file_reverse(file) == 1);
    assert(file_int_count(file) == 0);
    fclose(file);
}

static void test_mixed_operations(void)
{
    const int values[] = { 5, 6, 7, 8, 9, 10 };
    FILE* file = file_with(values, 6);
    int value = 0;

    /* Чтение и запись вперемешку: без fseek между ними файл испортится. */
    for (long i = 0; i < 6; i++) {
        assert(file_get(file, i, &value) == 1);
        assert(file_set(file, 5 - i, value * 10) == 1);
    }
    assert(file_int_count(file) == 6);
    assert_contents(file, (int[]) { 500, 600, 700, 70, 60, 50 }, 6);
    fclose(file);
}

static void test_large_is_fast(void)
{
    size_t count = 200000;
    int* values = malloc(count * sizeof(int));
    FILE* file = NULL;
    int value = 0;

    assert(values != NULL);
    for (size_t i = 0; i < count; i++) {
        values[i] = (int)i;
    }
    file = file_with(values, count);

    signal(SIGALRM, too_slow);
    alarm(TIME_LIMIT_SECONDS);
    assert(file_int_count(file) == (long)count);
    assert(file_reverse(file) == 1);
    alarm(0);

    assert(file_get(file, 0, &value) == 1 && value == (int)count - 1);
    assert(file_get(file, (long)count - 1, &value) == 1 && value == 0);
    assert(file_get(file, 12345, &value) == 1 && value == (int)count - 1 - 12345);
    fclose(file);
    free(values);
}

int main(void)
{
    test_count();
    test_count_broken_size();
    test_get();
    test_set();
    test_set_out_of_range();
    test_reverse();
    test_mixed_operations();
    test_large_is_fast();

    puts("All tests passed");
    return 0;
}
