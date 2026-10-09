/* Тесты к exercises/01_files/02_grep.c. Запуск: make test 1 2 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/01_files/02_grep.c"
#undef main

static int grep_gives(const char* input, const char* needle, const char* expected, size_t expected_count)
{
    char output[1024];
    FILE* in = tmpfile();
    FILE* out = tmpfile();
    size_t count;
    size_t length;

    assert(in != NULL && out != NULL);
    fputs(input, in);
    rewind(in);

    count = grep_stream(in, out, needle);

    rewind(out);
    length = fread(output, 1, sizeof(output) - 1, out);
    output[length] = '\0';

    fclose(in);
    fclose(out);

    return count == expected_count && strcmp(output, expected) == 0;
}

static void test_example(void)
{
    assert(grep_gives("apple\nbanana\npineapple\n", "apple", "1:apple\n3:pineapple\n", 2));
}

static void test_no_matches(void)
{
    assert(grep_gives("apple\nbanana\n", "kiwi", "", 0));
    assert(grep_gives("", "kiwi", "", 0));
}

static void test_match_in_the_middle(void)
{
    assert(grep_gives("one two three\nfour\n", "two", "1:one two three\n", 1));
}

static void test_last_line_without_newline(void)
{
    assert(grep_gives("one\ntwo", "two", "2:two\n", 1));
    assert(grep_gives("one", "one", "1:one\n", 1));
}

static void test_empty_lines_are_numbered(void)
{
    assert(grep_gives("\nfoo\n\nfoo\n", "foo", "2:foo\n4:foo\n", 2));
}

static void test_empty_needle_matches_everything(void)
{
    assert(grep_gives("a\n\nb\n", "", "1:a\n2:\n3:b\n", 3));
}

static void test_case_sensitive(void)
{
    assert(grep_gives("Apple\napple\n", "apple", "2:apple\n", 1));
}

static void test_long_line(void)
{
    char input[LINE_SIZE + 16];
    char expected[LINE_SIZE + 16];

    /* Строка максимальной длины: LINE_SIZE - 2 символа и '\n'. */
    memset(input, 'x', LINE_SIZE - 2);
    input[LINE_SIZE - 3] = 'y';
    strcpy(input + LINE_SIZE - 2, "\nshort y\n");

    strcpy(expected, "1:");
    memset(expected + 2, 'x', LINE_SIZE - 2);
    expected[LINE_SIZE - 1] = 'y';
    strcpy(expected + LINE_SIZE, "\n2:short y\n");

    assert(grep_gives(input, "y", expected, 2));
}

int main(void)
{
    test_example();
    test_no_matches();
    test_match_in_the_middle();
    test_last_line_without_newline();
    test_empty_lines_are_numbered();
    test_empty_needle_matches_everything();
    test_case_sensitive();
    test_long_line();

    puts("All tests passed");
    return 0;
}
