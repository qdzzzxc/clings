/* Тесты к exercises/01_files/07_date.c. Запуск: make test 1 7 */

#include <assert.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/01_files/07_date.c"
#undef main

static void check_date(const char* text, int day, int month, int year)
{
    int d = 0;
    int m = 0;
    int y = 0;

    assert(parse_date(text, &d, &m, &y) == 1);
    assert(d == day && m == month && y == year);
}

static void check_error(const char* text)
{
    int d = 11;
    int m = 22;
    int y = 33;

    assert(parse_date(text, &d, &m, &y) == 0);
    assert(d == 11 && m == 22 && y == 33);
}

static void test_days_in_month(void)
{
    assert(days_in_month(1, 2023) == 31);
    assert(days_in_month(4, 2023) == 30);
    assert(days_in_month(12, 2023) == 31);
    assert(days_in_month(2, 2023) == 28);
    assert(days_in_month(2, 2024) == 29);
    assert(days_in_month(2, 2000) == 29);
    assert(days_in_month(2, 1900) == 28);
    assert(days_in_month(2, 2100) == 28);
    assert(days_in_month(0, 2024) == 0);
    assert(days_in_month(13, 2024) == 0);
}

static void test_days_in_every_month(void)
{
    const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    for (int month = 1; month <= 12; month++) {
        assert(days_in_month(month, 2023) == days[month - 1]);
    }
}

static void test_valid_dates(void)
{
    check_date("07/03/2024", 7, 3, 2024);
    check_date("7/3/2024", 7, 3, 2024);
    check_date("31/12/1999", 31, 12, 1999);
    check_date("01/01/1", 1, 1, 1);
    check_date("29/02/2024", 29, 2, 2024);
    check_date("29/02/2000", 29, 2, 2000);
    check_date("30/04/9999", 30, 4, 9999);
}

static void test_newline_from_fgets(void)
{
    check_date("07/03/2024\n", 7, 3, 2024);
}

static void test_wrong_format(void)
{
    check_error("");
    check_error("\n");
    check_error("07-03-2024");
    check_error("07/03");
    check_error("07/03/");
    check_error("date");
    check_error("07/03/2024abc");
    check_error("07/03/2024 x");
    check_error("07/03/20245");
}

static void test_impossible_dates(void)
{
    check_error("00/03/2024");
    check_error("32/01/2024");
    check_error("31/04/2024");
    check_error("29/02/2023");
    check_error("29/02/1900");
    check_error("10/00/2024");
    check_error("10/13/2024");
    check_error("10/10/0");
    check_error("-1/10/2024");
}

int main(void)
{
    test_days_in_month();
    test_days_in_every_month();
    test_valid_dates();
    test_newline_from_fgets();
    test_wrong_format();
    test_impossible_dates();

    puts("All tests passed");
    return 0;
}
