/* Тесты к exercises/05_modules/01_report/. Запуск: make test 5 1 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Каждый заголовок подключён дважды: include guard должен это выдержать. */
#include "counter.h"
#include "report.h"

#include "counter.h"
#include "report.h"

static void test_counter_counts(void)
{
    counter_reset();

    assert(counter_next() == 1);
    assert(counter_next() == 2);
    assert(counter_next() == 3);
}

static void test_counter_step(void)
{
    counter_reset();
    assert(counter_step == 1);

    counter_step = 5;
    assert(counter_next() == 5);
    assert(counter_next() == 10);

    counter_step = -3;
    assert(counter_next() == 7);

    counter_step = 0;
    assert(counter_next() == 7);
}

static void test_counter_reset(void)
{
    counter_reset();
    counter_step = 100;
    counter_next();

    counter_reset();

    assert(counter_step == 1);
    assert(counter_next() == 1);
}

static void test_report_line(void)
{
    char line[32] = "";

    counter_reset();

    assert(report_line(line, sizeof(line), "hello"));
    assert(strcmp(line, "1: hello") == 0);

    assert(report_line(line, sizeof(line), "world"));
    assert(strcmp(line, "2: world") == 0);

    assert(report_line(line, sizeof(line), ""));
    assert(strcmp(line, "3: ") == 0);
}

static void test_report_uses_the_shared_counter(void)
{
    char line[32] = "";

    counter_reset();
    counter_step = 10;
    counter_next();

    assert(report_line(line, sizeof(line), "third"));
    assert(strcmp(line, "20: third") == 0);
    assert(counter_next() == 30);
}

static void test_report_exact_fit(void)
{
    /* "1: abc" — 6 символов и '\0'. */
    char line[7] = "";

    counter_reset();

    assert(report_line(line, sizeof(line), "abc"));
    assert(strcmp(line, "1: abc") == 0);
}

static void test_report_does_not_fit(void)
{
    /* Буфер в куче: запись за его границу увидит санитайзер. */
    char* line = malloc(6);

    assert(line != NULL);
    counter_reset();

    assert(!report_line(line, 6, "abc"));
    assert(!report_line(line, 6, "a much longer text"));

    /* Номер был взят оба раза, хотя строки не поместились. */
    assert(counter_next() == 3);

    free(line);
}

int main(void)
{
    test_counter_counts();
    test_counter_step();
    test_counter_reset();
    test_report_line();
    test_report_uses_the_shared_counter();
    test_report_exact_fit();
    test_report_does_not_fit();

    puts("All tests passed");
    return 0;
}
