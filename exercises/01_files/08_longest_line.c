/*
# Task 8 — Longest line

Вывести самую длинную строку входа. Если таких несколько — первую.

## Example

Input:
one
three
seven
two

Output:
three

## Requirements

- Читать строки целиком через `fgets` в буфер размера `LINE_SIZE`.
  Гарантируется, что любая строка вместе с '\n' и '\0' помещается
  в буфер, так что проверять, дочиталась ли строка, не нужно.
- '\n' в конце строки убирать одним вызовом:
  `line[strcspn(line, "\n")] = '\0';`. Последняя строка может быть
  без '\n' — эта запись работает и для неё.
- Лучшую строку хранить копией во втором буфере (`strcpy`)
  и вывести один раз в конце через `fprintf` или `fputs`,
  с '\n' на конце. Если вход пустой, ничего не выводить.
- Вход читается ровно один раз. Запомнить, где строка начиналась,
  и потом вернуться к ней через `fseek`/`rewind`, нельзя: в тестах
  вход — это pipe, по нему назад не перемотать.
- Не читать по символу: `fgetc` и `getc` запрещены.
- Вернуть длину выведенной строки без '\n' (для пустого входа 0).

## Interface

size_t print_longest_line(FILE *in, FILE *out);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 256

size_t print_longest_line(FILE* in, FILE* out)
{
    /* TODO: реализуйте print_longest_line. */
    (void)in;
    (void)out;
    assert(!"TODO: print_longest_line");
    return 0;
}

int main(int argc, char** argv)
{
    FILE* in = stdin;

    if (argc > 1) {
        in = fopen(argv[1], "r");
        if (in == NULL) {
            perror(argv[1]);
            return 1;
        }
    }
    print_longest_line(in, stdout);
    if (in != stdin) {
        fclose(in);
    }
    return 0;
}
