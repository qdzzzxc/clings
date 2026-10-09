/*
# Task 0 — Range sums

Дан массив и много запросов вида «сумма элементов с индексами
от left до right включительно».

Если на каждый запрос заново складывать элементы, на массиве из 200000
элементов и 200000 запросах получится порядка 10^10 сложений. Нужно
ответить на все запросы быстро: один раз подготовить данные, после чего
каждый запрос считается за постоянное время.

Идея — префиксные суммы: prefix[i] — сумма первых i элементов.
Тогда сумма на отрезке — разность двух префиксных сумм.

## Example

arr     = 3 1 4 1 5
запросы = [0, 4], [1, 2], [3, 3]
ответы  = 14, 5, 1

## Requirements

- Массив префиксных сумм выделить в динамической памяти и освободить
  перед выходом. Если `malloc` вернул NULL — просто выйти.
- Суммы хранить в `long long`.
- Гарантируется, что в каждом запросе left <= right < size.
- Тесты ограничены по времени.

## Interface

void range_sums(const int *arr, size_t size,
                const size_t *lefts, const size_t *rights,
                size_t query_count, long long *out);

`lefts[i]` и `rights[i]` — границы запроса i, ответ пишется в `out[i]`.
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void range_sums(const int* arr, size_t size,
    const size_t* lefts, const size_t* rights,
    size_t query_count, long long* out)
{
    /* TODO: реализуйте range_sums. */
    (void)arr;
    (void)size;
    (void)lefts;
    (void)rights;
    (void)query_count;
    (void)out;
    assert(!"TODO: range_sums");
}

int main(void)
{
    int values[] = { 3, 1, 4, 1, 5 };
    size_t lefts[] = { 0, 1, 3 };
    size_t rights[] = { 4, 2, 3 };
    long long sums[3] = { 0 };

    range_sums(values, 5, lefts, rights, 3, sums);

    printf("%lld %lld %lld\n", sums[0], sums[1], sums[2]);
    return 0;
}
