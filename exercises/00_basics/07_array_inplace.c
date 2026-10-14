/*
# Task 7 — Array in place

Три операции, которые меняют массив прямо на месте, без второго массива.

## Нужно реализовать функции

reverse_array:
    Разворачивает массив: 1 2 3 4 -> 4 3 2 1.

rotate_right:
    Циклически сдвигает массив вправо на `k` позиций: последние `k`
    элементов переезжают в начало.
    1 2 3 4 5, k = 2  ->  4 5 1 2 3
    `k` может быть больше `size`: сдвиг на `size` возвращает массив
    в исходное состояние.

move_zeros:
    Переносит все нули в конец массива. Порядок ненулевых элементов
    сохраняется: 0 3 0 1 2 -> 3 1 2 0 0.
    Возвращает количество ненулевых элементов.

## Requirements

- Дополнительные массивы не использовать — ни на стеке, ни в куче.
- `reverse_array` — двумя указателями, которые идут навстречу друг другу.
- `rotate_right` за O(size), а не за O(size * k). Подсказка: развернуть
  весь массив, затем отдельно первые `k` элементов и остальные.
  Удобно, если `reverse_array` можно вызвать для куска массива.
- `move_zeros` за один проход: второй указатель показывает, куда
  положить очередной ненулевой элемент.
- При `size == 0` функции ничего не делают.
- Тесты ограничены по времени.

## Interfaces

void reverse_array(int *arr, size_t size);
void rotate_right(int *arr, size_t size, size_t k);
size_t move_zeros(int *arr, size_t size);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

void swap_nums(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse_array(int* arr, size_t size)
{
    int* left = arr;
    int* right = arr + size - 1;

    while (left < right) {
        swap_nums(left, right);

        left++;
        right--;
    }
}

void rotate_right(int* arr, size_t size, size_t k)
{
    if (size == 0) {
        return;
    }

    k = k % size;

    reverse_array(arr, size);
    reverse_array(arr, k);
    reverse_array(arr + k, size - k);
}

size_t move_zeros(int* arr, size_t size)
{
    size_t count = 0;
    int* slow = arr;
    int* end = arr + size;

    while ((slow < end) && (*slow != 0)) {
        count++;
        slow++;
    }

    if (slow == end) {
        return count;
    }

    int* fast = slow + 1;

    while (fast < end) {
        if (*fast == 0) {
            fast++;
        } else {
            swap_nums(slow, fast);

            count++;
            slow++;
            fast++;
        }
    }

    return count;
}

static void print_array(const int* arr, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    int values[] = { 1, 2, 3, 4, 5 };
    int with_zeros[] = { 0, 3, 0, 1, 2 };
    size_t non_zero = 0;

    reverse_array(values, 5);
    print_array(values, 5);

    rotate_right(values, 5, 2);
    print_array(values, 5);

    non_zero = move_zeros(with_zeros, 5);
    print_array(with_zeros, 5);
    printf("non-zero: %zu\n", non_zero);
    return 0;
}
