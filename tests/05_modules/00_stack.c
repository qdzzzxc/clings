/* Тесты к exercises/05_modules/00_stack/. Запуск: make test 5 0 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

/* Каждый заголовок подключён дважды: include guard должен это выдержать. */
#include "stack.h"

#include "stack.h"

static void test_new_stack_is_empty(void)
{
    Stack stack;
    int value = 777;

    stack_init(&stack);

    assert(stack_size(&stack) == 0);
    assert(!stack_pop(&stack, &value));
    assert(!stack_peek(&stack, &value));
    assert(value == 777);
}

static void test_push_and_pop(void)
{
    Stack stack;
    int value = 777;

    stack_init(&stack);

    assert(stack_push(&stack, 10));
    assert(stack_push(&stack, 20));
    assert(stack_push(&stack, 30));
    assert(stack_size(&stack) == 3);

    assert(stack_pop(&stack, &value) && value == 30);
    assert(stack_pop(&stack, &value) && value == 20);
    assert(stack_size(&stack) == 1);

    assert(stack_push(&stack, 40));
    assert(stack_pop(&stack, &value) && value == 40);
    assert(stack_pop(&stack, &value) && value == 10);

    assert(stack_size(&stack) == 0);
    assert(!stack_pop(&stack, &value));
    assert(value == 10);
}

static void test_peek_keeps_the_value(void)
{
    Stack stack;
    int value = 777;

    stack_init(&stack);
    assert(stack_push(&stack, 5));
    assert(stack_push(&stack, 6));

    assert(stack_peek(&stack, &value) && value == 6);
    assert(stack_peek(&stack, &value) && value == 6);
    assert(stack_size(&stack) == 2);
}

static void test_full_stack(void)
{
    Stack stack;
    int value = 777;

    stack_init(&stack);

    for (int i = 0; i < STACK_CAPACITY; i++) {
        assert(stack_push(&stack, i));
    }

    assert(stack_size(&stack) == STACK_CAPACITY);
    assert(!stack_push(&stack, 100));
    assert(stack_size(&stack) == STACK_CAPACITY);

    for (int i = STACK_CAPACITY - 1; i >= 0; i--) {
        assert(stack_pop(&stack, &value) && value == i);
    }
}

static void test_init_resets_a_used_stack(void)
{
    Stack stack;

    stack_init(&stack);
    assert(stack_push(&stack, 1));
    assert(stack_push(&stack, 2));

    stack_init(&stack);
    assert(stack_size(&stack) == 0);
}

static void test_two_stacks_are_independent(void)
{
    Stack first;
    Stack second;
    int value = 777;

    stack_init(&first);
    stack_init(&second);

    assert(stack_push(&first, 1));
    assert(stack_push(&second, 2));
    assert(stack_push(&second, 3));

    assert(stack_size(&first) == 1);
    assert(stack_size(&second) == 2);
    assert(stack_pop(&first, &value) && value == 1);
    assert(stack_pop(&second, &value) && value == 3);
}

int main(void)
{
    test_new_stack_is_empty();
    test_push_and_pop();
    test_peek_keeps_the_value();
    test_full_stack();
    test_init_resets_a_used_stack();
    test_two_stacks_are_independent();

    puts("All tests passed");
    return 0;
}
