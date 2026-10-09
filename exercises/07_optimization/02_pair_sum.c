/*
# Task 2 — Pair with sum

Нужно узнать, есть ли в массиве два элемента на разных позициях,
которые в сумме дают `target`.

Перебор всех пар — это size * size / 2 сложений: для 300000 элементов
около 4.5 * 10^10. Быстрее так: отсортировать копию массива и пустить
два указателя навстречу друг другу. Если сумма крайних элементов меньше
нужной — сдвинуть левый указатель, если больше — правый.

## Example

arr = 8 1 5 3, target = 9   ->  1 (8 + 1)
arr = 8 1 5 3, target = 10  ->  0 (5 + 5 не подходит: пятёрка одна)

## Requirements

- Исходный массив не менять: сортировать копию в динамической памяти
  и освободить её перед выходом. Если `malloc` вернул NULL — вернуть 0.
- Сортировать через `qsort`.
- Сумму двух элементов считать в `long long`: сумма двух `int`
  может не поместиться в `int`.
- Один и тот же элемент нельзя взять дважды, но два равных элемента
  на разных позициях — можно.
- Тесты ограничены по времени.

## Interface

int has_pair_with_sum(const int *arr, size_t size, long long target);

Возвращаемое значение:

1 — пара есть
0 — пары нет
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int has_pair_with_sum(const int* arr, size_t size, long long target)
{
    /* TODO: реализуйте has_pair_with_sum. */
    (void)arr;
    (void)size;
    (void)target;
    assert(!"TODO: has_pair_with_sum");
    return 0;
}

int main(void)
{
    int values[] = { 8, 1, 5, 3 };

    printf("9: %d\n", has_pair_with_sum(values, 4, 9));
    printf("10: %d\n", has_pair_with_sum(values, 4, 10));
    return 0;
}
