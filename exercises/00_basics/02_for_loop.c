/*
# Task 2 — Loop practice

На вход подаётся положительное целое число `n`.

Нужно вывести все числа от 1 до `n`, которые:

- делятся на 3 или на 5;
- но не делятся одновременно на 3 и на 5.

После этого вывести количество таких чисел и их сумму.

## Example

Input:
10

Output:
3 5 6 9 10
count = 5
sum = 33

## Requirements

- Основной перебор сделать через `for`.
- Использовать `continue`, чтобы пропускать неподходящие значения.
- Не использовать массивы.
- Не использовать отдельную функцию для проверки делимости.
- Проверять результат `scanf`.
- `n > 0` гарантируется.
- `calc` сама записывает результат в `*count` и `*sum` и не полагается
  на их начальные значения.
*/

#include <assert.h>
#include <stdio.h>

void calc(int n, int* count, int* sum)
{
    /* TODO: реализуйте calc. */
    (void)n;
    (void)count;
    (void)sum;
    assert(!"TODO: calc");
}

#ifndef TEST

int main(void)
{
    int n = 0;
    int count = 0;
    int sum = 0;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    calc(n, &count, &sum);

    printf("count: %d\nsum: %d\n", count, sum);

    return 0;
}

#else

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

#endif
