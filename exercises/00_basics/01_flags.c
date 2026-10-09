/*
# Task 1 — Flags

Есть набор флагов доступа:

READ    — бит 0
WRITE   — бит 1
EXECUTE — бит 2
ADMIN   — бит 3

Несколько флагов могут одновременно храниться в одном `uint8_t`.

Например:

00000101
       ^^
       READ + EXECUTE

## Нужно реализовать функции

has_flag:
    Проверяет, установлен ли переданный флаг.

set_flag:
    Устанавливает флаг, не изменяя остальные.

clear_flag:
    Сбрасывает флаг, не изменяя остальные.

toggle_flag:
    Меняет состояние флага на противоположное.

## Requirements

- Использовать побитовые операции.
- Не использовать арифметику вида + / - для установки и сброса флагов.
- Не использовать массивы.
- Не хардкодить готовые значения вроде 1, 2, 4, 8:
  значения флагов получить с помощью сдвига `<<`.
- `has_flag` должна возвращать `bool`.
*/

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

enum Permission {
    READ = 1 << 0,
    WRITE = 1 << 1,
    EXECUTE = 1 << 2,
    ADMIN = 1 << 3,
};

bool has_flag(uint8_t permissions, enum Permission flag)
{
    return (permissions & flag) != 0;
}

void set_flag(uint8_t* permissions, enum Permission flag)
{
    *permissions |= flag;
}

void clear_flag(uint8_t* permissions, enum Permission flag)
{
    *permissions &= ~flag;
}

void toggle_flag(uint8_t* permissions, enum Permission flag)
{
    *permissions ^= flag;
}

int main(void)
{
    uint8_t permissions = 0;

    int flag_number = 0;

    printf("Choose flag:\n");
    printf("0 - READ\n");
    printf("1 - WRITE\n");
    printf("2 - EXECUTE\n");
    printf("3 - ADMIN\n");

    if (scanf("%d", &flag_number) != 1) {
        return 1;
    }

    enum Permission flag;

    switch (flag_number) {
    case 0:
        flag = READ;
        break;
    case 1:
        flag = WRITE;
        break;
    case 2:
        flag = EXECUTE;
        break;
    case 3:
        flag = ADMIN;
        break;
    default:
        printf("Unknown flag\n");
        return 1;
    }

    set_flag(&permissions, flag);

    printf("permissions = %u\n", (unsigned int)permissions);

    printf("READ: %d\n", has_flag(permissions, READ));
    printf("WRITE: %d\n", has_flag(permissions, WRITE));
    printf("EXECUTE: %d\n", has_flag(permissions, EXECUTE));
    printf("ADMIN: %d\n", has_flag(permissions, ADMIN));

    return 0;
}
