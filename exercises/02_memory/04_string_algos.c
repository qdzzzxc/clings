/*
# Task 4 — String algorithms

Три классических алгоритма над строками.

## Нужно реализовать функции

reverse:
    Разворачивает строку на месте: "abc" -> "cba".

is_palindrome:
    Проверяет, читается ли строка одинаково в обе стороны. Учитываются
    только буквы и цифры, регистр не важен:
    "A man, a plan, a canal: Panama" — палиндром.
    Строка без букв и цифр тоже считается палиндромом.

trim:
    Возвращает новую строку без пробельных символов в начале и в конце.
    Пробелы внутри строки сохраняются: "  a b  " -> "a b".

## Requirements

- `reverse` и `is_palindrome` работают двумя указателями (или индексами),
  которые идут навстречу друг другу, без дополнительной памяти.
- Буквы и цифры определять через `isalnum`, регистр приводить через
  `tolower`, пробельные символы определять через `isspace`.
- `trim` выделяет память через `malloc` ровно под результат и не меняет
  исходную строку. Результат освобождает вызывающий код.

## Interfaces

void reverse(char *s);
int is_palindrome(const char *s);
char *trim(const char *s);
*/

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char* s)
{
    /* TODO: реализуйте reverse. */
    (void)s;
    assert(!"TODO: reverse");
}

int is_palindrome(const char* s)
{
    /* TODO: реализуйте is_palindrome. */
    (void)s;
    assert(!"TODO: is_palindrome");
    return 0;
}

char* trim(const char* s)
{
    /* TODO: реализуйте trim. */
    (void)s;
    assert(!"TODO: trim");
    return NULL;
}

int main(void)
{
    char word[] = "stressed";
    char* trimmed = trim("   hello world \n");

    reverse(word);
    printf("%s\n", word);
    printf("%d\n", is_palindrome("A man, a plan, a canal: Panama"));

    if (trimmed != NULL) {
        printf("[%s]\n", trimmed);
    }
    free(trimmed);
    return 0;
}
