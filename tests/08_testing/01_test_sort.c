/* Тесты к exercises/08_testing/01_test_sort.c. Запуск: make test 8 1 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/08_testing/01_test_sort.c"
#undef main

static void insertion_sort(int* arr, size_t size)
{
    for (size_t i = 1; i < size; i++) {
        int value = arr[i];
        size_t j = i;

        while (j > 0 && arr[j - 1] > value) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = value;
    }
}

static int compare_ints(const void* left, const void* right)
{
    int a = *(const int*)left;
    int b = *(const int*)right;

    return (a > b) - (a < b);
}

/* Правильная, но устроена иначе: проверки не должны зависеть от реализации. */
static void library_sort(int* arr, size_t size)
{
    qsort(arr, size, sizeof(int), compare_ints);
}

static void does_nothing(int* arr, size_t size)
{
    (void)arr;
    (void)size;
}

static void sorts_descending(int* arr, size_t size)
{
    insertion_sort(arr, size);
    for (size_t i = 0; i < size / 2; i++) {
        int tmp = arr[i];

        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = tmp;
    }
}

static void forgets_last_element(int* arr, size_t size)
{
    if (size > 0) {
        insertion_sort(arr, size - 1);
    }
}

static void forgets_first_element(int* arr, size_t size)
{
    if (size > 0) {
        insertion_sort(arr + 1, size - 1);
    }
}

/* Результат упорядочен, но числа уже не те. */
static void fills_with_minimum(int* arr, size_t size)
{
    insertion_sort(arr, size);
    for (size_t i = 1; i < size; i++) {
        arr[i] = arr[0];
    }
}

/* Результат упорядочен, но повторы заменены другими числами. */
static void loses_duplicates(int* arr, size_t size)
{
    insertion_sort(arr, size);
    for (size_t i = 1; i < size; i++) {
        if (arr[i] <= arr[i - 1]) {
            arr[i] = arr[i - 1] + 1;
        }
    }
}

static void compares_absolute_values(int* arr, size_t size)
{
    for (size_t i = 1; i < size; i++) {
        int value = arr[i];
        size_t j = i;

        while (j > 0 && abs(arr[j - 1]) > abs(value)) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = value;
    }
}

/* Один проход пузырька: работает только на почти упорядоченных массивах. */
static void makes_one_pass(int* arr, size_t size)
{
    for (size_t i = 0; i + 1 < size; i++) {
        if (arr[i] > arr[i + 1]) {
            int tmp = arr[i];

            arr[i] = arr[i + 1];
            arr[i + 1] = tmp;
        }
    }
}

static void sorts_only_first_eight(int* arr, size_t size)
{
    insertion_sort(arr, size < 8 ? size : 8);
}

static void test_accepts_correct(void)
{
    assert(sort_is_correct(insertion_sort));
    assert(sort_is_correct(library_sort));
}

static void test_rejects_obviously_wrong(void)
{
    assert(!sort_is_correct(does_nothing));
    assert(!sort_is_correct(sorts_descending));
}

static void test_rejects_partial_sorts(void)
{
    assert(!sort_is_correct(forgets_last_element));
    assert(!sort_is_correct(forgets_first_element));
    assert(!sort_is_correct(makes_one_pass));
    assert(!sort_is_correct(sorts_only_first_eight));
}

static void test_rejects_changed_contents(void)
{
    assert(!sort_is_correct(fills_with_minimum));
    assert(!sort_is_correct(loses_duplicates));
}

static void test_rejects_sign_bugs(void)
{
    assert(!sort_is_correct(compares_absolute_values));
}

int main(void)
{
    test_accepts_correct();
    test_rejects_obviously_wrong();
    test_rejects_partial_sorts();
    test_rejects_changed_contents();
    test_rejects_sign_bugs();

    puts("All tests passed");
    return 0;
}
