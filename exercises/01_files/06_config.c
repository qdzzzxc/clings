/*
# Task 6 — Config file

Многие программы читают настройки из текстового файла такого вида:

# настройки сервера
host = example.com
port = 8080

name = My server

Нужно прочитать такой файл в массив пар «ключ — значение».

## Формат

- Файл читается построчно. Пробельные символы в начале и в конце
  строки не считаются.
- Пустые строки и строки, которые начинаются с '#', пропускаются.
- Остальные строки имеют вид `ключ = значение`. Ключ — текст до первого
  '=', значение — после него; пробелы вокруг обоих отбрасываются.
  Внутри значения пробелы сохраняются: "My server".
- Ключ непустой и без пробельных символов внутри. Значение может быть
  пустым: `comment =`.
- Если ключ повторяется, действует последнее значение.

## Нужно реализовать функции

config_load:
    Читает файл `path` в `entries` (не больше `capacity` записей)
    и записывает количество записей в `*count`.

config_get:
    Возвращает значение по ключу или NULL, если ключа нет.

## Ошибки

`config_load` возвращает 0 и пишет в поток `errors` одну строку:

- если файл не открылся: `<path>: <описание ошибки>`. Описание —
  `strerror(errno)` сразу после неудачного `fopen`;
- если строка файла неправильная (нет '=', пустой ключ, пробел
  в ключе, ключ или значение не помещаются в поле, записей больше
  `capacity`): `<path>:<номер строки>: <что не так>`. Строки нумеруются
  с 1, текст после номера — на твоё усмотрение.

При ошибке `*count` не меняется.

## Requirements

- Читать через `fgets` в буфер `LINE_SIZE`. Гарантируется, что любая
  строка вместе с '\n' короче `LINE_SIZE`.
- '=' искать через `strchr`.
- Ключ с '\0' должен помещаться в `KEY_SIZE`, значение — в `VALUE_SIZE`.
- Файл закрывать на всех путях, включая ошибки.

## Interfaces

#define KEY_SIZE 32
#define VALUE_SIZE 64

typedef struct {
    char key[KEY_SIZE];
    char value[VALUE_SIZE];
} ConfigEntry;

int config_load(const char *path, ConfigEntry *entries, size_t capacity,
                size_t *count, FILE *errors);
const char *config_get(const ConfigEntry *entries, size_t count,
                       const char *key);

Возвращаемое значение `config_load`:

1 — успех
0 — ошибка
*/

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 256
#define KEY_SIZE 32
#define VALUE_SIZE 64

typedef struct {
    char key[KEY_SIZE];
    char value[VALUE_SIZE];
} ConfigEntry;

int config_load(const char* path, ConfigEntry* entries, size_t capacity,
    size_t* count, FILE* errors)
{
    /* TODO: реализуйте config_load. */
    (void)path;
    (void)entries;
    (void)capacity;
    (void)count;
    (void)errors;
    assert(!"TODO: config_load");
    return 0;
}

const char* config_get(const ConfigEntry* entries, size_t count,
    const char* key)
{
    /* TODO: реализуйте config_get. */
    (void)entries;
    (void)count;
    (void)key;
    assert(!"TODO: config_get");
    return NULL;
}

int main(int argc, char** argv)
{
    ConfigEntry entries[16];
    size_t count = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <config>\n", argv[0]);
        return 1;
    }
    if (!config_load(argv[1], entries, 16, &count, stderr)) {
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s -> '%s'\n", entries[i].key, entries[i].value);
    }
    return 0;
}
