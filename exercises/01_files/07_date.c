/*
# Task 7 — Date input

Строку, которую ввёл пользователь, удобно сначала прочитать целиком
через `fgets`, а потом разобрать через `sscanf`. Он возвращает,
сколько значений удалось прочитать, — так видно, что формат нарушен.

## Нужно реализовать функции

days_in_month:
    Количество дней в месяце `month` (1..12) года `year`. В феврале
    високосного года 29 дней. Год високосный, если делится на 4,
    но не на 100, или делится на 400: 2024 и 2000 — високосные,
    1900 и 2023 — нет. Для неправильного месяца вернуть 0.

parse_date:
    Разбирает дату вида DD/MM/YYYY: "07/03/2024". День и месяц могут
    быть из одной цифры: "7/3/2024". Год — от 1 до 9999.
    Проверяет, что такая дата существует: "31/04/2024" и "29/02/2023" —
    ошибка, "29/02/2024" — правильная дата.

## Requirements

- Разбирать через `sscanf` и проверять его результат.
- Строка из `fgets` заканчивается на '\n': он допустим, а любой другой
  мусор после даты — ошибка: "07/03/2024abc", "07/03/20245".
  Подсказка: после года прочитать ещё один символ форматом " %c".
  Пробел в формате пропускает пробельные символы, включая '\n',
  поэтому `sscanf` вернёт 4, только если после даты что-то осталось.
- При ошибке `*day`, `*month` и `*year` не меняются.

## Interfaces

int days_in_month(int month, int year);
int parse_date(const char *text, int *day, int *month, int *year);

Возвращаемое значение `parse_date`:

1 — дата правильная
0 — ошибка
*/

#include <assert.h>
#include <stdio.h>

int days_in_month(int month, int year)
{
    /* TODO: реализуйте days_in_month. */
    (void)month;
    (void)year;
    assert(!"TODO: days_in_month");
    return 0;
}

int parse_date(const char* text, int* day, int* month, int* year)
{
    /* TODO: реализуйте parse_date. */
    (void)text;
    (void)day;
    (void)month;
    (void)year;
    assert(!"TODO: parse_date");
    return 0;
}

int main(void)
{
    char line[64] = "";
    int day = 0;
    int month = 0;
    int year = 0;

    printf("Enter a date (DD/MM/YYYY): ");
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 1;
    }
    if (!parse_date(line, &day, &month, &year)) {
        fprintf(stderr, "Invalid date\n");
        return 1;
    }
    printf("Day: %d, Month: %d, Year: %d\n", day, month, year);
    return 0;
}
