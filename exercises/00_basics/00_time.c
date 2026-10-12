/*
# Task 0 — Time split

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
days: 1
hours: 1
minutes: 1
seconds: 1

## Requirements

- Использовать целочисленные типы.
- Программа должна корректно работать как минимум со значением 4000000000.
- Проверять успешность чтения через возвращаемое значение `scanf`.
- Не использовать `float` и `double`.
- Количество секунд в минуте, часе и дне задать именованными константами.
- Логику разложения вынести из `main` в функцию `split_time`.
- `split_time` должна вернуть четыре результата через указатели.
- `main` отвечает только за ввод, вызов функции и вывод результата.
*/

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#define SECONDS_IN_MINUTE 60U
#define SECONDS_IN_HOUR (SECONDS_IN_MINUTE * 60U)
#define SECONDS_IN_DAY (SECONDS_IN_HOUR * 24U)

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
