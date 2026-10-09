/*
# Task 3 — qsort

Стандартная функция `qsort` умеет сортировать массив любого типа.
Для этого ей передают функцию сравнения — компаратор:

int compare(const void *left, const void *right);

Компаратор получает указатели на два элемента массива и возвращает
отрицательное число, ноль или положительное число, если левый элемент
должен стоять раньше, равен или должен стоять позже правого.

## Нужно реализовать функции

sort_ints:
    Сортирует числа по возрастанию.

sort_strings:
    Сортирует массив строк по алфавиту (как `strcmp`).

sort_people:
    Сортирует людей по возрасту, от младших к старшим.
    Людей одного возраста — по имени, как `strcmp`.

## Requirements

- Сортировать только через `qsort`, для каждой функции написать
  свой `static`-компаратор.
- В компараторе чисел не вычитать одно из другого: для далёких значений
  разность переполняется. Сравнивать через `<` и `>`.
- Элемент массива строк — это `const char *`, поэтому компаратор
  получает указатель на указатель.

## Interfaces

#define NAME_SIZE 16

typedef struct {
    char name[NAME_SIZE];
    int age;
} Person;

void sort_ints(int *arr, size_t size);
void sort_strings(const char **strings, size_t size);
void sort_people(Person *people, size_t size);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 16

typedef struct {
    char name[NAME_SIZE];
    int age;
} Person;

void sort_ints(int* arr, size_t size)
{
    /* TODO: реализуйте sort_ints. */
    (void)arr;
    (void)size;
    assert(!"TODO: sort_ints");
}

void sort_strings(const char** strings, size_t size)
{
    /* TODO: реализуйте sort_strings. */
    (void)strings;
    (void)size;
    assert(!"TODO: sort_strings");
}

void sort_people(Person* people, size_t size)
{
    /* TODO: реализуйте sort_people. */
    (void)people;
    (void)size;
    assert(!"TODO: sort_people");
}

int main(void)
{
    Person people[] = {
        { "Vera", 20 },
        { "Anna", 19 },
        { "Boris", 20 },
    };

    sort_people(people, 3);

    for (size_t i = 0; i < 3; i++) {
        printf("%d %s\n", people[i].age, people[i].name);
    }
    return 0;
}
