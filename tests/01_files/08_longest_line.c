/* Тесты к exercises/01_files/08_longest_line.c. Запуск: make test 1 8 */

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/01_files/08_longest_line.c"
#undef main

#define SOURCE_PATH "exercises/01_files/08_longest_line.c"

/* Поток для чтения из pipe: по нему нельзя перемотать назад. */
static FILE* pipe_with(const char* input)
{
    int fds[2] = { -1, -1 };
    size_t length = strlen(input);
    FILE* in = NULL;

    /* Весь вход должен влезть в буфер pipe, иначе write заблокируется. */
    assert(length < 60000);
    assert(pipe(fds) == 0);
    assert(write(fds[1], input, length) == (ssize_t)length);
    close(fds[1]);
    in = fdopen(fds[0], "r");
    assert(in != NULL);
    return in;
}

static int longest_gives(const char* input, const char* expected, size_t expected_length)
{
    static char output[LINE_SIZE * 2];
    FILE* in = pipe_with(input);
    FILE* out = tmpfile();
    size_t length = 0;
    size_t result = 0;

    assert(out != NULL);
    result = print_longest_line(in, out);

    rewind(out);
    length = fread(output, 1, sizeof(output) - 1, out);
    output[length] = '\0';

    fclose(in);
    fclose(out);
    return result == expected_length && strcmp(output, expected) == 0;
}

/* Читает исходник решения без комментариев и строковых литералов. */
static char* read_code(void)
{
    FILE* file = fopen(SOURCE_PATH, "r");
    char* code = NULL;
    size_t size = 0;
    long length = 0;
    int c = 0;
    int next = 0;

    assert(file != NULL && "тесты запускаются из корня репозитория");
    assert(fseek(file, 0, SEEK_END) == 0 && (length = ftell(file)) >= 0);
    rewind(file);
    code = malloc((size_t)length + 1);
    assert(code != NULL);
    while ((c = fgetc(file)) != EOF) {
        if (c == '/' && (next = fgetc(file)) == '*') {
            int prev = 0;

            while ((c = fgetc(file)) != EOF && !(prev == '*' && c == '/')) {
                prev = c;
            }
            c = ' ';
        } else if (c == '/' && next == '/') {
            while ((c = fgetc(file)) != EOF && c != '\n') {
            }
            c = '\n';
        } else if (c == '/') {
            ungetc(next, file);
        } else if (c == '"' || c == '\'') {
            int quote = c;

            while ((c = fgetc(file)) != EOF && c != quote) {
                if (c == '\\') {
                    fgetc(file);
                }
            }
            c = ' ';
        }
        if (c != EOF) {
            code[size++] = (char)c;
        }
    }
    code[size] = '\0';
    fclose(file);
    return code;
}

/* Встречается ли в коде идентификатор name. */
static bool uses(const char* code, const char* name)
{
    size_t length = strlen(name);

    for (const char* p = strstr(code, name); p != NULL; p = strstr(p + 1, name)) {
        bool left = p == code || !(isalnum((unsigned char)p[-1]) || p[-1] == '_');
        bool right = !(isalnum((unsigned char)p[length]) || p[length] == '_');

        if (left && right) {
            return true;
        }
    }
    return false;
}

static void test_no_char_by_char_and_no_rewind(void)
{
    static const char* const forbidden[] = { "fgetc", "getc", "fseek", "rewind", "ftell", "fsetpos", NULL };
    char* code = read_code();
    int found = 0;

    for (size_t i = 0; forbidden[i] != NULL; i++) {
        if (uses(code, forbidden[i])) {
            fprintf(stderr, "%s: `%s` не используется в этой задаче\n", SOURCE_PATH, forbidden[i]);
            found++;
        }
    }
    free(code);
    assert(found == 0 && "читать строками через fgets, без перемотки");
}

static void test_example(void)
{
    assert(longest_gives("one\nthree\nseven\ntwo\n", "three\n", 5));
}

static void test_first_of_equal(void)
{
    assert(longest_gives("abc\nxyz\nqwe\n", "abc\n", 3));
    assert(longest_gives("a\nbb\ncc\nd\n", "bb\n", 2));
}

static void test_longest_is_last(void)
{
    assert(longest_gives("a\nbb\nccc\n", "ccc\n", 3));
    assert(longest_gives("a\nbb\nccc", "ccc\n", 3));
}

static void test_single_line(void)
{
    assert(longest_gives("hello", "hello\n", 5));
    assert(longest_gives("hello\n", "hello\n", 5));
}

static void test_empty(void)
{
    assert(longest_gives("", "", 0));
    assert(longest_gives("\n", "\n", 0));
    assert(longest_gives("\n\n\n", "\n", 0));
}

static void test_spaces_count(void)
{
    assert(longest_gives("ab\n    \nabc\n", "    \n", 4));
    assert(longest_gives("x\n a b \n", " a b \n", 5));
}

static void test_max_length(void)
{
    char input[LINE_SIZE * 3];
    char expected[LINE_SIZE];

    /* Самая длинная допустимая строка: LINE_SIZE - 2 символа, '\n' и '\0'. */
    memset(expected, 'x', LINE_SIZE - 2);
    expected[LINE_SIZE - 2] = '\n';
    expected[LINE_SIZE - 1] = '\0';
    snprintf(input, sizeof(input), "short\n%sy\n", expected);
    assert(longest_gives(input, expected, LINE_SIZE - 2));
}

static void test_many_lines(void)
{
    static char input[50000];
    size_t used = 0;

    for (int i = 0; i < 2000; i++) {
        used += (size_t)snprintf(input + used, sizeof(input) - used, "%d\n", i * 37 % 1000);
    }
    snprintf(input + used, sizeof(input) - used, "longest line\nshort\n");
    assert(longest_gives(input, "longest line\n", 12));
}

int main(void)
{
    test_no_char_by_char_and_no_rewind();
    test_example();
    test_first_of_equal();
    test_longest_is_last();
    test_single_line();
    test_empty();
    test_spaces_count();
    test_max_length();
    test_many_lines();

    puts("All tests passed");
    return 0;
}
