/* Тесты к exercises/algo/04_has_loop.c. Запуск: make test algo 4 */

#include <assert.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/algo/04_has_loop.c"
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

/* Связывает nodes[0..n) в список. loop_to < 0 — без цикла,
   иначе последний узел указывает на nodes[loop_to]. */
static void build_list(Node* nodes, int n, int loop_to)
{
    for (int i = 0; i < n; i++) {
        nodes[i].value = i;
        nodes[i].next = i + 1 < n ? &nodes[i + 1] : NULL;
    }
    if (loop_to >= 0) {
        nodes[n - 1].next = &nodes[loop_to];
    }
}

/* Проверяет, что список не изменился. */
static void assert_intact(const Node* nodes, int n, int loop_to)
{
    for (int i = 0; i < n; i++) {
        const Node* expected = i + 1 < n ? &nodes[i + 1] : loop_to >= 0 ? &nodes[loop_to]
                                                                        : NULL;

        assert(nodes[i].value == i);
        assert(nodes[i].next == expected);
    }
}

static void check(Node* nodes, int n, int loop_to)
{
    build_list(nodes, n, loop_to);
    assert(hasLoop(&nodes[0]) == (loop_to >= 0));
    assert_intact(nodes, n, loop_to);
}

static void test_empty(void)
{
    assert(!hasLoop(NULL));
}

static void test_one_node(void)
{
    Node nodes[1] = { { 0, NULL } };

    check(nodes, 1, -1);
    check(nodes, 1, 0);
}

static void test_two_nodes(void)
{
    Node nodes[2] = { { 0, NULL }, { 0, NULL } };

    check(nodes, 2, -1);
    check(nodes, 2, 0);
    check(nodes, 2, 1);
}

static void test_example(void)
{
    Node nodes[3] = { { 0, NULL }, { 0, NULL }, { 0, NULL } };

    check(nodes, 3, -1);
    check(nodes, 3, 1);
}

static void test_all_shapes(void)
{
    Node nodes[40] = { { 0, NULL } };

    for (int n = 1; n <= 40; n++) {
        check(nodes, n, -1);
        for (int loop_to = 0; loop_to < n; loop_to++) {
            check(nodes, n, loop_to);
        }
    }
}

static void test_long_lists_are_fast(void)
{
    int n = 1000000;
    Node* nodes = malloc((size_t)n * sizeof(Node));

    assert(nodes != NULL);
    signal(SIGALRM, too_slow);
    alarm(TIME_LIMIT_SECONDS);
    check(nodes, n, -1);
    check(nodes, n, 0);
    check(nodes, n, n / 2);
    check(nodes, n, n - 1);
    alarm(0);
    free(nodes);
}

int main(void)
{
    CHECK_RULES();

    test_empty();
    test_one_node();
    test_two_nodes();
    test_example();
    test_all_shapes();
    test_long_lists_are_fast();

    puts("All tests passed");
    return 0;
}
