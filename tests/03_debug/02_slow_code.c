/* Тесты к exercises/03_debug/02_slow_code.c. Запуск: make test 3 2 */

#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/03_debug/02_slow_code.c"
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

/* Если до stop_timer пройдёт больше TIME_LIMIT_SECONDS, тест завершится. */
static void start_timer(void)
{
    signal(SIGALRM, too_slow);
    alarm(TIME_LIMIT_SECONDS);
}

static void stop_timer(void)
{
    alarm(0);
}

static void test_to_upper(void)
{
    char text[] = "Hello, World 123!";
    char empty[] = "";

    to_upper(text);
    to_upper(empty);

    assert(strcmp(text, "HELLO, WORLD 123!") == 0);
    assert(empty[0] == '\0');
}

static void test_to_upper_is_fast(void)
{
    size_t length = 2000000;
    char* text = malloc(length + 1);

    assert(text != NULL);
    memset(text, 'a', length);
    text[length] = '\0';

    start_timer();
    to_upper(text);
    stop_timer();

    assert(text[0] == 'A');
    assert(text[length / 2] == 'A');
    assert(text[length - 1] == 'A');
    assert(text[length] == '\0');

    free(text);
}

static void test_repeat(void)
{
    char* line = repeat("ab", 3);
    char* nothing = repeat("ab", 0);
    char* empty = repeat("", 4);

    assert(line != NULL && nothing != NULL && empty != NULL);
    assert(strcmp(line, "ababab") == 0);
    assert(strcmp(nothing, "") == 0);
    assert(strcmp(empty, "") == 0);

    free(line);
    free(nothing);
    free(empty);
}

static void test_repeat_is_fast(void)
{
    size_t times = 1000000;
    char* line;

    start_timer();
    line = repeat("abc", times);
    stop_timer();

    assert(line != NULL);
    assert(strlen(line) == 3 * times);
    assert(strncmp(line, "abcabc", 6) == 0);
    assert(strcmp(line + 3 * times - 6, "abcabc") == 0);

    free(line);
}

static void test_count_distinct(void)
{
    int values[] = { 5, 1, 5, 2, 1, 5, 0, MAX_VALUE, MAX_VALUE };
    int same[] = { 7, 7, 7 };

    assert(count_distinct(values, 9) == 5);
    assert(count_distinct(same, 3) == 1);
    assert(count_distinct(same, 1) == 1);
    assert(count_distinct(same, 0) == 0);
}

static void test_count_distinct_is_fast(void)
{
    size_t size = 400000;
    int* values = malloc(size * sizeof(int));
    size_t distinct;

    /* Первая половина — нули, вторая — все значения от 1 до MAX_VALUE по кругу. */
    assert(values != NULL);
    for (size_t i = 0; i < size; i++) {
        values[i] = i < size / 2 ? 0 : (int)(i % MAX_VALUE) + 1;
    }

    start_timer();
    distinct = count_distinct(values, size);
    stop_timer();

    assert(distinct == MAX_VALUE + 1);

    free(values);
}

int main(void)
{
    test_to_upper();
    test_to_upper_is_fast();
    test_repeat();
    test_repeat_is_fast();
    test_count_distinct();
    test_count_distinct_is_fast();

    puts("All tests passed");
    return 0;
}
