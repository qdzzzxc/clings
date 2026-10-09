/*
# Task 3 — Fast power

Нужно вычислить остаток от деления `base` в степени `exponent`
на `modulus`. Показатель степени может быть порядка 10^18, поэтому
умножать в цикле `exponent` раз нельзя.

Быстрое возведение в степень пользуется тем, что

x^(2k)   = (x^2)^k
x^(2k+1) = x * (x^2)^k

На каждом шаге показатель уменьшается вдвое, поэтому хватает
около 60 шагов даже для 10^18.

## Example

pow_mod(2, 10, 1000) == 24      (2^10 = 1024)
pow_mod(3, 0, 7) == 1

## Requirements

- Работать за O(log exponent): цикл по битам показателя.
- Остаток брать после каждого умножения. Оба множителя тогда меньше
  2^32, и их произведение помещается в `uint64_t`.
- `base` может быть больше `modulus`: сначала взять остаток от него.
- Любое число в степени 0 равно 1. При `modulus == 1` ответ всегда 0.
- Гарантируется, что `modulus > 0`.
- Тесты ограничены по времени.

## Interface

uint64_t pow_mod(uint64_t base, uint64_t exponent, uint32_t modulus);
*/

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

uint64_t pow_mod(uint64_t base, uint64_t exponent, uint32_t modulus)
{
    /* TODO: реализуйте pow_mod. */
    (void)base;
    (void)exponent;
    (void)modulus;
    assert(!"TODO: pow_mod");
    return 0;
}

int main(void)
{
    printf("2^10 mod 1000 = %lu\n", (unsigned long)pow_mod(2, 10, 1000));
    printf("2^(10^18) mod 1000000007 = %lu\n",
        (unsigned long)pow_mod(2, 1000000000000000000ULL, 1000000007));
    return 0;
}
