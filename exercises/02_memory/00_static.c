/*
# Task 0 — Static storage

Обычная локальная переменная исчезает при выходе из функции. Переменная
со статическим временем жизни существует всю работу программы и сохраняет
значение между вызовами.

## Нужно реализовать функции

next_id:
    При каждом вызове возвращает следующий номер: 1, 2, 3, ...

reset_ids:
    После вызова `next_id` снова начинает с 1.

day_name:
    Для номера дня 1..7 возвращает "Mon", "Tue", "Wed", "Thu", "Fri",
    "Sat", "Sun". Для остальных значений возвращает NULL.

## Requirements

- Счётчик хранить в `static`-переменной на уровне файла: она общая для
  `next_id` и `reset_ids`, но не видна из других файлов.
- `day_name` возвращает указатель на строку из статической таблицы.
  Не использовать `malloc` и не возвращать адрес локального массива `char`.
- Для одного и того же дня `day_name` всегда возвращает один и тот же
  указатель.

## Interfaces

unsigned next_id(void);
void reset_ids(void);
const char *day_name(int day);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

unsigned next_id(void)
{
    /* TODO: реализуйте next_id. */
    assert(!"TODO: next_id");
    return 0;
}

void reset_ids(void)
{
    /* TODO: реализуйте reset_ids. */
    assert(!"TODO: reset_ids");
}

const char* day_name(int day)
{
    /* TODO: реализуйте day_name. */
    (void)day;
    assert(!"TODO: day_name");
    return NULL;
}

int main(void)
{
    for (int day = 1; day <= 7; day++) {
        printf("%u: %s\n", next_id(), day_name(day));
    }
    return 0;
}
