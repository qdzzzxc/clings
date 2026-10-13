/*
# Task 4 — System calls

`fopen`, `fread` и `fwrite` — обёртки стандартной библиотеки. Под ними
лежат системные вызовы `open`, `read`, `write` и `close`: они работают
с файловым дескриптором (`int`) и не буферизуют данные — каждый вызов
идёт в ядро. Поэтому читать и писать нужно сразу блоками.

## Нужно реализовать функцию

copy_file:
    Копирует файл `from` в файл `to` и возвращает количество
    скопированных байт. Если `to` существует, он перезаписывается.
    При любой ошибке возвращает -1.

## Requirements

- Только `open`, `read`, `write`, `close` из `<fcntl.h>` и `<unistd.h>`.
  `FILE *` и функции `stdio.h` для работы с файлами не использовать.
- `from` открывать с `O_RDONLY`, `to` — с `O_WRONLY | O_CREAT | O_TRUNC`
  и правами 0644.
- Читать в цикле блоками по `BUFFER_SIZE` байт в буфер на стеке.
  `read` возвращает число прочитанных байт, 0 в конце файла и -1
  при ошибке. Прочитать он может меньше, чем просили.
- `write` тоже может записать меньше, чем просили: дописывать
  остаток в цикле, пока блок не запишется целиком.
- Закрывать оба файла на всех путях, включая ошибки. Незакрытый
  дескриптор тесты считают утечкой.
- `close` тоже может вернуть ошибку: для `to` её надо проверить,
  потому что данные могут окончательно записаться только при закрытии.

## Interface

long copy_file(const char *from, const char *to);
*/

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

long copy_file(const char* from, const char* to)
{
    /* TODO: реализуйте copy_file. */
    (void)from;
    (void)to;
    assert(!"TODO: copy_file");
    return -1;
}

int main(int argc, char** argv)
{
    long copied = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <from> <to>\n", argv[0]);
        return 1;
    }

    copied = copy_file(argv[1], argv[2]);
    if (copied < 0) {
        perror("copy_file");
        return 1;
    }
    printf("copied %ld bytes\n", copied);
    return 0;
}
