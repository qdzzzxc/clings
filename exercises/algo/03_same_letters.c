/*
# Task 3 — Same letters

На вход подаются две строки. Первая (str1) — слово из малых английских
букв. Вторая (str2) — несколько слов из малых английских букв,
разделённых пробелами. Вернуть число слов второй строки, которые
состоят из тех же букв, что и слово из первой строки.

Количество букв может различаться: считается, что 'abab' и 'aaaab'
состоят из одних и тех же букв ({a, b}). А 'abc' и 'ab' — нет.

1 <= длина str1 <= 50
1 <= длина str2 <= 1000

## Example

Вход:
ab
abab ba aaaab abc a
Ответ: 3 (abab, ba, aaaab)

## Requirements

- Массивы запрещены, поэтому строки не сохранить: читай по символу
  через fgetc. Набор букв слова помещается в одно число — 26 битов,
  бит i означает «в слове есть буква 'a' + i».
- Между словами может быть несколько пробелов, в начале и в конце
  строки — тоже. Строка заканчивается '\n' или концом файла.

## Interface

int countSameLetters(FILE* in);
*/

#include <assert.h>
#include <stdio.h>

int countSameLetters(FILE* in)
{
    /* TODO: реализуйте countSameLetters. */
    (void)in;
    assert(!"TODO: countSameLetters");
    return 0;
}

int main(void)
{
    printf("%d\n", countSameLetters(stdin));
    return 0;
}
