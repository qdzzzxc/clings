/* Тесты к exercises/04_structs/01_students.c. Запуск: make test 4 1 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/04_structs/01_students.c"
#undef main

static void test_init(void)
{
    Student student;

    assert(student_init(&student, "Anna", 19, 4.5));
    assert(strcmp(student.name, "Anna") == 0);
    assert(student.age == 19);
    assert(student.grade == 4.5);
}

static void test_init_copies_the_name(void)
{
    char name[] = "Boris";
    Student student;

    assert(student_init(&student, name, 20, 3.0));
    name[0] = 'M';

    assert(strcmp(student.name, "Boris") == 0);
}

static void test_name_length_limit(void)
{
    Student student;

    /* 15 символов и '\0' — ровно NAME_SIZE. */
    assert(student_init(&student, "123456789012345", 18, 5.0));
    assert(strcmp(student.name, "123456789012345") == 0);
    assert(student.age == 18);

    assert(student_init(&student, "", 18, 5.0));
    assert(student.name[0] == '\0');
}

static void test_init_rejects_bad_data(void)
{
    Student student;

    assert(student_init(&student, "Vera", 21, 4.0));

    assert(!student_init(&student, "1234567890123456", 30, 2.0));
    assert(!student_init(&student, "A very long name that does not fit", 30, 2.0));
    assert(!student_init(&student, "Gleb", -1, 2.0));

    assert(strcmp(student.name, "Vera") == 0);
    assert(student.age == 21);
    assert(student.grade == 4.0);
}

static void test_rename(void)
{
    Student student;

    assert(student_init(&student, "Vera", 21, 4.0));

    assert(rename_student(&student, "Veronika"));
    assert(strcmp(student.name, "Veronika") == 0);

    assert(!rename_student(&student, "1234567890123456"));
    assert(strcmp(student.name, "Veronika") == 0);

    assert(student.age == 21);
    assert(student.grade == 4.0);
}

static void fill_group(Student* group)
{
    assert(student_init(&group[0], "Anna", 19, 4.5));
    assert(student_init(&group[1], "Boris", 17, 4.9));
    assert(student_init(&group[2], "Vera", 18, 3.8));
    assert(student_init(&group[3], "Gleb", 16, 4.9));
}

static void test_best_student(void)
{
    Student group[4];

    fill_group(group);

    assert(best_student(group, 4) == &group[1]);
    assert(best_student(group, 1) == &group[0]);
    assert(best_student(group + 2, 2) == &group[3]);
    assert(best_student(group, 0) == NULL);
}

static void test_best_student_with_negative_grades(void)
{
    Student group[2];

    assert(student_init(&group[0], "Anna", 19, -2.0));
    assert(student_init(&group[1], "Boris", 19, -1.0));

    assert(best_student(group, 2) == &group[1]);
}

static void test_count_adults(void)
{
    Student group[4];

    fill_group(group);

    assert(count_adults(group, 4) == 2);
    assert(count_adults(group, 1) == 1);
    assert(count_adults(group + 3, 1) == 0);
    assert(count_adults(group, 0) == 0);
}

int main(void)
{
    test_init();
    test_init_copies_the_name();
    test_name_length_limit();
    test_init_rejects_bad_data();
    test_rename();
    test_best_student();
    test_best_student_with_negative_grades();
    test_count_adults();

    puts("All tests passed");
    return 0;
}
