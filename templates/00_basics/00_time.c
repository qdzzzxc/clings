/*
# Task 1 — Time split

Написать программу, которая получает неотрицательное количество секунд
и раскладывает его на:

- days
- hours
- minutes
- seconds

## Example

Input:
90061

Output:
1 1 1 1

## Requirements

- Использовать целочисленные типы.
- Программа должна корректно работать как минимум со значением 4000000000.
- Проверять успешность чтения через возвращаемое значение `scanf`.
- Не использовать `float` и `double`.
- Количество секунд в минуте, часе и дне задать именованными константами.
- Логику разложения вынести из `main` в функцию `split_time`.
- `split_time` должна вернуть четыре результата через указатели.
- `main` отвечает только за ввод, вызов функции и вывод результата.

Формат вывода:

days hours minutes seconds
*/

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

const unsigned int SECONDS_IN_MINUTE = 60;
const unsigned int SECONDS_IN_HOUR = SECONDS_IN_MINUTE * 60;
const unsigned int SECONDS_IN_DAY = SECONDS_IN_HOUR * 24;

void split_time(uint64_t total_seconds,
    uint64_t* days,
    uint64_t* hours,
    uint64_t* minutes,
    uint64_t* seconds)
{
    /* TODO: реализуйте split_time. */
    (void)total_seconds;
    (void)days;
    (void)hours;
    (void)minutes;
    (void)seconds;
    assert(!"TODO: split_time");
}

#ifndef TEST

int main(void)
{
    uint64_t total_seconds = 0;
    uint64_t days = 0;
    uint64_t hours = 0;
    uint64_t minutes = 0;
    uint64_t seconds = 0;

    if (scanf("%lu", &total_seconds) != 1) {
        return 1;
    }

    split_time(total_seconds, &days, &hours, &minutes, &seconds);

    printf("days: %lu\nhours: %lu\nminutes: %lu\nseconds: %lu\n", days, hours, minutes, seconds);

    return 0;
}

#else

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

int main(void)
{
    test_zero();
    test_seconds_only();
    test_one_minute();
    test_one_hour();
    test_one_day();
    test_mixed();
    test_large_value();

    puts("All tests passed");
    return 0;
}

#endif
