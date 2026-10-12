/*
# Task 0 — Equal split

Запишем число N в десятичной системе и разрежем запись на две непустые
части: левую и правую. Нужно найти разрез, при котором суммы цифр
левой и правой частей равны.

Функция возвращает количество цифр в правой части. Если подходящих
разрезов несколько — самый правый, то есть с наименьшей правой частью.
Если разрезать нельзя — вернуть -1.

## Example

1221     ->  2   (12 | 21: 1 + 2 == 2 + 1)
3030     ->  2   (30 | 30; разрез 3 | 030 тоже подходит, но он левее)
12345    ->  -1  (сумма цифр 15 нечётная)
7        ->  -1  (одну цифру не разрезать)
0        ->  -1

## Requirements

- Без массивов и строк: цифры достаются через % 10 и / 10.
- N может быть любым unsigned long long, вплоть до ULLONG_MAX.

## Interface

int searchEqualSplit(unsigned long long n);
*/

#include <assert.h>
#include <stdio.h>

int searchEqualSplit(unsigned long long n)
{
    unsigned long long n_copy = n;
    int left_sum = 0;

    while (n_copy) {
        left_sum += n_copy % 10;
        n_copy /= 10;
    }

    if (left_sum % 2 != 0) {
        return -1;
    }

    int right_sum = 0;
    int n_count = 0;

    while (n) {
        int last_digit = n % 10;
        n_count += 1;

        left_sum -= last_digit;
        right_sum += last_digit;

        if (left_sum == right_sum) {
            return n_count;
        }

        n /= 10;
    }

    return -1;
}

int main(void)
{
    unsigned long long n = 0;

    if (scanf("%llu", &n) != 1) {
        return 1;
    }
    printf("%d\n", searchEqualSplit(n));
    return 0;
}
