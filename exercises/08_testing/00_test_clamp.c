/*
# Task 0 — Tests for clamp

До сих пор тесты были готовы, а писать нужно было функцию. Здесь
наоборот: описание функции есть, а написать нужно проверку для неё.

## Что проверяем

int clamp(int value, int low, int high);

Функция «зажимает» значение в отрезок [low, high]:

- если value < low  — возвращает low;
- если value > high — возвращает high;
- иначе возвращает value.

Гарантируется, что low <= high.

## Нужно реализовать функцию

clamp_is_correct:
    Получает указатель на какую-то реализацию `clamp` и возвращает 1,
    если она ведёт себя по описанию, и 0, если нашлась ошибка.

Проверяется это так: твоей функции по очереди дают правильную реализацию
и несколько реализаций с разными ошибками. Правильную нужно принять,
каждую ошибочную — отвергнуть.

## Requirements

- Не использовать `assert`: при ошибке нужно вернуть 0, а не завершить
  программу.
- Хороший набор проверок получается из вопроса «где здесь можно
  ошибиться?»: значение ниже отрезка, выше, внутри, ровно на границе,
  отрицательные числа, отрезок из одной точки.
- Не перебирать тысячи случайных значений: достаточно десятка
  осмысленных проверок.

## Interface

typedef int (*ClampFn)(int value, int low, int high);

int clamp_is_correct(ClampFn clamp);
*/

#include <assert.h>
#include <stdio.h>

typedef int (*ClampFn)(int value, int low, int high);

int clamp_is_correct(ClampFn clamp)
{
    /* TODO: реализуйте clamp_is_correct. */
    (void)clamp;
    assert(!"TODO: clamp_is_correct");
    return 0;
}

static int my_clamp(int value, int low, int high)
{
    if (value < low) {
        return low;
    }
    if (value > high) {
        return high;
    }
    return value;
}

int main(void)
{
    printf("my_clamp is correct: %d\n", clamp_is_correct(my_clamp));
    return 0;
}
