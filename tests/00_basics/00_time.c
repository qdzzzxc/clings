/* Тесты к exercises/00_basics/00_time.c. Запуск: make test 0 0 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/00_basics/00_time.c"
#undef main

static void test_zero(void)
{
    uint64_t days;
    uint64_t hours;
    uint64_t minutes;
    uint64_t seconds;

    split_time(0, &days, &hours, &minutes, &seconds);

    assert(days == 0);
    assert(hours == 0);
    assert(minutes == 0);
    assert(seconds == 0);
}

static void test_seconds_only(void)
{
    uint64_t days;
    uint64_t hours;
    uint64_t minutes;
    uint64_t seconds;

    split_time(59, &days, &hours, &minutes, &seconds);

    assert(days == 0);
    assert(hours == 0);
    assert(minutes == 0);
    assert(seconds == 59);
}

static void test_one_minute(void)
{
    uint64_t days;
    uint64_t hours;
    uint64_t minutes;
    uint64_t seconds;

    split_time(60, &days, &hours, &minutes, &seconds);

    assert(days == 0);
    assert(hours == 0);
    assert(minutes == 1);
    assert(seconds == 0);
}

static void test_one_hour(void)
{
    uint64_t days;
    uint64_t hours;
    uint64_t minutes;
    uint64_t seconds;

    split_time(3600, &days, &hours, &minutes, &seconds);

    assert(days == 0);
    assert(hours == 1);
    assert(minutes == 0);
    assert(seconds == 0);
}

static void test_one_day(void)
{
    uint64_t days;
    uint64_t hours;
    uint64_t minutes;
    uint64_t seconds;

    split_time(86400, &days, &hours, &minutes, &seconds);

    assert(days == 1);
    assert(hours == 0);
    assert(minutes == 0);
    assert(seconds == 0);
}

static void test_mixed(void)
{
    uint64_t days;
    uint64_t hours;
    uint64_t minutes;
    uint64_t seconds;

    split_time(90061, &days, &hours, &minutes, &seconds);

    assert(days == 1);
    assert(hours == 1);
    assert(minutes == 1);
    assert(seconds == 1);
}

static void test_large_value(void)
{
    uint64_t days;
    uint64_t hours;
    uint64_t minutes;
    uint64_t seconds;

    split_time(4000000000ULL, &days, &hours, &minutes, &seconds);

    assert(days == 46296);
    assert(hours == 7);
    assert(minutes == 6);
    assert(seconds == 40);
}

static void test_last_second_of_day(void)
{
    uint64_t days = 99;
    uint64_t hours = 99;
    uint64_t minutes = 99;
    uint64_t seconds = 99;

    split_time(86399, &days, &hours, &minutes, &seconds);

    assert(days == 0);
    assert(hours == 23);
    assert(minutes == 59);
    assert(seconds == 59);
}

static void test_max_value(void)
{
    uint64_t days = 99;
    uint64_t hours = 99;
    uint64_t minutes = 99;
    uint64_t seconds = 99;

    split_time(UINT64_MAX, &days, &hours, &minutes, &seconds);

    assert(days == 213503982334601ULL);
    assert(hours == 7);
    assert(minutes == 0);
    assert(seconds == 15);
}

int main(void)
{
    test_zero();
    test_seconds_only();
    test_one_minute();
    test_one_hour();
    test_one_day();
    test_mixed();
    test_large_value();

    test_last_second_of_day();
    test_max_value();

    puts("All tests passed");
    return 0;
}
