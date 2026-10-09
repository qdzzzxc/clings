/* Тесты к exercises/04_structs/03_qsort.c. Запуск: make test 4 3 */

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/04_structs/03_qsort.c"
#undef main

static int ints_equal(const int* actual, const int* expected, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        if (actual[i] != expected[i]) {
            return 0;
        }
    }
    return 1;
}

static void test_sort_ints(void)
{
    int values[] = { 5, -1, 3, 0, 3, -7 };
    const int expected[] = { -7, -1, 0, 3, 3, 5 };

    sort_ints(values, 6);

    assert(ints_equal(values, expected, 6));
}

static void test_sort_ints_small(void)
{
    int one[] = { 4 };
    int two[] = { 2, 1 };
    const int two_sorted[] = { 1, 2 };

    sort_ints(one, 0);
    sort_ints(one, 1);
    sort_ints(two, 2);

    assert(one[0] == 4);
    assert(ints_equal(two, two_sorted, 2));
}

static void test_sort_ints_far_apart(void)
{
    /* Здесь ломается компаратор, который вычитает одно число из другого. */
    int values[] = { INT_MAX, -1, INT_MIN, 1, 0, INT_MAX, INT_MIN, -2 };
    const int expected[] = { INT_MIN, INT_MIN, -2, -1, 0, 1, INT_MAX, INT_MAX };

    sort_ints(values, 8);

    assert(ints_equal(values, expected, 8));
}

static void test_sort_ints_only_given_part(void)
{
    int values[] = { 3, 2, 1, 0 };
    const int expected[] = { 1, 2, 3, 0 };

    sort_ints(values, 3);

    assert(ints_equal(values, expected, 4));
}

static void test_sort_strings(void)
{
    const char* words[] = { "pear", "apple", "fig", "banana", "apple pie", "Apple" };
    const char* expected[] = { "Apple", "apple", "apple pie", "banana", "fig", "pear" };

    sort_strings(words, 6);

    for (size_t i = 0; i < 6; i++) {
        assert(strcmp(words[i], expected[i]) == 0);
    }
}

static void test_sort_strings_keeps_the_same_pointers(void)
{
    const char* b = "b";
    const char* a = "a";
    const char* words[2];

    words[0] = b;
    words[1] = a;

    sort_strings(words, 2);

    assert(words[0] == a);
    assert(words[1] == b);
}

static int person_is(const Person* person, const char* name, int age)
{
    return person->age == age && strcmp(person->name, name) == 0;
}

static void test_sort_people_by_age(void)
{
    Person people[] = {
        { "Vera", 30 },
        { "Anna", 19 },
        { "Boris", 25 },
    };

    sort_people(people, 3);

    assert(person_is(&people[0], "Anna", 19));
    assert(person_is(&people[1], "Boris", 25));
    assert(person_is(&people[2], "Vera", 30));
}

static void test_sort_people_same_age_by_name(void)
{
    Person people[] = {
        { "Vera", 20 },
        { "Zoya", 19 },
        { "Boris", 20 },
        { "Anna", 20 },
        { "Gleb", 19 },
    };

    sort_people(people, 5);

    assert(person_is(&people[0], "Gleb", 19));
    assert(person_is(&people[1], "Zoya", 19));
    assert(person_is(&people[2], "Anna", 20));
    assert(person_is(&people[3], "Boris", 20));
    assert(person_is(&people[4], "Vera", 20));
}

static void test_sort_people_far_apart_ages(void)
{
    Person people[] = {
        { "Max", INT_MAX },
        { "Min", INT_MIN },
        { "Zero", 0 },
    };

    sort_people(people, 3);

    assert(person_is(&people[0], "Min", INT_MIN));
    assert(person_is(&people[1], "Zero", 0));
    assert(person_is(&people[2], "Max", INT_MAX));
}

int main(void)
{
    test_sort_ints();
    test_sort_ints_small();
    test_sort_ints_far_apart();
    test_sort_ints_only_given_part();
    test_sort_strings();
    test_sort_strings_keeps_the_same_pointers();
    test_sort_people_by_age();
    test_sort_people_same_age_by_name();
    test_sort_people_far_apart_ages();

    puts("All tests passed");
    return 0;
}
