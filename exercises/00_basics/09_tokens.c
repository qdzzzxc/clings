/*
# Task 9 — string.h

В `string.h` есть функции, которые ищут символы за нас. Каждую функцию
этой задачи нужно построить на одной из них.

## Нужно реализовать функции

replace_all:
    Заменяет в строке каждый символ `from` на `to` и возвращает
    количество замен. Искать очередной `from` через `strchr`.

is_identifier:
    Возвращает 1, если строка — имя переменной в C: непустая,
    состоит из латинских букв, цифр и '_' и не начинается с цифры.
    Проверить «состоит только из» через `strspn`.

count_sentences:
    Считает предложения. Предложение заканчивается группой из одного
    или нескольких символов '.', '!', '?': "Ну что?!" — одно предложение,
    "Ждём..." — тоже одно. Текст после последней такой группы
    предложением не считается. Искать концы через `strpbrk`,
    пропускать группу через `strspn`.
    "Hi. How are you?! Fine..."  ->  3

split_words:
    Разбивает текст на слова через `strtok`. Разделители — символы
    строки `delimiters`. Указатели на слова записывает в `words`,
    но не больше `max_words` штук, и возвращает количество записанных.

## Requirements

- Не перебирать строку посимвольно вручную там, где сказано
  использовать функцию из `string.h`.
- `strtok` портит строку: заменяет разделители на '\0'. Поэтому
  `split_words` получает изменяемую строку, а слова в `words` указывают
  внутрь неё.
- `strtok` хранит состояние между вызовами: первый вызов получает
  строку, следующие — NULL.

## Interfaces

size_t replace_all(char *s, char from, char to);
int is_identifier(const char *s);
size_t count_sentences(const char *text);
size_t split_words(char *text, const char *delimiters,
                   char **words, size_t max_words);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

size_t replace_all(char* s, char from, char to)
{
    /* TODO: реализуйте replace_all. */
    (void)s;
    (void)from;
    (void)to;
    assert(!"TODO: replace_all");
    return 0;
}

int is_identifier(const char* s)
{
    /* TODO: реализуйте is_identifier. */
    (void)s;
    assert(!"TODO: is_identifier");
    return 0;
}

size_t count_sentences(const char* text)
{
    /* TODO: реализуйте count_sentences. */
    (void)text;
    assert(!"TODO: count_sentences");
    return 0;
}

size_t split_words(char* text, const char* delimiters,
    char** words, size_t max_words)
{
    /* TODO: реализуйте split_words. */
    (void)text;
    (void)delimiters;
    (void)words;
    (void)max_words;
    assert(!"TODO: split_words");
    return 0;
}

int main(void)
{
    char path[] = "home/user/projects";
    char text[] = "red, green;blue";
    char* words[8] = { NULL };
    size_t count = 0;

    printf("replaced: %zu, %s\n", replace_all(path, '/', '\\'), path);
    printf("is_identifier(\"_tmp1\"): %d\n", is_identifier("_tmp1"));
    printf("sentences: %zu\n", count_sentences("Hi. How are you?! Fine..."));

    count = split_words(text, " ,;", words, 8);
    for (size_t i = 0; i < count; i++) {
        printf("word: %s\n", words[i]);
    }
    return 0;
}
