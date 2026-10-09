/* Тесты к exercises/01_files/03_binary.c. Запуск: make test 1 3 */

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/01_files/03_binary.c"
#undef main

#define TEST_PATH ".build/binary_test.bin"

static long file_size(const char* path)
{
    FILE* in = fopen(path, "rb");
    long size;

    assert(in != NULL);
    fseek(in, 0, SEEK_END);
    size = ftell(in);
    fclose(in);
    return size;
}

static void test_round_trip(void)
{
    int values[] = { 1, -2, INT_MAX, INT_MIN, 0 };
    int loaded[5] = { 9, 9, 9, 9, 9 };
    size_t count = 777;

    assert(save_ints(TEST_PATH, values, 5));
    assert(file_size(TEST_PATH) == (long)(sizeof(uint32_t) + 5 * sizeof(int)));

    assert(load_ints(TEST_PATH, loaded, 5, &count));
    assert(count == 5);
    for (size_t i = 0; i < 5; i++) {
        assert(loaded[i] == values[i]);
    }

    remove(TEST_PATH);
}

static void test_empty_array(void)
{
    int values[1] = { 0 };
    int loaded[1] = { 9 };
    size_t count = 777;

    assert(save_ints(TEST_PATH, values, 0));
    assert(file_size(TEST_PATH) == (long)sizeof(uint32_t));

    assert(load_ints(TEST_PATH, loaded, 1, &count));
    assert(count == 0);

    remove(TEST_PATH);
}

static void test_save_overwrites_old_file(void)
{
    int first[] = { 1, 2, 3, 4 };
    int second[] = { 7 };
    int loaded[4];
    size_t count = 777;

    assert(save_ints(TEST_PATH, first, 4));
    assert(save_ints(TEST_PATH, second, 1));

    assert(load_ints(TEST_PATH, loaded, 4, &count));
    assert(count == 1);
    assert(loaded[0] == 7);

    remove(TEST_PATH);
}

static void test_capacity_too_small(void)
{
    int values[] = { 1, 2, 3 };
    int loaded[3];
    size_t count = 777;

    assert(save_ints(TEST_PATH, values, 3));
    assert(!load_ints(TEST_PATH, loaded, 2, &count));
    assert(load_ints(TEST_PATH, loaded, 3, &count));

    remove(TEST_PATH);
}

static void test_missing_file(void)
{
    int loaded[1];
    size_t count = 777;

    assert(!load_ints(".build/no_such_file.bin", loaded, 1, &count));
}

static void test_cannot_create_file(void)
{
    int values[] = { 1 };

    assert(!save_ints(".build/no_such_directory/file.bin", values, 1));
}

static void test_truncated_file(void)
{
    uint32_t promised = 5;
    int actual[] = { 1, 2 };
    int loaded[5];
    size_t count = 777;
    FILE* out = fopen(TEST_PATH, "wb");

    /* В заголовке обещано 5 элементов, а записано только 2. */
    assert(out != NULL);
    assert(fwrite(&promised, sizeof(promised), 1, out) == 1);
    assert(fwrite(actual, sizeof(int), 2, out) == 2);
    fclose(out);

    assert(!load_ints(TEST_PATH, loaded, 5, &count));

    remove(TEST_PATH);
}

static void test_file_without_header(void)
{
    int loaded[1];
    size_t count = 777;
    FILE* out = fopen(TEST_PATH, "wb");

    assert(out != NULL);
    fputc('x', out);
    fclose(out);

    assert(!load_ints(TEST_PATH, loaded, 1, &count));

    remove(TEST_PATH);
}

int main(void)
{
    test_round_trip();
    test_empty_array();
    test_save_overwrites_old_file();
    test_capacity_too_small();
    test_missing_file();
    test_cannot_create_file();
    test_truncated_file();
    test_file_without_header();

    puts("All tests passed");
    return 0;
}
