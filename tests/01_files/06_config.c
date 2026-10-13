/* Тесты к exercises/01_files/06_config.c. Запуск: make test 1 6 */

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/01_files/06_config.c"
#undef main

#define TEST_PATH ".build/config_test.conf"
#define CAPACITY 8

static ConfigEntry entries[CAPACITY];
static char error_text[512];

static void write_config(const char* text)
{
    FILE* out = fopen(TEST_PATH, "w");

    assert(out != NULL);
    assert(fputs(text, out) != EOF);
    assert(fclose(out) == 0);
}

static int next_free_fd(void)
{
    int fd = dup(STDIN_FILENO);

    assert(fd >= 0);
    close(fd);
    return fd;
}

/* Загружает config, сообщения об ошибках собирает в error_text. */
static int load(const char* path, size_t capacity, size_t* count)
{
    FILE* errors = tmpfile();
    size_t length = 0;
    int fd_before = next_free_fd();
    int result = 0;

    assert(errors != NULL);
    memset(entries, 'x', sizeof(entries));
    result = config_load(path, entries, capacity, count, errors);
    rewind(errors);
    length = fread(error_text, 1, sizeof(error_text) - 1, errors);
    error_text[length] = '\0';
    /* errors ещё открыт: он занял дескриптор до замера. */
    assert(next_free_fd() == fd_before);
    fclose(errors);
    return result;
}

static size_t load_ok(const char* text)
{
    size_t count = 999;

    write_config(text);
    assert(load(TEST_PATH, CAPACITY, &count) == 1);
    assert(error_text[0] == '\0');
    return count;
}

/* Ошибка в строке line: сообщение начинается с "<path>:<line>:". */
static void check_line_error(const char* text, size_t capacity, int line)
{
    char prefix[64] = "";
    size_t count = 999;

    write_config(text);
    snprintf(prefix, sizeof(prefix), "%s:%d:", TEST_PATH, line);
    assert(load(TEST_PATH, capacity, &count) == 0);
    assert(count == 999);
    assert(strncmp(error_text, prefix, strlen(prefix)) == 0);
    assert(strchr(error_text, '\n') == error_text + strlen(error_text) - 1);
}

static void test_example(void)
{
    size_t count = load_ok("# настройки сервера\nhost = example.com\nport = 8080\n\nname = My server\n");

    assert(count == 3);
    assert(strcmp(entries[0].key, "host") == 0 && strcmp(entries[0].value, "example.com") == 0);
    assert(strcmp(entries[1].key, "port") == 0 && strcmp(entries[1].value, "8080") == 0);
    assert(strcmp(config_get(entries, count, "name"), "My server") == 0);
    assert(strcmp(config_get(entries, count, "port"), "8080") == 0);
    assert(config_get(entries, count, "missing") == NULL);
    assert(config_get(entries, count, "hos") == NULL);
}

static void test_spaces(void)
{
    size_t count = load_ok("  \t key1=value1  \n\tkey2   =   a  b  c\t\n   # comment with = inside\n\t\n");

    assert(count == 2);
    assert(strcmp(config_get(entries, count, "key1"), "value1") == 0);
    assert(strcmp(config_get(entries, count, "key2"), "a  b  c") == 0);
}

static void test_values(void)
{
    size_t count = load_ok("empty =\nequals = a=b=c\nlast = no newline");

    assert(count == 3);
    assert(strcmp(config_get(entries, count, "empty"), "") == 0);
    assert(strcmp(config_get(entries, count, "equals"), "a=b=c") == 0);
    assert(strcmp(config_get(entries, count, "last"), "no newline") == 0);
}

static void test_duplicate_key(void)
{
    size_t count = load_ok("mode = slow\nmode = fast\n");

    assert(strcmp(config_get(entries, count, "mode"), "fast") == 0);
}

static void test_empty_file(void)
{
    assert(load_ok("") == 0);
    assert(load_ok("# only comments\n\n   \n") == 0);
}

static void test_limits(void)
{
    /* Ключ из 31 символа и значение из 63 помещаются. */
    size_t count = load_ok("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk = "
                           "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n");

    assert(count == 1);
    assert(strlen(entries[0].key) == 31 && strlen(entries[0].value) == 63);
}

static void test_line_errors(void)
{
    check_line_error("no equals sign\n", CAPACITY, 1);
    check_line_error("a = 1\n\n# c\n= value\n", CAPACITY, 4);
    check_line_error("a = 1\nbad key = 2\n", CAPACITY, 2);
    check_line_error("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk = 1\n", CAPACITY, 1);
    check_line_error("k = vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n", CAPACITY, 1);
    check_line_error("a = 1\nb = 2\nc = 3\n", 2, 3);
}

static void test_missing_file(void)
{
    char expected[256] = "";
    size_t count = 999;

    remove(".build/no_such_config.conf");
    snprintf(expected, sizeof(expected), ".build/no_such_config.conf: %s\n", strerror(ENOENT));
    assert(load(".build/no_such_config.conf", CAPACITY, &count) == 0);
    assert(count == 999);
    assert(strcmp(error_text, expected) == 0);
}

int main(void)
{
    test_example();
    test_spaces();
    test_values();
    test_duplicate_key();
    test_empty_file();
    test_limits();
    test_line_errors();
    test_missing_file();

    remove(TEST_PATH);
    puts("All tests passed");
    return 0;
}
