/*
# Task 5 — Timing

Прежде чем ускорять код, его время надо измерить. Время бывает двух
видов:

- реальное (wall clock) — сколько прошло по часам на стене. Сюда входит
  ожидание: `sleep`, диск, сеть, другие процессы;
- процессорное (CPU time) — сколько процессор реально считал этот
  процесс. Пока программа спит, оно не растёт.

Из программы:

- `clock_gettime(CLOCK_MONOTONIC, &ts)` — реальное время с точностью
  до наносекунд. `CLOCK_MONOTONIC`, а не `CLOCK_REALTIME`: его не
  сдвигает перевод системных часов. Старый вариант — `gettimeofday`,
  до микросекунд;
- `clock()` — процессорное время в тиках, секунды — это
  `(double)ticks / CLOCKS_PER_SEC`;
- `time(NULL)` — секунды с 1970 года: для замеров слишком грубо.

Из терминала: `time ./app` показывает real, user и sys,
`perf stat ./app` — ещё и счётчики процессора.

## Нужно реализовать функции

wall_ms:
    Вызывает `job(arg)` и возвращает, сколько миллисекунд реального
    времени занял вызов.

cpu_ms:
    То же, но процессорное время в миллисекундах.

## Requirements

- `wall_ms` — через `clock_gettime(CLOCK_MONOTONIC, ...)`. Разность
  двух `struct timespec` — это разность `tv_sec` и разность `tv_nsec`,
  и вторая может быть отрицательной. Считать в `double`.
- `cpu_ms` — через `clock()`.
- Замерять только вызов `job`, без лишней работы между замерами.

## Interfaces

typedef void (*Job)(void *arg);

double wall_ms(Job job, void *arg);
double cpu_ms(Job job, void *arg);
*/

#include <assert.h>
#include <stdio.h>
#include <time.h>

typedef void (*Job)(void* arg);

double wall_ms(Job job, void* arg)
{
    /* TODO: реализуйте wall_ms. */
    (void)job;
    (void)arg;
    assert(!"TODO: wall_ms");
    return 0;
}

double cpu_ms(Job job, void* arg)
{
    /* TODO: реализуйте cpu_ms. */
    (void)job;
    (void)arg;
    assert(!"TODO: cpu_ms");
    return 0;
}

static void sum_squares(void* arg)
{
    const long* n = arg;
    volatile long long sum = 0;

    for (long i = 0; i < *n; i++) {
        sum += (long long)i * i;
    }
}

int main(void)
{
    long n = 100000000;

    printf("wall: %.1f ms\n", wall_ms(sum_squares, &n));
    printf("cpu:  %.1f ms\n", cpu_ms(sum_squares, &n));
    return 0;
}
