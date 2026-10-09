/*
# Task 0 — Word count

Написать упрощённый `wc`: посчитать в файле строки, слова и байты.

## Example

Файл:

hello world
foo

Результат: lines = 2, words = 3, bytes = 16

## Requirements

- `count_stream` читает уже открытый поток до конца через `fgetc`.
- Результат `fgetc` хранить в `int`, а не в `char`: иначе байт 255
  не отличить от `EOF`.
- Строки — это количество символов '\n'.
- Слово — последовательность непробельных символов. Пробельные символы
  определять через `isspace`.
- `count_file` открывает файл по имени, вызывает `count_stream`
  и закрывает файл.
- Если файл не открылся, `count_file` возвращает 0 и не меняет результаты.

## Interfaces

void count_stream(FILE *in, size_t *lines, size_t *words, size_t *bytes);

int count_file(const char *path, size_t *lines, size_t *words, size_t *bytes);

Возвращаемое значение `count_file`:

1 — успех
0 — ошибка
*/

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

void count_stream(FILE* in, size_t* lines, size_t* words, size_t* bytes)
{
    /* TODO: реализуйте count_stream. */
    (void)in;
    (void)lines;
    (void)words;
    (void)bytes;
    assert(!"TODO: count_stream");
}

int count_file(const char* path, size_t* lines, size_t* words, size_t* bytes)
{
    /* TODO: реализуйте count_file. */
    (void)path;
    (void)lines;
    (void)words;
    (void)bytes;
    assert(!"TODO: count_file");
    return 0;
}

int main(int argc, char** argv)
{
    size_t lines = 0;
    size_t words = 0;
    size_t bytes = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    if (!count_file(argv[1], &lines, &words, &bytes)) {
        fprintf(stderr, "Cannot open %s\n", argv[1]);
        return 1;
    }

    printf("%zu %zu %zu %s\n", lines, words, bytes, argv[1]);
    return 0;
}
