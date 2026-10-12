/* Тесты к exercises/algo/01_stock_profit.c. Запуск: make test algo 1 */

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/algo/01_stock_profit.c"
#undef main

#include "rules.h"

#define TIME_LIMIT_SECONDS 1

static void too_slow(int signal_number)
{
    static const char message[] = "Too slow: time limit exceeded\n";
    ssize_t written = write(STDERR_FILENO, message, sizeof(message) - 1);

    (void)signal_number;
    (void)written;
    _exit(1);
}

static int run(const char* input)
{
    FILE* in = tmpfile();
    int result = 0;

    assert(in != NULL);
    fputs(input, in);
    rewind(in);
    result = maxProfit(in);
    fclose(in);
    return result;
}

static int reference(const int* prices, int n)
{
    int best = 0;
    int low = prices[0];

    for (int i = 1; i < n; i++) {
        if (prices[i] - low > best) {
            best = prices[i] - low;
        }
        if (prices[i] < low) {
            low = prices[i];
        }
    }
    return best;
}

/* Пишет n цен во временный файл, запускает решение и сверяет с эталоном. */
static void check(const int* prices, int n)
{
    FILE* in = tmpfile();

    assert(in != NULL);
    fprintf(in, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(in, i + 1 < n ? "%d " : "%d\n", prices[i]);
    }
    rewind(in);
    assert(maxProfit(in) == reference(prices, n));
    fclose(in);
}

static void test_examples(void)
{
    assert(run("6\n7 1 5 3 6 4\n") == 5);
    assert(run("5\n7 6 4 3 1\n") == 0);
}

static void test_one_day(void)
{
    assert(run("1\n5\n") == 0);
    assert(run("1\n0\n") == 0);
}

static void test_simple(void)
{
    assert(run("2\n1 2\n") == 1);
    assert(run("2\n2 1\n") == 0);
    assert(run("4\n3 3 3 3\n") == 0);
    assert(run("5\n1 2 3 4 5\n") == 4);
    assert(run("3\n0 10000 0\n") == 10000);
}

static void test_minimum_is_not_first(void)
{
    /* Самая низкая цена позже самой высокой: купить на ней уже нечего. */
    assert(run("6\n5 9 1 2 3 0\n") == 4);
    assert(run("6\n3 8 1 4 2 7\n") == 6);
    assert(run("5\n2 4 1 9 0\n") == 8);
}

static void test_reads_exactly_n(void)
{
    assert(run("3\n5 3 4\n100 200\n") == 1);
    assert(run("2\n9 1 100\n") == 0);
}

static void test_whitespace(void)
{
    assert(run("  4\n\n 1\n  3\t2\n\n5") == 4);
}

static void test_random(void)
{
    int prices[200] = { 0 };
    unsigned state = 12345;

    for (int round = 0; round < 500; round++) {
        int n = 1 + round % 200;

        for (int i = 0; i < n; i++) {
            state = state * 1103515245u + 12345u;
            prices[i] = (int)(state >> 8) % (round % 2 == 0 ? 10001 : 20);
        }
        check(prices, n);
    }
}

static void test_large_is_fast(void)
{
    int n = 100000;
    int* prices = malloc((size_t)n * sizeof(int));

    assert(prices != NULL);
    for (int i = 0; i < n; i++) {
        prices[i] = (int)((unsigned)i * 7919u % 10001u);
    }
    signal(SIGALRM, too_slow);
    alarm(TIME_LIMIT_SECONDS);
    check(prices, n);
    for (int i = 0; i < n; i++) {
        prices[i] = 10000 - i / 10;
    }
    check(prices, n);
    alarm(0);
    free(prices);
}

int main(void)
{
    CHECK_RULES();

    test_examples();
    test_one_day();
    test_simple();
    test_minimum_is_not_first();
    test_reads_exactly_n();
    test_whitespace();
    test_random();
    test_large_is_fast();

    puts("All tests passed");
    return 0;
}
