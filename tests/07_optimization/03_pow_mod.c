/* Тесты к exercises/07_optimization/03_pow_mod.c. Запуск: make test 7 3 */

#include <assert.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/07_optimization/03_pow_mod.c"
#undef main

#define TIME_LIMIT_SECONDS 2

static void too_slow(int signal_number)
{
    static const char message[] = "Too slow: time limit exceeded\n";
    ssize_t written = write(STDERR_FILENO, message, sizeof(message) - 1);

    (void)signal_number;
    (void)written;
    _exit(1);
}

/* Если до stop_timer пройдёт больше TIME_LIMIT_SECONDS, тест завершится. */
static void start_timer(void)
{
    signal(SIGALRM, too_slow);
    alarm(TIME_LIMIT_SECONDS);
}

static void stop_timer(void)
{
    alarm(0);
}

static void test_small_powers(void)
{
    assert(pow_mod(2, 10, 1000) == 24);
    assert(pow_mod(2, 10, 2000) == 1024);
    assert(pow_mod(3, 4, 100) == 81);
    assert(pow_mod(5, 3, 13) == 8);
    assert(pow_mod(7, 1, 5) == 2);
}

static void test_power_zero(void)
{
    assert(pow_mod(3, 0, 7) == 1);
    assert(pow_mod(123456789, 0, 1000) == 1);
}

static void test_modulus_one(void)
{
    assert(pow_mod(5, 0, 1) == 0);
    assert(pow_mod(5, 3, 1) == 0);
}

static void test_base_zero_and_one(void)
{
    assert(pow_mod(0, 5, 7) == 0);
    assert(pow_mod(1, 1000, 7) == 1);
    assert(pow_mod(14, 5, 7) == 0);
}

static void test_odd_and_even_exponents(void)
{
    assert(pow_mod(3, 200, 13) == 9);
    assert(pow_mod(5, 117, 19) == 1);
    assert(pow_mod(2, 63, 1000000007) == 291172004);
    assert(pow_mod(2, 64, 1000000007) == 582344008);
}

static void test_huge_exponents_are_fast(void)
{
    start_timer();
    assert(pow_mod(2, 1000000000000000000ULL, 1000000007) == 719476260);
    assert(pow_mod(7, UINT64_MAX, 4294967295U) == 1227133513);
    stop_timer();
}

static void test_huge_base(void)
{
    start_timer();
    assert(pow_mod(1000000000000000000ULL, 1000000000000000000ULL, 4294967291U) == 4225787865U);
    assert(pow_mod(UINT64_MAX, UINT64_MAX, 4294967291U) == 1556015985);
    stop_timer();
}

int main(void)
{
    test_small_powers();
    test_power_zero();
    test_modulus_one();
    test_base_zero_and_one();
    test_odd_and_even_exponents();
    test_huge_exponents_are_fast();
    test_huge_base();

    puts("All tests passed");
    return 0;
}
