/* Тесты к exercises/02_memory/00_static.c. Запуск: make test 2 0 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/02_memory/00_static.c"
#undef main

static void test_ids_grow(void)
{
    reset_ids();

    assert(next_id() == 1);
    assert(next_id() == 2);
    assert(next_id() == 3);
}

static void test_reset(void)
{
    reset_ids();
    next_id();
    next_id();

    reset_ids();
    assert(next_id() == 1);

    reset_ids();
    reset_ids();
    assert(next_id() == 1);
    assert(next_id() == 2);
}

static void test_many_ids(void)
{
    reset_ids();

    for (unsigned expected = 1; expected <= 1000; expected++) {
        assert(next_id() == expected);
    }
}

static void test_day_names(void)
{
    const char* expected[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

    for (int day = 1; day <= 7; day++) {
        assert(day_name(day) != NULL);
        assert(strcmp(day_name(day), expected[day - 1]) == 0);
    }
}

static void test_unknown_days(void)
{
    assert(day_name(0) == NULL);
    assert(day_name(8) == NULL);
    assert(day_name(-1) == NULL);
    assert(day_name(100) == NULL);
}

static void test_same_pointer_every_time(void)
{
    const char* first = day_name(3);
    const char* other = day_name(5);

    assert(day_name(3) == first);
    assert(strcmp(first, "Wed") == 0);
    assert(strcmp(other, "Fri") == 0);
}

int main(void)
{
    test_ids_grow();
    test_reset();
    test_many_ids();
    test_day_names();
    test_unknown_days();
    test_same_pointer_every_time();

    puts("All tests passed");
    return 0;
}
