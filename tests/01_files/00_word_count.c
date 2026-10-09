/* Тесты к exercises/01_files/00_word_count.c. Запуск: make test 1 0 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/01_files/00_word_count.c"
#undef main

#define TEST_PATH ".build/word_count_test.txt"

/* Количество байт всегда должно совпасть с длиной текста. */
static int stream_counts(const char* text, size_t lines, size_t words)
{
    size_t got_lines = 777;
    size_t got_words = 777;
    size_t got_bytes = 777;
    FILE* in = tmpfile();

    assert(in != NULL);
    fputs(text, in);
    rewind(in);

    count_stream(in, &got_lines, &got_words, &got_bytes);
    fclose(in);

    return got_lines == lines && got_words == words && got_bytes == strlen(text);
}

static void test_empty(void)
{
    assert(stream_counts("", 0, 0));
}

static void test_lines_and_words(void)
{
    assert(stream_counts("hello\n", 1, 1));
    assert(stream_counts("hello world\n", 1, 2));
    assert(stream_counts("hello world\nfoo\n", 2, 3));
}

static void test_no_trailing_newline(void)
{
    assert(stream_counts("a b c", 0, 3));
}

static void test_many_spaces(void)
{
    assert(stream_counts("  one \t two\n\n  three  ", 2, 3));
    assert(stream_counts(" \n\t\n", 2, 0));
}

static void test_byte_255_is_not_eof(void)
{
    assert(stream_counts("a\xff"
                         "b\n",
        1, 1));
}

static void test_file(void)
{
    size_t lines = 777;
    size_t words = 777;
    size_t bytes = 777;
    FILE* out = fopen(TEST_PATH, "w");

    assert(out != NULL);
    fputs("one two\nthree\n", out);
    fclose(out);

    assert(count_file(TEST_PATH, &lines, &words, &bytes));
    assert(lines == 2);
    assert(words == 3);
    assert(bytes == 14);

    remove(TEST_PATH);
}

static void test_missing_file(void)
{
    size_t lines = 777;
    size_t words = 777;
    size_t bytes = 777;

    assert(!count_file(".build/no_such_file.txt", &lines, &words, &bytes));
    assert(lines == 777);
    assert(words == 777);
    assert(bytes == 777);
}

int main(void)
{
    test_empty();
    test_lines_and_words();
    test_no_trailing_newline();
    test_many_spaces();
    test_byte_255_is_not_eof();
    test_file();
    test_missing_file();

    puts("All tests passed");
    return 0;
}
