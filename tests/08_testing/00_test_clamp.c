/* Тесты к exercises/08_testing/00_test_clamp.c. Запуск: make test 8 0 */

#include <assert.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/08_testing/00_test_clamp.c"
#undef main

static int correct_clamp(int value, int low, int high)
{
    if (value < low) {
        return low;
    }
    if (value > high) {
        return high;
    }
    return value;
}

/* Правильная, но написана по-другому: проверки не должны зависеть от реализации. */
static int correct_clamp_other_way(int value, int low, int high)
{
    int result = value > low ? value : low;

    return result < high ? result : high;
}

static int returns_value_as_is(int value, int low, int high)
{
    (void)low;
    (void)high;
    return value;
}

static int ignores_upper_bound(int value, int low, int high)
{
    (void)high;
    return value < low ? low : value;
}

static int ignores_lower_bound(int value, int low, int high)
{
    (void)low;
    return value > high ? high : value;
}

static int mixes_up_bounds(int value, int low, int high)
{
    if (value < low) {
        return high;
    }
    if (value > high) {
        return low;
    }
    return value;
}

static int works_only_for_positive(int value, int low, int high)
{
    if (value < 0) {
        value = -value;
    }
    return correct_clamp(value, low, high);
}

static int breaks_on_single_point(int value, int low, int high)
{
    if (low == high) {
        return value;
    }
    return correct_clamp(value, low, high);
}

static int never_returns_bounds(int value, int low, int high)
{
    if (value <= low) {
        return low + 1;
    }
    if (value >= high) {
        return high - 1;
    }
    return value;
}

static int always_returns_low(int value, int low, int high)
{
    (void)value;
    (void)high;
    return low;
}

static void test_accepts_correct(void)
{
    assert(clamp_is_correct(correct_clamp));
    assert(clamp_is_correct(correct_clamp_other_way));
}

static void test_rejects_obviously_wrong(void)
{
    assert(!clamp_is_correct(returns_value_as_is));
    assert(!clamp_is_correct(always_returns_low));
    assert(!clamp_is_correct(mixes_up_bounds));
}

static void test_rejects_one_sided(void)
{
    assert(!clamp_is_correct(ignores_upper_bound));
    assert(!clamp_is_correct(ignores_lower_bound));
}

static void test_rejects_boundary_bugs(void)
{
    assert(!clamp_is_correct(never_returns_bounds));
    assert(!clamp_is_correct(breaks_on_single_point));
}

static void test_rejects_sign_bugs(void)
{
    assert(!clamp_is_correct(works_only_for_positive));
}

int main(void)
{
    test_accepts_correct();
    test_rejects_obviously_wrong();
    test_rejects_one_sided();
    test_rejects_boundary_bugs();
    test_rejects_sign_bugs();

    puts("All tests passed");
    return 0;
}
