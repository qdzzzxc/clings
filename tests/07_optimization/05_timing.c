/* Тесты к exercises/07_optimization/05_timing.c. Запуск: make test 7 5 */

#include <assert.h>
#include <stdio.h>
#include <time.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/07_optimization/05_timing.c"
#undef main

static int calls = 0;

/* Спит ms миллисекунд: реальное время идёт, процессорное — нет. */
static void sleep_ms(void* arg)
{
    long ms = *(const long*)arg;
    struct timespec duration = { ms / 1000, ms % 1000 * 1000000L };

    calls++;
    while (nanosleep(&duration, &duration) != 0) {
    }
}

/* Крутит цикл ms миллисекунд: процессорное время идёт вместе с реальным. */
static void busy_ms(void* arg)
{
    long ms = *(const long*)arg;
    clock_t end = clock() + (clock_t)(ms * CLOCKS_PER_SEC / 1000);
    volatile long counter = 0;

    calls++;
    while (clock() < end) {
        counter++;
    }
}

static void test_job_called_once(void)
{
    long ms = 1;

    calls = 0;
    wall_ms(sleep_ms, &ms);
    assert(calls == 1);
    cpu_ms(sleep_ms, &ms);
    assert(calls == 2);
}

static void test_sleep(void)
{
    long ms = 200;
    double wall = wall_ms(sleep_ms, &ms);
    double cpu = cpu_ms(sleep_ms, &ms);

    printf("sleep 200 ms: wall %.1f ms, cpu %.1f ms\n", wall, cpu);
    assert(wall >= 199.0 && wall < 1000.0);
    assert(cpu >= 0.0 && cpu < 50.0);
}

/* Дольше секунды: одной разности tv_nsec уже не хватает, нужна и tv_sec. */
static void test_crosses_second(void)
{
    long ms = 1050;
    double wall = wall_ms(sleep_ms, &ms);

    printf("sleep 1050 ms: wall %.1f ms\n", wall);
    assert(wall >= 1049.0 && wall < 2000.0);
}

static void test_busy(void)
{
    long ms = 200;
    double wall = wall_ms(busy_ms, &ms);
    double cpu = cpu_ms(busy_ms, &ms);

    printf("busy 200 ms: wall %.1f ms, cpu %.1f ms\n", wall, cpu);
    assert(wall >= 190.0 && wall < 2000.0);
    assert(cpu >= 190.0 && cpu < 400.0);
}

int main(void)
{
    test_job_called_once();
    test_sleep();
    test_crosses_second();
    test_busy();

    puts("All tests passed");
    return 0;
}
