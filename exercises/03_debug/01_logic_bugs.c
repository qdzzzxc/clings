/*
# Task 1 — Logic bugs

Здесь память в порядке, но в каждой из четырёх функций есть ошибка
в логике. Обычные входные данные они обрабатывают правильно, а ломаются
на граничных: пустой массив, одни отрицательные числа, очень большие
значения, ноль.

Часть ошибок — неопределённое поведение, например переполнение знакового
целого. Санитайзер сообщает о нём строкой `runtime error: ...` с номером
строки. Остальные ошибки видны только по упавшему `assert` в тестах.

Полезный приём: прежде чем читать код, выпиши граничные случаи для
функции и мысленно выполни её на каждом.

## Requirements

- Не менять интерфейсы функций и то, что они должны делать
  (это написано в комментарии над каждой).
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

/* Среднее арифметическое с округлением к нулю. Гарантируется size > 0. */
int average(const int* arr, size_t size)
{
    int sum = 0;

    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / (int)size;
}

/* Максимальный элемент массива. Гарантируется size > 0. */
int max_of(const int* arr, size_t size)
{
    int max = 0;

    for (size_t i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/* Индекс последнего элемента, равного value, или -1, если такого нет.
   Массив может быть пустым. */
long find_last(const int* arr, size_t size, int value)
{
    for (size_t i = size - 1; i > 0; i--) {
        if (arr[i] == value) {
            return (long)i;
        }
    }
    return -1;
}

/* Возвращает 1, если x — степень двойки (1, 2, 4, 8, ...), иначе 0. */
int is_power_of_two(unsigned x)
{
    return (x & (x - 1)) == 0;
}

int main(void)
{
    int values[] = { 4, 8, 15, 16, 23, 42 };

    printf("average: %d\n", average(values, 6));
    printf("max: %d\n", max_of(values, 6));
    printf("last 16 at: %ld\n", find_last(values, 6, 16));
    printf("16 is power of two: %d\n", is_power_of_two(16));
    return 0;
}
