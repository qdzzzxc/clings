/*
# Task 1 — Students

Массив структур: каждый элемент описывает одного студента.

## Нужно реализовать функции

student_init:
    Заполняет структуру. Имя копируется внутрь структуры, в поле `name`.
    Возвращает 0 и не меняет структуру, если имя вместе с '\0'
    не помещается в `NAME_SIZE` или если возраст отрицательный.

best_student:
    Возвращает указатель на студента с наибольшей оценкой.
    При равных оценках — на того, кто стоит в массиве раньше.
    Для пустого массива возвращает NULL.

count_adults:
    Количество студентов, которым 18 лет или больше.

rename_student:
    Меняет имя студента по тем же правилам, что и `student_init`:
    если новое имя не помещается, возвращает 0 и оставляет старое.

## Requirements

- Не писать за границу поля `name`: в нём всегда должна лежать
  корректная строка с '\0' в конце.
- `best_student` возвращает указатель на элемент исходного массива,
  а не на копию.

## Interfaces

#define NAME_SIZE 16

typedef struct {
    char name[NAME_SIZE];
    int age;
    double grade;
} Student;

int student_init(Student *student, const char *name, int age, double grade);
const Student *best_student(const Student *students, size_t count);
size_t count_adults(const Student *students, size_t count);
int rename_student(Student *student, const char *name);

Возвращаемое значение `student_init` и `rename_student`:

1 — успех
0 — ошибка
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define NAME_SIZE 16

typedef struct {
    char name[NAME_SIZE];
    int age;
    double grade;
} Student;

int rename_student(Student* student, const char* name)
{
    /* TODO: реализуйте rename_student. */
    (void)student;
    (void)name;
    assert(!"TODO: rename_student");
    return 0;
}

int student_init(Student* student, const char* name, int age, double grade)
{
    /* TODO: реализуйте student_init. */
    (void)student;
    (void)name;
    (void)age;
    (void)grade;
    assert(!"TODO: student_init");
    return 0;
}

const Student* best_student(const Student* students, size_t count)
{
    /* TODO: реализуйте best_student. */
    (void)students;
    (void)count;
    assert(!"TODO: best_student");
    return NULL;
}

size_t count_adults(const Student* students, size_t count)
{
    /* TODO: реализуйте count_adults. */
    (void)students;
    (void)count;
    assert(!"TODO: count_adults");
    return 0;
}

int main(void)
{
    Student group[3];
    const Student* best;

    if (!student_init(&group[0], "Anna", 19, 4.5)
        || !student_init(&group[1], "Boris", 17, 4.9)
        || !student_init(&group[2], "Vera", 20, 3.8)) {
        return 1;
    }

    best = best_student(group, 3);
    printf("best: %s (%.1f)\n", best->name, best->grade);
    printf("adults: %zu\n", count_adults(group, 3));
    return 0;
}
