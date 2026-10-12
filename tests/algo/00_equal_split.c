/* Тесты к exercises/algo/00_equal_split.c. Запуск: make test algo 0 */

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/algo/00_equal_split.c"
#undef main

#include "rules.h"

/* Эталон: перебор разрезов по строке с цифрами. */
static int reference(unsigned long long n)
{
    char digits[32] = "";
    int length = snprintf(digits, sizeof(digits), "%llu", n);

    for (int right = 1; right < length; right++) {
        int left_sum = 0;
        int right_sum = 0;

        for (int i = 0; i < length; i++) {
            if (i < length - right) {
                left_sum += digits[i] - '0';
            } else {
                right_sum += digits[i] - '0';
            }
        }
        if (left_sum == right_sum) {
            return right;
        }
    }
    return -1;
}

static void test_examples(void)
{
    assert(searchEqualSplit(1221) == 2);
    assert(searchEqualSplit(3030) == 2);
    assert(searchEqualSplit(12345) == -1);
    assert(searchEqualSplit(7) == -1);
    assert(searchEqualSplit(0) == -1);
}

static void test_small(void)
{
    assert(searchEqualSplit(11) == 1);
    assert(searchEqualSplit(55) == 1);
    assert(searchEqualSplit(10) == -1);
    assert(searchEqualSplit(12) == -1);
    assert(searchEqualSplit(101) == 1);
    assert(searchEqualSplit(110) == 2);
    assert(searchEqualSplit(123) == 1);
    assert(searchEqualSplit(321) == 2);
}

static void test_zeros(void)
{
    /* Нули справа не меняют сумму: правая часть растёт, пока не наберёт половину. */
    assert(searchEqualSplit(1001) == 1);
    assert(searchEqualSplit(10010) == 2);
    assert(searchEqualSplit(1000001) == 1);
    assert(searchEqualSplit(5000000005ULL) == 1);
    assert(searchEqualSplit(100) == -1);
}

static void test_right_part_is_larger(void)
{
    assert(searchEqualSplit(9111111111ULL) == 9);
    assert(searchEqualSplit(811111111ULL) == 8);
    assert(searchEqualSplit(1119) == -1);
}

static void test_large(void)
{
    assert(searchEqualSplit(ULLONG_MAX) == reference(ULLONG_MAX));
    assert(searchEqualSplit(10000000000000000001ULL) == 1);
    assert(searchEqualSplit(999999999999999999ULL) == 9);
    assert(searchEqualSplit(9999999999999999999ULL) == -1);
}

static void test_against_reference(void)
{
    unsigned long long state = 88172645463325252ULL;

    for (unsigned long long n = 0; n < 100000; n++) {
        assert(searchEqualSplit(n) == reference(n));
    }
    for (int i = 0; i < 200000; i++) {
        unsigned long long n = 0;

        state ^= state << 13;
        state ^= state >> 7;
        state ^= state << 17;
        n = state >> (state % 64);
        assert(searchEqualSplit(n) == reference(n));
    }
}

int main(void)
{
    CHECK_RULES();

    test_examples();
    test_small();
    test_zeros();
    test_right_part_is_larger();
    test_large();
    test_against_reference();

    puts("All tests passed");
    return 0;
}
