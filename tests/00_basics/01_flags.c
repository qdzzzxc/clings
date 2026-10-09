/* Тесты к exercises/00_basics/01_flags.c. Запуск: make test 0 1 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/00_basics/01_flags.c"
#undef main

static void test_empty(void)
{
    uint8_t permissions = 0;

    assert(!has_flag(permissions, READ));
    assert(!has_flag(permissions, WRITE));
    assert(!has_flag(permissions, EXECUTE));
    assert(!has_flag(permissions, ADMIN));
}

static void test_set_flag(void)
{
    uint8_t permissions = 0;

    set_flag(&permissions, READ);

    assert(has_flag(permissions, READ));
    assert(!has_flag(permissions, WRITE));

    set_flag(&permissions, WRITE);

    assert(has_flag(permissions, READ));
    assert(has_flag(permissions, WRITE));
}

static void test_set_twice(void)
{
    uint8_t permissions = 0;

    set_flag(&permissions, READ);
    set_flag(&permissions, READ);

    assert(permissions == READ);
}

static void test_clear_flag(void)
{
    uint8_t permissions = 0;

    set_flag(&permissions, READ);
    set_flag(&permissions, WRITE);

    clear_flag(&permissions, READ);

    assert(!has_flag(permissions, READ));
    assert(has_flag(permissions, WRITE));
}

static void test_clear_missing_flag(void)
{
    uint8_t permissions = 0;

    clear_flag(&permissions, ADMIN);

    assert(permissions == 0);
}

static void test_toggle_flag(void)
{
    uint8_t permissions = 0;

    toggle_flag(&permissions, EXECUTE);
    assert(has_flag(permissions, EXECUTE));

    toggle_flag(&permissions, EXECUTE);
    assert(!has_flag(permissions, EXECUTE));
}

static void test_multiple_flags(void)
{
    uint8_t permissions = 0;

    set_flag(&permissions, READ);
    set_flag(&permissions, EXECUTE);
    set_flag(&permissions, ADMIN);

    assert(has_flag(permissions, READ));
    assert(!has_flag(permissions, WRITE));
    assert(has_flag(permissions, EXECUTE));
    assert(has_flag(permissions, ADMIN));
}

static void test_has_flag_among_others(void)
{
    uint8_t permissions = WRITE | ADMIN;

    assert(!has_flag(permissions, READ));
    assert(has_flag(permissions, WRITE));
    assert(!has_flag(permissions, EXECUTE));
    assert(has_flag(permissions, ADMIN));
}

static void test_set_keeps_other_flags(void)
{
    uint8_t permissions = WRITE | EXECUTE;

    set_flag(&permissions, ADMIN);

    assert(permissions == (WRITE | EXECUTE | ADMIN));
}

static void test_clear_keeps_other_flags(void)
{
    uint8_t permissions = READ | WRITE | EXECUTE | ADMIN;

    clear_flag(&permissions, WRITE);

    assert(permissions == (READ | EXECUTE | ADMIN));
}

static void test_toggle_keeps_other_flags(void)
{
    uint8_t permissions = READ | ADMIN;

    toggle_flag(&permissions, WRITE);
    assert(permissions == (READ | WRITE | ADMIN));

    toggle_flag(&permissions, READ);
    assert(permissions == (WRITE | ADMIN));
}

int main(void)
{
    test_empty();
    test_set_flag();
    test_set_twice();
    test_clear_flag();
    test_clear_missing_flag();
    test_toggle_flag();
    test_multiple_flags();

    test_has_flag_among_others();
    test_set_keeps_other_flags();
    test_clear_keeps_other_flags();
    test_toggle_keeps_other_flags();

    puts("All tests passed");
    return 0;
}
