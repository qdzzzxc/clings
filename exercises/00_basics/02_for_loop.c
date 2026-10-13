/*
# Task 2 — Loop practice

На вход подаётся положительное целое число `n`.

Среди чисел от 1 до `n` нужно найти те, которые:

- делятся на 3 или на 5;
- но не делятся одновременно на 3 и на 5.

Вывести количество таких чисел и их сумму.

## Example

Input:
10

Подходят 3 5 6 9 10.

Output:
count: 5
sum: 33

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
    *count = 0;
    *sum = 0;

    for (int i = 1; i <= n; i++) {
        if (i % 15 == 0) {
            continue;
        }

        if ((i % 3 == 0) || (i % 5 == 0)) {
            printf("%d ", i);
            *count += 1;
            *sum += i;
        }
    }
}

int main(void)
{
    int n = 0;
    int count = 0;
    int sum = 0;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    calc(n, &count, &sum);

    printf("\ncount: %d\nsum: %d\n", count, sum);

    return 0;
}
