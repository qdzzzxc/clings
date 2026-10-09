/* Тесты к exercises/04_structs/02_callbacks.c. Запуск: make test 4 2 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/04_structs/02_callbacks.c"
#undef main

static int square(int value)
{
    return value * value;
}

static int negate(int value)
{
    return -value;
}

static int is_even(int value)
{
    return value % 2 == 0;
}

static int is_negative(int value)
{
    return value < 0;
}

/* Возвращает не 0 и не 1: count_if должен считать любое ненулевое значение. */
static int is_big(int value)
{
    return value > 100 ? value : 0;
}

static int max_of_two(int left, int right)
{
    return left > right ? left : right;
}

static int append_digit(int left, int right)
{
    return left * 10 + right;
}

static void test_map(void)
{
    int values[] = { 1, -2, 3, 0 };

    map(values, 4, square);
    assert(values[0] == 1 && values[1] == 4 && values[2] == 9 && values[3] == 0);

    map(values, 4, negate);
    assert(values[0] == -1 && values[1] == -4 && values[2] == -9 && values[3] == 0);
}

static void test_map_part_of_array(void)
{
    int values[] = { 2, 3, 4 };

    map(values, 2, square);
    assert(values[0] == 4 && values[1] == 9 && values[2] == 4);

    map(values, 0, square);
    assert(values[0] == 4);
}

static void test_count_if(void)
{
    int values[] = { 1, 2, -4, 7, 200, 300 };

    assert(count_if(values, 6, is_even) == 4);
    assert(count_if(values, 6, is_negative) == 1);
    assert(count_if(values, 6, is_big) == 2);
    assert(count_if(values, 0, is_even) == 0);
}

static void test_reduce(void)
{
    int values[] = { 3, 9, 2, 7 };

    assert(reduce(values, 4, 0, max_of_two) == 9);
    assert(reduce(values, 4, 100, max_of_two) == 100);
    assert(reduce(values, 0, 42, max_of_two) == 42);
}

static void test_reduce_goes_left_to_right(void)
{
    int digits[] = { 1, 2, 3 };

    assert(reduce(digits, 3, 0, append_digit) == 123);
    assert(reduce(digits, 3, 9, append_digit) == 9123);
}

static void test_operation_by_symbol(void)
{
    assert(operation_by_symbol('+') != NULL);
    assert(operation_by_symbol('-') != NULL);
    assert(operation_by_symbol('*') != NULL);

    assert(operation_by_symbol('+')(7, 5) == 12);
    assert(operation_by_symbol('-')(7, 5) == 2);
    assert(operation_by_symbol('-')(5, 7) == -2);
    assert(operation_by_symbol('*')(7, 5) == 35);
}

static void test_unknown_operation(void)
{
    assert(operation_by_symbol('/') == NULL);
    assert(operation_by_symbol('x') == NULL);
    assert(operation_by_symbol('\0') == NULL);
}

static void test_operations_work_with_reduce(void)
{
    int values[] = { 1, 2, 3, 4 };

    assert(reduce(values, 4, 0, operation_by_symbol('+')) == 10);
    assert(reduce(values, 4, 1, operation_by_symbol('*')) == 24);
    assert(reduce(values, 4, 10, operation_by_symbol('-')) == 0);
}

static void test_calculate(void)
{
    int result = 777;

    assert(calculate(6, '*', 7, &result));
    assert(result == 42);

    assert(calculate(6, '-', 7, &result));
    assert(result == -1);

    assert(calculate(6, '+', 7, &result));
    assert(result == 13);
}

static void test_calculate_unknown_operation(void)
{
    int result = 777;

    assert(!calculate(6, '/', 7, &result));
    assert(!calculate(6, '?', 7, &result));
    assert(result == 777);
}

int main(void)
{
    test_map();
    test_map_part_of_array();
    test_count_if();
    test_reduce();
    test_reduce_goes_left_to_right();
    test_operation_by_symbol();
    test_unknown_operation();
    test_operations_work_with_reduce();
    test_calculate();
    test_calculate_unknown_operation();

    puts("All tests passed");
    return 0;
}
