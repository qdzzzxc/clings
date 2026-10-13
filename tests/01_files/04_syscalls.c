/* Тесты к exercises/01_files/04_syscalls.c. Запуск: make test 1 4 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/01_files/04_syscalls.c"
#undef main

#define FROM_PATH ".build/syscalls_from.bin"
#define TO_PATH ".build/syscalls_to.bin"

/* Номер следующего свободного дескриптора: если он вырос, кто-то не закрыл файл. */
static int next_free_fd(void)
{
    int fd = dup(STDIN_FILENO);

    assert(fd >= 0);
    close(fd);
    return fd;
}

static void write_file(const char* path, const unsigned char* data, size_t size)
{
    FILE* out = fopen(path, "wb");

    assert(out != NULL);
    assert(fwrite(data, 1, size, out) == size);
    assert(fclose(out) == 0);
}

static int file_equals(const char* path, const unsigned char* data, size_t size)
{
    FILE* in = fopen(path, "rb");
    unsigned char* buffer = malloc(size + 1);
    size_t read_size = 0;
    int equal = 0;

    assert(in != NULL && buffer != NULL);
    read_size = fread(buffer, 1, size + 1, in);
    equal = read_size == size && memcmp(buffer, data, size) == 0;
    fclose(in);
    free(buffer);
    return equal;
}

static void check_copy(size_t size)
{
    unsigned char* data = malloc(size + 1);
    int fd_before = next_free_fd();

    assert(data != NULL);
    for (size_t i = 0; i < size; i++) {
        data[i] = (unsigned char)(i * 31 + i / 7);
    }
    write_file(FROM_PATH, data, size);

    assert(copy_file(FROM_PATH, TO_PATH) == (long)size);
    assert(file_equals(TO_PATH, data, size));
    assert(next_free_fd() == fd_before);

    remove(FROM_PATH);
    remove(TO_PATH);
    free(data);
}

static void test_sizes(void)
{
    check_copy(0);
    check_copy(1);
    check_copy(100);
    check_copy(BUFFER_SIZE - 1);
    check_copy(BUFFER_SIZE);
    check_copy(BUFFER_SIZE + 1);
    check_copy(3 * BUFFER_SIZE + 17);
    check_copy(1000000);
}

static void test_zero_bytes_inside(void)
{
    const unsigned char data[] = { 'a', 0, 'b', 0, 0, 'c', '\n', 255 };

    write_file(FROM_PATH, data, sizeof(data));
    assert(copy_file(FROM_PATH, TO_PATH) == (long)sizeof(data));
    assert(file_equals(TO_PATH, data, sizeof(data)));
    remove(FROM_PATH);
    remove(TO_PATH);
}

static void test_overwrites_longer_file(void)
{
    const unsigned char long_data[] = "a much longer old content";
    const unsigned char short_data[] = "new";

    write_file(TO_PATH, long_data, sizeof(long_data) - 1);
    write_file(FROM_PATH, short_data, sizeof(short_data) - 1);
    assert(copy_file(FROM_PATH, TO_PATH) == 3);
    assert(file_equals(TO_PATH, short_data, 3));
    remove(FROM_PATH);
    remove(TO_PATH);
}

static void test_missing_source(void)
{
    int fd_before = next_free_fd();

    remove(TO_PATH);
    assert(copy_file(".build/no_such_file.bin", TO_PATH) == -1);
    assert(next_free_fd() == fd_before);
}

static void test_bad_destination(void)
{
    const unsigned char data[] = "data";
    int fd_before = next_free_fd();

    write_file(FROM_PATH, data, 4);
    assert(copy_file(FROM_PATH, ".build/no_such_directory/file.bin") == -1);
    /* Источник открылся, а приёмник нет: источник всё равно надо закрыть. */
    assert(next_free_fd() == fd_before);
    remove(FROM_PATH);
}

static void test_source_is_directory(void)
{
    int fd_before = next_free_fd();

    /* Каталог открывается на чтение, но read из него даёт ошибку. */
    assert(copy_file(".build", TO_PATH) == -1);
    assert(next_free_fd() == fd_before);
    remove(TO_PATH);
}

int main(void)
{
    test_sizes();
    test_zero_bytes_inside();
    test_overwrites_longer_file();
    test_missing_source();
    test_bad_destination();
    test_source_is_directory();

    puts("All tests passed");
    return 0;
}
