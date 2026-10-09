/*
# Task 2 — Grep

Вывести строки, в которых встречается подстрока, вместе с их номерами.

## Example

Input:
apple
banana
pineapple

Подстрока: apple

Output:
1:apple
3:pineapple

## Requirements

- Читать построчно через `fgets` в буфер размера `LINE_SIZE`.
  Гарантируется, что любая строка вместе с '\n' короче `LINE_SIZE`.
- Искать подстроку через `strstr`.
- Писать через `fprintf` в формате `<номер>:<строка>`. Нумерация с 1.
- Последняя строка входа может не заканчиваться на '\n'.
  В выводе каждая строка заканчивается на '\n' ровно один раз.
- Вернуть количество найденных строк.

## Interface

size_t grep_stream(FILE *in, FILE *out, const char *needle);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 256

size_t grep_stream(FILE* in, FILE* out, const char* needle)
{
    /* TODO: реализуйте grep_stream. */
    (void)in;
    (void)out;
    (void)needle;
    assert(!"TODO: grep_stream");
    return 0;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <substring>  (text is read from stdin)\n", argv[0]);
        return 1;
    }

    return grep_stream(stdin, stdout, argv[1]) > 0 ? 0 : 1;
}
