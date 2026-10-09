/* Тесты к exercises/01_files/01_sum_numbers.c. Запуск: make test 1 1 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/01_files/01_sum_numbers.c"
#undef main

static int run(const char* text, size_t* count, long* sum)
{
    FILE* in = tmpfile();
    int ok;

    assert(in != NULL);
    fputs(text, in);
    rewind(in);

    ok = sum_numbers(in, count, sum);
    fclose(in);
    return ok;
}

static int sums_to(const char* text, size_t expected_count, long expected_sum)
{
    size_t count = 777;
    long sum = 777;

    return run(text, &count, &sum) && count == expected_count && sum == expected_sum;
}

static int is_rejected(const char* text)
{
    size_t count = 777;
    long sum = 777;

    return !run(text, &count, &sum);
}

static void test_simple(void)
{
    assert(sums_to("1 2 3", 3, 6));
    assert(sums_to("10 20\n-5\n", 3, 25));
    assert(sums_to("42", 1, 42));
}

static void test_whitespace(void)
{
    assert(sums_to("  7\t8\n\n\n9   \n", 3, 24));
}

static void test_empty_is_ok(void)
{
    assert(sums_to("", 0, 0));
    assert(sums_to("  \n\n\t", 0, 0));
}

static void test_negative_and_large(void)
{
    assert(sums_to("-1 -2 -3", 3, -6));
    assert(sums_to("2000000000 2000000000", 2, 4000000000L));
}

static void test_not_a_number(void)
{
    assert(is_rejected("abc"));
    assert(is_rejected("1 2 x 3"));
    assert(is_rejected("1 2 3 end"));
    assert(is_rejected("12abc"));
}

int main(void)
{
    test_simple();
    test_whitespace();
    test_empty_is_ok();
    test_negative_and_large();
    test_not_a_number();

    puts("All tests passed");
    return 0;
}
