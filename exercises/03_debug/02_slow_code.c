/*
# Task 2 — Slow code

Все три функции работают правильно, но на больших данных — слишком долго.
В каждой есть место, где одна и та же работа зря повторяется много раз.
Нужно найти эти места и убрать лишнюю работу.

Тесты ограничены по времени: если функция не укладывается в пару секунд,
тест завершается с сообщением `Too slow`.

Как искать: для входа длины n посчитай, сколько раз выполнится каждая
строка, и не забудь про стоимость функций, которые вызываются внутри
цикла. `strlen` и `strcat` каждый раз проходят строку с самого начала.

## Requirements

- Не менять интерфейсы функций и результат их работы.
- После исправления каждая функция должна проходить по данным
  один раз (или постоянное число раз), а не n раз.
- В `count_distinct` значения массива лежат в диапазоне
  0..MAX_VALUE — этим можно воспользоваться.
*/

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUE 999

/* Переводит латинские буквы строки в верхний регистр, на месте. */
void to_upper(char* s)
{
    for (size_t i = 0; i < strlen(s); i++) {
        s[i] = (char)toupper((unsigned char)s[i]);
    }
}

/* Возвращает новую строку: s, повторённая times раз.
   Память освобождает вызывающий код. */
char* repeat(const char* s, size_t times)
{
    char* result = malloc(strlen(s) * times + 1);

    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    for (size_t i = 0; i < times; i++) {
        strcat(result, s);
    }
    return result;
}

/* Количество различных значений в массиве.
   Все значения лежат в диапазоне 0..MAX_VALUE. */
size_t count_distinct(const int* arr, size_t size)
{
    size_t distinct = 0;

    for (size_t i = 0; i < size; i++) {
        int seen_before = 0;

        for (size_t j = 0; j < i; j++) {
            if (arr[j] == arr[i]) {
                seen_before = 1;
                break;
            }
        }
        if (!seen_before) {
            distinct++;
        }
    }
    return distinct;
}

int main(void)
{
    char text[] = "hello, world";
    int values[] = { 1, 2, 2, 3, 3, 3 };
    char* line = repeat("ab", 5);

    to_upper(text);
    printf("%s\n", text);
    if (line != NULL) {
        printf("%s\n", line);
    }
    printf("distinct: %zu\n", count_distinct(values, 6));

    free(line);
    return 0;
}
