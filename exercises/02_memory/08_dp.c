/*
# Task 8 — Dynamic programming

Три задачи на динамическое программирование. Алгоритм тот же, что
в Python; в C добавляется память под таблицу: её выделяют, следят
за размером и типом ячейки и освобождают на всех путях.

## Нужно реализовать функции

grid_paths:
    Поле из `rows` строк по `cols` символов: '.' — свободная клетка,
    '#' — стена. Из левой верхней клетки в правую нижнюю можно ходить
    только вправо и вниз. Вернуть количество путей. Если начальная
    или конечная клетка — стена, путей 0.

    ...
    .#.     ->  2
    ...

levenshtein:
    Расстояние Левенштейна: наименьшее число вставок, удалений
    и замен символов, чтобы получить из строки `a` строку `b`.
    "kitten", "sitting"  ->  3

subset_sum:
    Можно ли выбрать несколько чисел из `values` (каждое не больше
    одного раза), чтобы их сумма была ровно `target`. Пустой выбор
    даёт сумму 0. Вернуть 1 или 0, при нехватке памяти — -1.
    3 34 4 12 5 2, target 9  ->  1 (4 + 5)

## Requirements

- `grid_paths`: одна строка таблицы из `cols` чисел, а не вся таблица.
  Ответ на полностью свободном поле 34 x 35 — около 1.4e19: он влезает
  в `unsigned long long`, но не в `long long` и тем более не в `int`.
  Гарантируется, что rows >= 1, cols >= 1 и ответ влезает
  в `unsigned long long`. При нехватке памяти вернуть 0.
- `levenshtein`: две строки таблицы длины `strlen(b) + 1`, а не вся
  таблица (len(a) + 1) x (len(b) + 1): для строк по 10000 символов
  она заняла бы 800 МБ. При нехватке памяти вернуть `SIZE_MAX`.
- `subset_sum`: таблица `reachable[0..target]` через `calloc`.
  Все числа >= 0, 0 <= target <= 1000000. Числа равные 0 тоже
  бывают: проверь, что цикл по `size_t` вниз до текущего числа
  при этом заканчивается.
- Каждая функция освобождает всё, что выделила.
- Тесты ограничены по времени.

## Interfaces

unsigned long long grid_paths(const char *const *grid, size_t rows, size_t cols);
size_t levenshtein(const char *a, const char *b);
int subset_sum(const int *values, size_t count, int target);
*/

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long grid_paths(const char* const* grid, size_t rows, size_t cols)
{
    /* TODO: реализуйте grid_paths. */
    (void)grid;
    (void)rows;
    (void)cols;
    assert(!"TODO: grid_paths");
    return 0;
}

size_t levenshtein(const char* a, const char* b)
{
    /* TODO: реализуйте levenshtein. */
    (void)a;
    (void)b;
    assert(!"TODO: levenshtein");
    return 0;
}

int subset_sum(const int* values, size_t count, int target)
{
    /* TODO: реализуйте subset_sum. */
    (void)values;
    (void)count;
    (void)target;
    assert(!"TODO: subset_sum");
    return 0;
}

int main(void)
{
    const char* grid[] = { "...", ".#.", "..." };
    int values[] = { 3, 34, 4, 12, 5, 2 };

    printf("%llu\n", grid_paths(grid, 3, 3));
    printf("%zu\n", levenshtein("kitten", "sitting"));
    printf("%d\n", subset_sum(values, 6, 9));
    return 0;
}
