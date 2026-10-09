/* Тесты к exercises/00_basics/02_for_loop.c. Запуск: make test 0 2 */

#include <assert.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/00_basics/02_for_loop.c"
#undef main

static void test_small(void)
{
    int count = 0;
    int sum = 0;

    calc(1, &count, &sum);

    assert(count == 0);
    assert(sum == 0);
}

static void test_ten(void)
{
    int count = 0;
    int sum = 0;

    calc(10, &count, &sum);

    assert(count == 5);
    assert(sum == 33);
}

static void test_fifteen(void)
{
    int count = 0;
    int sum = 0;

    calc(15, &count, &sum);

    assert(count == 6);
    assert(sum == 45);
}

static void test_twenty(void)
{
    int count = 0;
    int sum = 0;

    calc(20, &count, &sum);

    assert(count == 8);
    assert(sum == 83);
}

static void test_boundaries(void)
{
    int count = 0;
    int sum = 0;

    calc(3, &count, &sum);

    assert(count == 1);
    assert(sum == 3);

    calc(5, &count, &sum);

    assert(count == 2);
    assert(sum == 8);
}

static void test_thirty(void)
{
    int count = 0;
    int sum = 0;

    calc(30, &count, &sum);

    assert(count == 12);
    assert(sum == 180);
}

static void test_overwrites_previous_values(void)
{
    int count = 123;
    int sum = -456;

    calc(10, &count, &sum);

    assert(count == 5);
    assert(sum == 33);
}

int main(void)
{
    test_small();
    test_ten();
    test_fifteen();
    test_twenty();

    test_boundaries();
    test_thirty();
    test_overwrites_previous_values();

    puts("All tests passed");
    return 0;
}
