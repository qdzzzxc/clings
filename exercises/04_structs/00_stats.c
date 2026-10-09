/*
# Task 0 — Stats struct

В теме 00 статистику массива приходилось возвращать через несколько
выходных указателей. Структура позволяет собрать связанные значения
в один объект и вернуть его целиком.

## Нужно реализовать функции

stats_of:
    Считает статистику массива и возвращает её по значению.
    Гарантируется, что `size > 0`.

stats_add:
    Учитывает в уже посчитанной статистике ещё одно число.
    Структура передаётся по указателю и меняется на месте.

stats_merge:
    Возвращает статистику объединения двух наборов чисел.

stats_average:
    Возвращает среднее арифметическое как `double`.

## Requirements

- К полям через указатель обращаться оператором `->`.
- `stats_add` и `stats_merge` не имеют доступа к исходным числам
  и работают только с полями структур.
- В `stats_average` не потерять дробную часть при делении.

## Interfaces

typedef struct {
    int min;
    int max;
    long long sum;
    size_t count;
} Stats;

Stats stats_of(const int *arr, size_t size);
void stats_add(Stats *stats, int value);
Stats stats_merge(Stats a, Stats b);
double stats_average(const Stats *stats);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    int min;
    int max;
    long long sum;
    size_t count;
} Stats;

void stats_add(Stats* stats, int value)
{
    /* TODO: реализуйте stats_add. */
    (void)stats;
    (void)value;
    assert(!"TODO: stats_add");
}

Stats stats_of(const int* arr, size_t size)
{
    /* TODO: реализуйте stats_of. */
    (void)arr;
    (void)size;
    assert(!"TODO: stats_of");
    return (Stats) { 0, 0, 0, 0 };
}

Stats stats_merge(Stats a, Stats b)
{
    /* TODO: реализуйте stats_merge. */
    (void)b;
    assert(!"TODO: stats_merge");
    return a;
}

double stats_average(const Stats* stats)
{
    /* TODO: реализуйте stats_average. */
    (void)stats;
    assert(!"TODO: stats_average");
    return 0.0;
}

int main(void)
{
    int values[] = { 3, -2, 7, -5, 10 };
    Stats stats = stats_of(values, 5);

    printf("min: %d\n", stats.min);
    printf("max: %d\n", stats.max);
    printf("sum: %lld\n", stats.sum);
    printf("average: %.2f\n", stats_average(&stats));
    return 0;
}
