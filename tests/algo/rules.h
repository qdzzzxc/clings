/*
Правила контрольной. Тест вызывает CHECK_RULES() до проверки ответов:
если файл с решением нарушает правила, тест падает сразу —
на контрольной за такое решение ставят 0.

- Каждая переменная инициализируется при объявлении.
- Параметр-указатель, по которому функция ничего не пишет,
  объявлен как указатель на const: `const Node* head`.
- Код отформатирован clang-format по .clang-format из корня (WebKit).

Проверка инициализации и const — разбор исходника по токенам, а не
настоящий компилятор: необычный код она может не понять. Пиши просто.
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RULES_TOKEN_SIZE 64
#define RULES_MAX_TYPEDEFS 64
#define RULES_MAX_FUNCTIONS 64

typedef struct {
    char text[RULES_TOKEN_SIZE];
    int line;
    bool word;
} RulesToken;

typedef struct {
    size_t name;
    size_t open;
    size_t close;
    size_t body;
    size_t end;
    bool returns_mutable_pointer;
} RulesFunction;

typedef struct {
    const char* path;
    RulesToken* tokens;
    size_t count;
    size_t capacity;
    char typedefs[RULES_MAX_TYPEDEFS][RULES_TOKEN_SIZE];
    size_t typedef_count;
    RulesFunction functions[RULES_MAX_FUNCTIONS];
    size_t function_count;
    int errors;
} Rules;

enum { RULES_PARAM_OTHER,
    RULES_PARAM_CONST_POINTER,
    RULES_PARAM_MUTABLE_POINTER };

static void rules_error(Rules* r, int line, const char* message, const char* name)
{
    fprintf(stderr, "%s:%d: ", r->path, line);
    fprintf(stderr, message, name);
    fputc('\n', stderr);
    r->errors++;
}

static bool rules_eq(const Rules* r, size_t i, const char* text)
{
    return i < r->count && strcmp(r->tokens[i].text, text) == 0;
}

static bool rules_in(const char* text, const char* const* list)
{
    for (size_t i = 0; list[i] != NULL; i++) {
        if (strcmp(text, list[i]) == 0) {
            return true;
        }
    }
    return false;
}

static bool rules_type_word(const Rules* r, const char* text)
{
    static const char* const words[] = { "void", "char", "short", "int", "long", "float", "double",
        "signed", "unsigned", "_Bool", "bool", "const", "volatile", "static", "register", "extern",
        "inline", "restrict", "FILE", NULL };
    size_t length = strlen(text);

    if (rules_in(text, words) || (length > 2 && strcmp(text + length - 2, "_t") == 0)) {
        return true;
    }
    for (size_t i = 0; i < r->typedef_count; i++) {
        if (strcmp(text, r->typedefs[i]) == 0) {
            return true;
        }
    }
    return false;
}

static bool rules_assign_op(const Rules* r, size_t i)
{
    static const char* const ops[] = { "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=",
        ">>=", NULL };

    return i < r->count && rules_in(r->tokens[i].text, ops);
}

static size_t rules_punct_length(const char* p)
{
    static const char* const three[] = { "<<=", ">>=", "...", NULL };
    static const char* const two[] = { "->", "++", "--", "<<", ">>", "<=", ">=", "==", "!=", "&&",
        "||", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "##", NULL };

    for (size_t i = 0; three[i] != NULL; i++) {
        if (strncmp(p, three[i], 3) == 0) {
            return 3;
        }
    }
    for (size_t i = 0; two[i] != NULL; i++) {
        if (strncmp(p, two[i], 2) == 0) {
            return 2;
        }
    }
    return 1;
}

static void rules_push(Rules* r, const char* begin, size_t length, int line, bool word)
{
    if (r->count == r->capacity) {
        size_t capacity = r->capacity == 0 ? 256 : r->capacity * 2;
        RulesToken* tokens = realloc(r->tokens, capacity * sizeof(RulesToken));

        if (tokens == NULL) {
            fputs("rules: out of memory\n", stderr);
            exit(1);
        }
        r->tokens = tokens;
        r->capacity = capacity;
    }
    if (length >= RULES_TOKEN_SIZE) {
        length = RULES_TOKEN_SIZE - 1;
    }
    memcpy(r->tokens[r->count].text, begin, length);
    r->tokens[r->count].text[length] = '\0';
    r->tokens[r->count].line = line;
    r->tokens[r->count].word = word;
    r->count++;
}

/* Токены кода без комментариев и директив препроцессора. */
static void rules_tokenize(Rules* r, const char* p)
{
    int line = 1;
    bool line_start = true;
    bool directive = false;

    while (*p != '\0') {
        const char* begin = p;
        bool word = false;

        if (p[0] == '\\' && p[1] == '\n') {
            p += 2;
            line++;
            continue;
        }
        if (*p == '\n') {
            p++;
            line++;
            line_start = true;
            directive = false;
            continue;
        }
        if (isspace((unsigned char)*p)) {
            p++;
            continue;
        }
        if (p[0] == '/' && p[1] == '/') {
            while (*p != '\0' && *p != '\n') {
                p++;
            }
            continue;
        }
        if (p[0] == '/' && p[1] == '*') {
            p += 2;
            while (*p != '\0' && !(p[0] == '*' && p[1] == '/')) {
                line += *p == '\n';
                p++;
            }
            p += *p != '\0' ? 2 : 0;
            continue;
        }
        if (line_start && *p == '#') {
            directive = true;
        }
        line_start = false;

        if (*p == '"' || *p == '\'') {
            char quote = *p++;

            while (*p != '\0' && *p != quote && *p != '\n') {
                p += p[0] == '\\' && p[1] != '\0' ? 2 : 1;
            }
            p += *p == quote;
        } else if (isalpha((unsigned char)*p) || *p == '_') {
            while (isalnum((unsigned char)*p) || *p == '_') {
                p++;
            }
            word = true;
        } else if (isdigit((unsigned char)*p) || (*p == '.' && isdigit((unsigned char)p[1]))) {
            while (isalnum((unsigned char)*p) || *p == '.' || *p == '_'
                || ((*p == '+' || *p == '-') && strchr("eEpP", p[-1]) != NULL)) {
                p++;
            }
        } else {
            p += rules_punct_length(p);
        }

        if (!directive) {
            rules_push(r, begin, (size_t)(p - begin), line, word);
        }
    }
}

/* tokens[i] — открывающая скобка. Возвращает индекс парной закрывающей. */
static size_t rules_match(const Rules* r, size_t i)
{
    int depth = 0;

    for (; i < r->count; i++) {
        const char* t = r->tokens[i].text;

        if (strcmp(t, "(") == 0 || strcmp(t, "{") == 0 || strcmp(t, "[") == 0) {
            depth++;
        } else if (strcmp(t, ")") == 0 || strcmp(t, "}") == 0 || strcmp(t, "]") == 0) {
            if (--depth == 0) {
                return i;
            }
        }
    }
    return r->count;
}

/* Конец объявления: `;` вне скобок. */
static size_t rules_statement_end(const Rules* r, size_t i)
{
    while (i < r->count && !rules_eq(r, i, ";")) {
        if (rules_eq(r, i, "(") || rules_eq(r, i, "{") || rules_eq(r, i, "[")) {
            i = rules_match(r, i);
        }
        i++;
    }
    return i;
}

static void rules_collect_typedefs(Rules* r)
{
    for (size_t i = 0; i < r->count; i++) {
        size_t end = 0;
        size_t name = SIZE_MAX;

        if (!rules_eq(r, i, "typedef")) {
            continue;
        }
        end = rules_statement_end(r, i);
        if (end > 0 && r->tokens[end - 1].word) {
            name = end - 1;
        }
        for (size_t k = i; name == SIZE_MAX && k + 2 < end; k++) {
            if (rules_eq(r, k, "(") && rules_eq(r, k + 1, "*") && r->tokens[k + 2].word) {
                name = k + 2;
            }
        }
        if (name != SIZE_MAX && r->typedef_count < RULES_MAX_TYPEDEFS) {
            strcpy(r->typedefs[r->typedef_count++], r->tokens[name].text);
        }
    }
}

static bool rules_starts_declaration(const Rules* r, size_t i)
{
    static const char* const words[] = { "typedef", "struct", "union", "enum", NULL };

    return i < r->count && r->tokens[i].word
        && (rules_in(r->tokens[i].text, words) || rules_type_word(r, r->tokens[i].text));
}

static void rules_add_function(Rules* r, size_t begin, size_t name, size_t open, size_t body)
{
    RulesFunction f = { name, open, rules_match(r, open), body, rules_match(r, body), false };
    bool const_seen = false;

    for (size_t k = begin; k < name; k++) {
        const_seen = const_seen || rules_eq(r, k, "const");
        if (rules_eq(r, k, "*") && !const_seen) {
            f.returns_mutable_pointer = true;
        }
    }
    if (r->function_count < RULES_MAX_FUNCTIONS) {
        r->functions[r->function_count++] = f;
    }
}

/* Разбирает объявление с tokens[i]. Возвращает индекс `;` или `{` тела функции. */
static size_t rules_declaration(Rules* r, size_t i)
{
    size_t begin = i;
    bool is_extern = false;

    if (rules_eq(r, i, "typedef")) {
        return rules_statement_end(r, i);
    }
    while (i < r->count) {
        if (rules_eq(r, i, "struct") || rules_eq(r, i, "union") || rules_eq(r, i, "enum")) {
            i++;
            if (i < r->count && r->tokens[i].word) {
                i++;
            }
            if (rules_eq(r, i, "{")) {
                i = rules_match(r, i) + 1;
            }
        } else if (r->tokens[i].word && rules_type_word(r, r->tokens[i].text)) {
            is_extern = is_extern || rules_eq(r, i, "extern");
            i++;
        } else {
            break;
        }
    }

    for (;;) {
        size_t name = SIZE_MAX;
        size_t params = SIZE_MAX;
        bool initialized = false;
        int depth = 0;

        while (i < r->count) {
            const char* t = r->tokens[i].text;

            if (depth == 0 && (strcmp(t, ";") == 0 || strcmp(t, ",") == 0)) {
                break;
            }
            if (depth == 0 && strcmp(t, "{") == 0 && !initialized) {
                break;
            }
            if (strcmp(t, "(") == 0 || strcmp(t, "{") == 0 || strcmp(t, "[") == 0) {
                if (depth == 0 && !initialized && strcmp(t, "(") == 0 && name != SIZE_MAX && name + 1 == i) {
                    params = i;
                }
                depth++;
            } else if (strcmp(t, ")") == 0 || strcmp(t, "}") == 0 || strcmp(t, "]") == 0) {
                depth--;
            } else if (depth == 0 && strcmp(t, "=") == 0) {
                initialized = true;
            } else if (!initialized && name == SIZE_MAX && r->tokens[i].word && !rules_type_word(r, t)) {
                name = i;
            }
            i++;
        }

        if (name != SIZE_MAX && params != SIZE_MAX) {
            if (rules_eq(r, i, "{")) {
                rules_add_function(r, begin, name, params, i);
                return i;
            }
        } else if (name != SIZE_MAX && !initialized && !is_extern) {
            rules_error(r, r->tokens[name].line, "переменная `%s` объявлена без инициализации", r->tokens[name].text);
        }
        if (!rules_eq(r, i, ",")) {
            return i;
        }
        i++;
    }
}

static void rules_scan_declarations(Rules* r)
{
    bool statement_start = true;
    size_t i = 0;

    while (i < r->count) {
        if (statement_start && rules_starts_declaration(r, i)) {
            i = rules_declaration(r, i);
            statement_start = false;
            continue;
        }
        statement_start = rules_eq(r, i, ";") || rules_eq(r, i, "{") || rules_eq(r, i, "}")
            || (rules_eq(r, i, "(") && i > 0 && rules_eq(r, i - 1, "for"));
        i++;
    }
}

/* Параметр из токенов [from, to): указатель на const, просто указатель или другое. */
static int rules_param_kind(const Rules* r, size_t from, size_t to, size_t* name)
{
    int stars = 0;
    bool const_before_star = false;
    bool other = false;

    *name = SIZE_MAX;
    for (size_t k = from; k < to; k++) {
        const char* t = r->tokens[k].text;

        if (strcmp(t, "*") == 0) {
            stars++;
        } else if (strcmp(t, "const") == 0 && stars == 0) {
            const_before_star = true;
        } else if (strcmp(t, "(") == 0 || strcmp(t, "FILE") == 0) {
            other = true;
        } else if (r->tokens[k].word && !rules_type_word(r, t)) {
            *name = k;
        }
    }
    if (other || stars != 1 || *name == SIZE_MAX) {
        return RULES_PARAM_OTHER;
    }
    return const_before_star ? RULES_PARAM_CONST_POINTER : RULES_PARAM_MUTABLE_POINTER;
}

/* Вид параметра номер index у функции из этого файла с именем name. */
static int rules_callee_param(const Rules* r, const char* name, size_t index)
{
    for (size_t f = 0; f < r->function_count; f++) {
        const RulesFunction* fn = &r->functions[f];
        size_t from = fn->open + 1;
        size_t current = 0;

        if (strcmp(r->tokens[fn->name].text, name) != 0) {
            continue;
        }
        for (size_t k = from; k <= fn->close; k++) {
            if (k == fn->close || rules_eq(r, k, ",")) {
                size_t param = 0;

                if (current == index) {
                    return rules_param_kind(r, from, k, &param);
                }
                current++;
                from = k + 1;
            } else if (rules_eq(r, k, "(")) {
                k = rules_match(r, k);
            }
        }
    }
    return RULES_PARAM_MUTABLE_POINTER;
}

/* `*` в позиции i — разыменование, а не умножение. */
static bool rules_unary_star(const Rules* r, size_t i)
{
    static const char* const keywords[] = { "return", "sizeof", "case", "else", "do", NULL };
    const RulesToken* prev = i > 0 ? &r->tokens[i - 1] : NULL;

    if (prev == NULL) {
        return true;
    }
    if (prev->word) {
        return rules_in(prev->text, keywords);
    }
    return !isdigit((unsigned char)prev->text[0]) && strcmp(prev->text, ")") != 0
        && strcmp(prev->text, "]") != 0;
}

/* Переменная слева от `=` объявлена в функции как указатель на const. */
static bool rules_const_variable(const Rules* r, const RulesFunction* fn, size_t eq)
{
    if (eq == 0 || !r->tokens[eq - 1].word) {
        return false;
    }
    for (size_t m = fn->open + 1; m < fn->end; m++) {
        if (strcmp(r->tokens[m].text, r->tokens[eq - 1].text) != 0 || !rules_eq(r, m - 1, "*")) {
            continue;
        }
        for (size_t k = m - 1; k > fn->open; k--) {
            const char* t = r->tokens[k - 1].text;

            if (strcmp(t, "const") == 0) {
                return true;
            }
            if (strcmp(t, ";") == 0 || strcmp(t, "{") == 0 || strcmp(t, "}") == 0
                || strcmp(t, "(") == 0 || strcmp(t, ",") == 0) {
                break;
            }
        }
    }
    return false;
}

/* tokens[j] — аргумент вызова: функция может писать по нему. */
static bool rules_passed_to_writer(const Rules* r, size_t j)
{
    static const char* const keywords[] = { "if", "while", "for", "switch", "return", "sizeof", NULL };
    size_t index = 0;
    int depth = 0;

    for (size_t k = j; k-- > 0;) {
        const char* t = r->tokens[k].text;

        if (strcmp(t, ")") == 0 || strcmp(t, "}") == 0) {
            depth++;
        } else if (strcmp(t, "(") == 0 || strcmp(t, "{") == 0) {
            if (depth-- > 0) {
                continue;
            }
            if (strcmp(t, "(") != 0 || k == 0 || !r->tokens[k - 1].word || rules_in(r->tokens[k - 1].text, keywords)) {
                return false;
            }
            return rules_callee_param(r, r->tokens[k - 1].text, index) != RULES_PARAM_CONST_POINTER;
        } else if (depth == 0 && strcmp(t, ",") == 0) {
            index++;
        } else if (depth == 0 && strcmp(t, ";") == 0) {
            return false;
        }
    }
    return false;
}

/* Пишет ли функция по указателю name (или отдаёт его туда, где могут писать). */
static bool rules_writes_through(const Rules* r, const RulesFunction* fn, const char* name)
{
    for (size_t j = fn->body + 1; j < fn->end; j++) {
        size_t k = j + 1;
        bool deref = false;
        bool member = false;

        if (strcmp(r->tokens[j].text, name) != 0 || rules_eq(r, j - 1, ".") || rules_eq(r, j - 1, "->")) {
            continue;
        }
        deref = rules_eq(r, j - 1, "*") && rules_unary_star(r, j - 1);
        if (deref) {
            if (j >= 2 && (rules_eq(r, j - 2, "++") || rules_eq(r, j - 2, "--"))) {
                return true;
            }
            while (rules_eq(r, k, ")")) {
                k++;
            }
        }
        while ((rules_eq(r, k, "->") || rules_eq(r, k, ".")) && k + 1 < fn->end && r->tokens[k + 1].word) {
            k += 2;
            member = true;
        }
        if (member || deref) {
            if (rules_assign_op(r, k) || rules_eq(r, k, "++") || rules_eq(r, k, "--")) {
                return true;
            }
            if (!deref && (rules_eq(r, j - 1, "++") || rules_eq(r, j - 1, "--") || rules_eq(r, j - 1, "&"))) {
                return true;
            }
            continue;
        }
        if (rules_eq(r, j - 1, "return")) {
            if (fn->returns_mutable_pointer) {
                return true;
            }
        } else if (rules_eq(r, j - 1, "=")) {
            if (!rules_const_variable(r, fn, j - 1)) {
                return true;
            }
        } else if (rules_eq(r, j - 1, "(") || rules_eq(r, j - 1, ",")) {
            if (rules_passed_to_writer(r, j)) {
                return true;
            }
        }
    }
    return false;
}

static void rules_check_const_params(Rules* r)
{
    for (size_t f = 0; f < r->function_count; f++) {
        const RulesFunction* fn = &r->functions[f];
        size_t from = fn->open + 1;

        for (size_t k = from; k <= fn->close; k++) {
            if (k == fn->close || rules_eq(r, k, ",")) {
                size_t name = SIZE_MAX;

                if (rules_param_kind(r, from, k, &name) == RULES_PARAM_MUTABLE_POINTER
                    && !rules_writes_through(r, fn, r->tokens[name].text)) {
                    rules_error(r, r->tokens[name].line,
                        "параметр `%s` только читается — объяви его как указатель на const", r->tokens[name].text);
                }
                from = k + 1;
            } else if (rules_eq(r, k, "(")) {
                k = rules_match(r, k);
            }
        }
    }
}

static void rules_check_format(Rules* r)
{
    char command[1024] = "";

    if (system("command -v clang-format >/dev/null 2>&1") != 0) {
        fputs("clang-format не найден, форматирование не проверить.\n"
              "Установи: sudo apt install clang-format\n",
            stderr);
        r->errors++;
        return;
    }
    snprintf(command, sizeof(command), "clang-format --dry-run -Werror '%s'", r->path);
    if (system(command) != 0) {
        fprintf(stderr, "%s: код не отформатирован в стиле WebKit — запусти make format\n", r->path);
        r->errors++;
    }
}

static char* rules_read_file(const char* path)
{
    FILE* file = fopen(path, "rb");
    char* text = NULL;
    long size = 0;

    if (file == NULL) {
        return NULL;
    }
    if (fseek(file, 0, SEEK_END) == 0 && (size = ftell(file)) >= 0 && fseek(file, 0, SEEK_SET) == 0) {
        text = malloc((size_t)size + 1);
        if (text != NULL && fread(text, 1, (size_t)size, file) == (size_t)size) {
            text[size] = '\0';
        } else {
            free(text);
            text = NULL;
        }
    }
    fclose(file);
    return text;
}

/* Проверяет решение, которое лежит в exercises/ по тому же пути, что и тест. */
static void rules_check_solution(const char* test_path)
{
    char path[512] = "";
    const char* tail = strstr(test_path, "tests/");
    Rules r = { 0 };
    char* text = NULL;

    snprintf(path, sizeof(path), "exercises/%s", tail != NULL ? tail + strlen("tests/") : test_path);
    r.path = path;
    text = rules_read_file(path);
    if (text == NULL) {
        fprintf(stderr, "rules: не прочитать %s (тесты запускаются из корня репозитория)\n", path);
        exit(1);
    }

    rules_tokenize(&r, text);
    rules_collect_typedefs(&r);
    rules_scan_declarations(&r);
    rules_check_const_params(&r);
    rules_check_format(&r);

    free(text);
    free(r.tokens);
    if (r.errors > 0) {
        fprintf(stderr, "\nНарушений правил: %d. На контрольной за такое решение — 0 баллов.\n", r.errors);
        exit(1);
    }
}

#define CHECK_RULES() rules_check_solution(__FILE__)
