/* Тесты к exercises/02_memory/03_push_back.c. Запуск: make test 2 3 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* realloc в решении подменяется: тест может заставить его вернуть NULL. */
static int realloc_should_fail = 0;

void* test_realloc(void* ptr, size_t size)
{
    if (realloc_should_fail) {
        return NULL;
    }
    return realloc(ptr, size);
}

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define realloc test_realloc
#define main demo_main
#include "../../exercises/02_memory/03_push_back.c"
#undef main
#undef realloc

static void test_first_push(void)
{
    size_t size = 0;
    size_t capacity = 0;
    int* data = push_back(NULL, &size, &capacity, 42);

    assert(data != NULL);
    assert(size == 1);
    assert(capacity == 1);
    assert(data[0] == 42);

    free(data);
}

static void test_capacity_doubles(void)
{
    int* data = NULL;
    size_t size = 0;
    size_t capacity = 0;
    size_t expected_capacity = 0;

    for (int i = 0; i < 1000; i++) {
        data = push_back(data, &size, &capacity, i * 3);
        assert(data != NULL);

        if (expected_capacity < size) {
            expected_capacity = expected_capacity == 0 ? 1 : expected_capacity * 2;
        }

        assert(size == (size_t)i + 1);
        assert(capacity == expected_capacity);
    }

    assert(capacity == 1024);
    for (int i = 0; i < 1000; i++) {
        assert(data[i] == i * 3);
    }

    free(data);
}

static void test_no_growth_when_there_is_room(void)
{
    size_t size = 1;
    size_t capacity = 4;
    int* data = malloc(4 * sizeof(int));

    assert(data != NULL);
    data[0] = 10;

    data = push_back(data, &size, &capacity, 20);

    assert(data != NULL);
    assert(size == 2);
    assert(capacity == 4);
    assert(data[0] == 10);
    assert(data[1] == 20);

    free(data);
}

static FILE* stream_with(const char* text)
{
    FILE* in = tmpfile();

    assert(in != NULL);
    fputs(text, in);
    rewind(in);
    return in;
}

static void test_failed_realloc_keeps_array(void)
{
    int* data = NULL;
    size_t size = 0;
    size_t capacity = 0;

    data = push_back(data, &size, &capacity, 1);
    assert(data != NULL);
    data = push_back(data, &size, &capacity, 2);
    assert(data != NULL);
    assert(size == 2 && capacity == 2);

    /* Места нет, realloc отказывает: массив остаётся прежним. */
    realloc_should_fail = 1;
    assert(push_back(data, &size, &capacity, 3) == NULL);
    realloc_should_fail = 0;

    assert(size == 2);
    assert(capacity == 2);
    assert(data[0] == 1 && data[1] == 2);

    free(data);
}

static void test_read_ints(void)
{
    FILE* in = stream_with("5 4\n3 -2 1\n");
    size_t size = 777;
    int* data = read_ints(in, &size);

    fclose(in);

    assert(data != NULL);
    assert(size == 5);
    assert(data[0] == 5);
    assert(data[1] == 4);
    assert(data[2] == 3);
    assert(data[3] == -2);
    assert(data[4] == 1);

    free(data);
}

static void test_read_nothing(void)
{
    FILE* in = stream_with("  \n");
    size_t size = 777;
    int* data = read_ints(in, &size);

    fclose(in);

    assert(data == NULL);
    assert(size == 0);
}

static void test_read_stops_at_garbage(void)
{
    FILE* in = stream_with("1 2 stop 3");
    size_t size = 777;
    int* data = read_ints(in, &size);

    fclose(in);

    assert(data != NULL);
    assert(size == 2);
    assert(data[0] == 1);
    assert(data[1] == 2);

    free(data);
}

static void test_read_many(void)
{
    FILE* in = tmpfile();
    size_t size = 777;
    int* data;

    assert(in != NULL);
    for (int i = 0; i < 5000; i++) {
        fprintf(in, "%d\n", i - 2500);
    }
    rewind(in);

    data = read_ints(in, &size);
    fclose(in);

    assert(data != NULL);
    assert(size == 5000);
    for (int i = 0; i < 5000; i++) {
        assert(data[i] == i - 2500);
    }

    free(data);
}

int main(void)
{
    test_first_push();
    test_capacity_doubles();
    test_no_growth_when_there_is_room();
    test_failed_realloc_keeps_array();
    test_read_ints();
    test_read_nothing();
    test_read_stops_at_garbage();
    test_read_many();

    puts("All tests passed");
    return 0;
}
