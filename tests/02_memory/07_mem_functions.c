/* Тесты к exercises/02_memory/07_mem_functions.c. Запуск: make test 2 7 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/02_memory/07_mem_functions.c"
#undef main

typedef struct {
    char name[11];
    int age;
} Person;

static int equals(const int* actual, const int* expected, size_t size)
{
    return memcmp(actual, expected, size * sizeof(int)) == 0;
}

static void test_insert(void)
{
    int arr[5] = { 1, 2, 4, 5, 777 };
    int middle[] = { 1, 2, 3, 4, 5 };
    int first[2] = { 7, 777 };
    int front[] = { 0, 1, 2, 3, 4, 5 };
    int big[6] = { 1, 2, 3, 4, 5, 777 };
    int end[] = { 0, 1, 2, 3, 4, 5, 6 };
    int bigger[7] = { 0 };

    insert_at(arr, 4, 2, 3);
    assert(equals(arr, middle, 5));

    insert_at(first, 0, 0, 7);
    assert(first[0] == 7 && first[1] == 777);

    insert_at(big, 5, 0, 0);
    assert(equals(big, front, 6));

    memcpy(bigger, big, sizeof(big));
    insert_at(bigger, 6, 6, 6);
    assert(equals(bigger, end, 7));
}

static void test_remove(void)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int no_first[] = { 2, 3, 4, 5 };
    int no_middle[] = { 2, 4, 5 };
    int no_last[] = { 2, 4 };

    remove_at(arr, 5, 0);
    assert(equals(arr, no_first, 4));
    remove_at(arr, 4, 1);
    assert(equals(arr, no_middle, 3));
    remove_at(arr, 3, 2);
    assert(equals(arr, no_last, 2));
}

static void test_duplicate(void)
{
    int src[] = { 5, -1, 0, 2147483647 };
    int* copy = duplicate(src, 4);

    assert(copy != NULL && copy != src);
    assert(equals(copy, src, 4));
    copy[0] = 42;
    assert(src[0] == 5);
    free(copy);
}

static void test_zeros(void)
{
    size_t count = 100000;
    int* arr = zeros(count);

    assert(arr != NULL);
    for (size_t i = 0; i < count; i++) {
        assert(arr[i] == 0);
    }
    free(arr);
}

static void test_swap(void)
{
    int a = 1;
    int b = -2;
    double x = 0.5;
    double y = 1e100;
    Person p = { "Alice", 30 };
    Person q = { "Bob", 25 };

    swap_bytes(&a, &b, sizeof(a));
    assert(a == -2 && b == 1);

    swap_bytes(&x, &y, sizeof(x));
    assert(x == 1e100 && y == 0.5);

    swap_bytes(&p, &q, sizeof(p));
    assert(strcmp(p.name, "Bob") == 0 && p.age == 25);
    assert(strcmp(q.name, "Alice") == 0 && q.age == 30);
}

static void test_reverse(void)
{
    int ints[] = { 1, 2, 3, 4, 5 };
    int ints_reversed[] = { 5, 4, 3, 2, 1 };
    double doubles[] = { 1.5, 2.5, 3.5, 4.5 };
    char chars[] = "abcdef";
    Person people[] = { { "Alice", 30 }, { "Bob", 25 }, { "Carol", 41 } };
    int one[] = { 9 };

    reverse_any(ints, 5, sizeof(int));
    assert(equals(ints, ints_reversed, 5));

    reverse_any(doubles, 4, sizeof(double));
    assert(doubles[0] == 4.5 && doubles[1] == 3.5 && doubles[2] == 2.5 && doubles[3] == 1.5);

    reverse_any(chars, 6, 1);
    assert(strcmp(chars, "fedcba") == 0);

    reverse_any(people, 3, sizeof(Person));
    assert(strcmp(people[0].name, "Carol") == 0 && people[0].age == 41);
    assert(strcmp(people[1].name, "Bob") == 0 && people[1].age == 25);
    assert(strcmp(people[2].name, "Alice") == 0 && people[2].age == 30);

    reverse_any(one, 1, sizeof(int));
    assert(one[0] == 9);
    reverse_any(one, 0, sizeof(int));
    assert(one[0] == 9);
}

int main(void)
{
    test_insert();
    test_remove();
    test_duplicate();
    test_zeros();
    test_swap();
    test_reverse();

    puts("All tests passed");
    return 0;
}
