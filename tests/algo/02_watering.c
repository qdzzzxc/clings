/* Тесты к exercises/algo/02_watering.c. Запуск: make test algo 2 */

#include <assert.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/algo/02_watering.c"
#undef main

#include "rules.h"

static long long run(const char* input)
{
    FILE* in = tmpfile();
    long long result = 0;

    assert(in != NULL);
    fputs(input, in);
    rewind(in);
    result = wateringSteps(in);
    fclose(in);
    return result;
}

/* Эталон: честно ходим по оси шаг за шагом. */
static long long reference(const int* plants, int n, int capacity)
{
    long long steps = 0;
    int position = -1;
    int water = capacity;

    for (int i = 0; i < n; i++) {
        if (water < plants[i]) {
            while (position > -1) {
                position--;
                steps++;
            }
            water = capacity;
        }
        while (position < i) {
            position++;
            steps++;
        }
        water -= plants[i];
    }
    return steps;
}

static void check(const int* plants, int n, int capacity)
{
    FILE* in = tmpfile();

    assert(in != NULL);
    fprintf(in, "%d\n%d\n", n, capacity);
    for (int i = 0; i < n; i++) {
        fprintf(in, i + 1 < n ? "%d " : "%d\n", plants[i]);
    }
    rewind(in);
    assert(wateringSteps(in) == reference(plants, n, capacity));
    fclose(in);
}

static void test_examples(void)
{
    assert(run("4\n5\n2 2 3 3\n") == 14);
    assert(run("6\n4\n1 1 1 4 2 3\n") == 30);
}

static void test_no_refill(void)
{
    assert(run("1\n1\n1\n") == 1);
    assert(run("3\n10\n1 2 3\n") == 3);
    assert(run("4\n10\n1 2 3 4\n") == 4);
}

static void test_refill_every_time(void)
{
    assert(run("7\n8\n7 7 7 7 7 7 7\n") == 49);
    assert(run("3\n5\n5 5 5\n") == 9);
}

static void test_exact_water(void)
{
    /* Воды ровно столько, сколько нужно: к реке не идём. */
    assert(run("2\n5\n2 3\n") == 2);
    assert(run("3\n5\n2 3 1\n") == 1 + 1 + 2 + 3);
}

static void test_big_numbers(void)
{
    assert(run("3\n1000000000\n1000000 1000000 1000000\n") == 3);
    assert(run("2\n1000000\n1000000 1000000\n") == 1 + 1 + 2);
}

static void test_random(void)
{
    int plants[1000] = { 0 };
    unsigned state = 2024;

    for (int round = 0; round < 300; round++) {
        int n = round < 299 ? 1 + round % 50 : 1000;
        int max_plant = 1 + round % 10;
        int capacity = 0;

        for (int i = 0; i < n; i++) {
            state = state * 1103515245u + 12345u;
            plants[i] = 1 + (int)((state >> 8) % (unsigned)max_plant);
            if (plants[i] > capacity) {
                capacity = plants[i];
            }
        }
        state = state * 1103515245u + 12345u;
        capacity += (int)((state >> 8) % 15u);
        check(plants, n, capacity);
    }
}

int main(void)
{
    CHECK_RULES();

    test_examples();
    test_no_refill();
    test_refill_every_time();
    test_exact_water();
    test_big_numbers();
    test_random();

    puts("All tests passed");
    return 0;
}
