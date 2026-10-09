/*
# Task 0 — Stack module

До сих пор каждая программа целиком лежала в одном файле. Здесь её нужно
разделить на модуль и программу, которая этим модулем пользуется.

Этот файл уже готов, менять его не нужно. Рядом с ним нужно создать
три файла: `stack.h`, `stack.c` и `Makefile`.

## stack.h — интерфейс модуля

Стек целых чисел фиксированной ёмкости. В заголовке лежат только
определение типа и объявления функций:

#define STACK_CAPACITY 8

typedef struct {
    int items[STACK_CAPACITY];
    size_t size;
} Stack;

void stack_init(Stack *stack);
int stack_push(Stack *stack, int value);
int stack_pop(Stack *stack, int *value);
int stack_peek(const Stack *stack, int *value);
size_t stack_size(const Stack *stack);

- `stack_init` делает стек пустым.
- `stack_push` кладёт значение на вершину. Если стек полон — возвращает 0.
- `stack_pop` снимает значение с вершины и записывает его в `*value`.
  Если стек пуст — возвращает 0 и не меняет `*value`.
- `stack_peek` делает то же, но оставляет значение в стеке.
- При успехе `stack_push`, `stack_pop` и `stack_peek` возвращают 1.

Заголовок должен быть защищён от повторного включения (include guard)
и сам подключать всё, что ему нужно (`size_t` объявлен в `<stddef.h>`).

## stack.c — реализация

Подключает `stack.h` и определяет все пять функций.

## Makefile

- `make` собирает программу `app` из `main.c` и `stack.c`.
- Каждый `.c` сначала компилируется в свой `.o`, затем `.o` линкуются.
- Если изменился `stack.h`, пересобираются оба `.o`.
- `make clean` удаляет `app` и все `.o`.

## Проверка

`make test 5 0` сначала собирает задачу твоим Makefile, затем запускает
тесты модуля. `make run 5 0` собирает и запускает `app`.
*/

#include <stdio.h>

#include "stack.h"

int main(void)
{
    Stack stack;
    int value = 0;

    stack_init(&stack);

    for (int i = 1; i <= 5; i++) {
        if (!stack_push(&stack, i * i)) {
            return 1;
        }
    }

    printf("size: %zu\n", stack_size(&stack));

    while (stack_pop(&stack, &value)) {
        printf("%d\n", value);
    }
    return 0;
}
