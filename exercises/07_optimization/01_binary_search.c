/*
# Task 1 — Binary search

В отсортированном массиве не нужно просматривать все элементы подряд.
Двоичный поиск каждый раз смотрит в середину и отбрасывает половину:
в массиве из миллиона элементов хватает 20 шагов вместо миллиона.

## Нужно реализовать функции

count_less:
    Количество элементов, строго меньших `value`.
    Это же — индекс первого элемента, который не меньше `value`.

count_in_range:
    Количество элементов `x`, для которых low <= x <= high.
    Если low > high — возвращает 0.

## Example

sorted = 1 3 3 5 8

count_less(sorted, 5, 3) == 1
count_less(sorted, 5, 4) == 3
count_in_range(sorted, 5, 3, 5) == 3

## Requirements

- Массив отсортирован по возрастанию, в нём могут быть повторы.
- Обе функции работают за O(log size).
- Середину считать как `left + (right - left) / 2`.
- `count_in_range` должна работать для любых границ, включая
  `INT_MIN` и `INT_MAX`: выражение `high + 1` переполняется.
- Тесты ограничены по времени.

## Interfaces

size_t count_less(const int *sorted, size_t size, int value);
size_t count_in_range(const int *sorted, size_t size, int low, int high);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

size_t count_less(const int* sorted, size_t size, int value)
{
    /* TODO: реализуйте count_less. */
    (void)sorted;
    (void)size;
    (void)value;
    assert(!"TODO: count_less");
    return 0;
}

size_t count_in_range(const int* sorted, size_t size, int low, int high)
{
    /* TODO: реализуйте count_in_range. */
    (void)sorted;
    (void)size;
    (void)low;
    (void)high;
    assert(!"TODO: count_in_range");
    return 0;
}

int main(void)
{
    int sorted[] = { 1, 3, 3, 5, 8 };

    printf("less than 4: %zu\n", count_less(sorted, 5, 4));
    printf("in [3, 5]: %zu\n", count_in_range(sorted, 5, 3, 5));
    return 0;
}
