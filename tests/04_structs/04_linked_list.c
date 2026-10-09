/* Тесты к exercises/04_structs/04_linked_list.c. Запуск: make test 4 4 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/04_structs/04_linked_list.c"
#undef main

/* Строит список, в котором значения идут в том же порядке, что и в массиве. */
static Node* list_from(const int* values, size_t count)
{
    Node* head = NULL;

    for (size_t i = count; i > 0; i--) {
        head = list_push_front(head, values[i - 1]);
        assert(head != NULL);
    }
    return head;
}

static int list_equals(const Node* head, const int* expected, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        if (head == NULL || head->value != expected[i]) {
            return 0;
        }
        head = head->next;
    }
    return head == NULL;
}

static void test_push_front(void)
{
    const int expected[] = { 3, 2, 1 };
    Node* list = NULL;

    list = list_push_front(list, 1);
    assert(list != NULL);
    assert(list->value == 1);
    assert(list->next == NULL);

    list = list_push_front(list, 2);
    list = list_push_front(list, 3);

    assert(list_equals(list, expected, 3));

    list_free(list);
}

static void test_length(void)
{
    const int values[] = { 4, 5, 6, 7 };
    Node* list = list_from(values, 4);

    assert(list_length(NULL) == 0);
    assert(list_length(list) == 4);
    assert(list_length(list->next) == 3);

    list_free(list);
}

static void test_reverse(void)
{
    const int values[] = { 1, 2, 3, 4 };
    const int expected[] = { 4, 3, 2, 1 };
    Node* list = list_from(values, 4);

    list = list_reverse(list);
    assert(list_equals(list, expected, 4));

    list = list_reverse(list);
    assert(list_equals(list, values, 4));

    list_free(list);
}

static void test_reverse_moves_nodes_not_values(void)
{
    const int values[] = { 1, 2, 3 };
    Node* list = list_from(values, 3);
    Node* first = list;
    Node* last = list->next->next;

    list = list_reverse(list);

    assert(list == last);
    assert(list->next->next == first);
    assert(first->value == 1);
    assert(first->next == NULL);

    list_free(list);
}

static void test_reverse_short_lists(void)
{
    const int values[] = { 9 };
    Node* list = list_from(values, 1);

    assert(list_reverse(NULL) == NULL);

    list = list_reverse(list);
    assert(list_equals(list, values, 1));

    list_free(list);
}

static void test_remove_middle(void)
{
    const int values[] = { 1, 2, 3, 4 };
    const int expected[] = { 1, 2, 4 };
    Node* list = list_from(values, 4);
    Node* head = list;

    list = list_remove(list, 3);

    assert(list == head);
    assert(list_equals(list, expected, 3));

    list_free(list);
}

static void test_remove_first_and_last(void)
{
    const int values[] = { 1, 2, 3 };
    const int without_first[] = { 2, 3 };
    const int without_last[] = { 2 };
    Node* list = list_from(values, 3);

    list = list_remove(list, 1);
    assert(list_equals(list, without_first, 2));

    list = list_remove(list, 3);
    assert(list_equals(list, without_last, 1));

    list = list_remove(list, 2);
    assert(list == NULL);
}

static void test_remove_only_first_match(void)
{
    const int values[] = { 5, 7, 5, 7 };
    const int expected[] = { 5, 5, 7 };
    Node* list = list_from(values, 4);

    list = list_remove(list, 7);
    assert(list_equals(list, expected, 3));

    list_free(list);
}

static void test_remove_missing_value(void)
{
    const int values[] = { 1, 2, 3 };
    Node* list = list_from(values, 3);

    list = list_remove(list, 42);
    assert(list_equals(list, values, 3));

    assert(list_remove(NULL, 42) == NULL);

    list_free(list);
}

static void test_free_empty_list(void)
{
    list_free(NULL);
}

int main(void)
{
    test_push_front();
    test_length();
    test_reverse();
    test_reverse_moves_nodes_not_values();
    test_reverse_short_lists();
    test_remove_middle();
    test_remove_first_and_last();
    test_remove_only_first_match();
    test_remove_missing_value();
    test_free_empty_list();

    puts("All tests passed");
    return 0;
}
