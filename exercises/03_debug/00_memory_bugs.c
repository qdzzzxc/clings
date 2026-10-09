/*
# Task 0 — Memory bugs

В этом файле код уже написан, но в каждой функции есть одна ошибка работы
с памятью. Нужно найти и исправить все четыре.

Тесты собираются с санитайзерами. Когда программа делает что-то
недопустимое, санитайзер останавливает её и печатает отчёт. В отчёте
важны три вещи:

- вид ошибки в первой строке: `heap-buffer-overflow`,
  `stack-buffer-overflow`, `detected memory leaks`;
- верхние строки стека вызовов: файл и номер строки, где это случилось;
- для кучи — где была выделена память («allocated by»).

## Requirements

- Не менять интерфейсы функций и то, что они должны делать
  (это написано в комментарии над каждой).
- Исправлять причину, а не прятать её: не выделять память «с запасом».
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Возвращает сумму элементов массива. */
long long sum_array(const int* arr, size_t size)
{
    long long sum = 0;

    for (size_t i = 0; i <= size; i++) {
        sum += arr[i];
    }
    return sum;
}

/* Возвращает новую копию строки. Память освобождает вызывающий код. */
char* copy_string(const char* s)
{
    size_t length = strlen(s);
    char* copy = malloc(length);

    if (copy == NULL) {
        return NULL;
    }

    for (size_t i = 0; i <= length; i++) {
        copy[i] = s[i];
    }
    return copy;
}

/* Раскладывает число на четыре младшие десятичные цифры:
   digits[0] — единицы, digits[1] — десятки и так далее. */
void split_digits(unsigned value, int* digits)
{
    for (int i = 1; i <= 4; i++) {
        digits[i] = (int)(value % 10);
        value /= 10;
    }
}

/* Возвращает новую строку "<first> <second>".
   Память освобождает вызывающий код. */
char* join_words(const char* first, const char* second)
{
    size_t length = strlen(first) + 1 + strlen(second) + 1;
    char* buffer = malloc(length);
    char* result = malloc(length);

    if (buffer == NULL || result == NULL) {
        free(buffer);
        free(result);
        return NULL;
    }

    strcpy(buffer, first);
    strcat(buffer, " ");
    strcat(buffer, second);

    strcpy(result, buffer);
    return result;
}

int main(void)
{
    int values[] = { 1, 2, 3 };
    int digits[4];
    char* joined = join_words("hello", "world");

    split_digits(1234, digits);

    printf("sum: %lld\n", sum_array(values, 3));
    printf("digits: %d %d %d %d\n", digits[0], digits[1], digits[2], digits[3]);
    if (joined != NULL) {
        printf("%s\n", joined);
    }

    free(joined);
    return 0;
}
