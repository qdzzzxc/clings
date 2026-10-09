/*
# Task 4 — Linked list

Односвязный список: каждый узел лежит в динамической памяти и хранит
значение и указатель на следующий узел. Пустой список — это NULL.

## Нужно реализовать функции

list_push_front:
    Создаёт узел и ставит его в начало списка. Возвращает новую голову.
    Если `malloc` вернул NULL — возвращает NULL, список не меняется.

list_length:
    Количество узлов.

list_reverse:
    Разворачивает список и возвращает новую голову.

list_remove:
    Удаляет первый узел со значением `value` и освобождает его память.
    Возвращает голову списка (она меняется, если удалён первый узел).
    Если такого значения нет — список не меняется.

list_free:
    Освобождает все узлы.

## Requirements

- `list_reverse` не выделяет память и не меняет значения в узлах:
  переставляются только указатели `next`.
- После `free(node)` к полям узла обращаться нельзя: в `list_free`
  указатель на следующий узел нужно запомнить заранее.
- Утечки памяти тесты считают ошибкой.

## Interfaces

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *list_push_front(Node *head, int value);
size_t list_length(const Node *head);
Node *list_reverse(Node *head);
Node *list_remove(Node *head, int value);
void list_free(Node *head);
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* list_push_front(Node* head, int value)
{
    /* TODO: реализуйте list_push_front. */
    (void)head;
    (void)value;
    assert(!"TODO: list_push_front");
    return NULL;
}

size_t list_length(const Node* head)
{
    /* TODO: реализуйте list_length. */
    (void)head;
    assert(!"TODO: list_length");
    return 0;
}

Node* list_reverse(Node* head)
{
    /* TODO: реализуйте list_reverse. */
    (void)head;
    assert(!"TODO: list_reverse");
    return NULL;
}

Node* list_remove(Node* head, int value)
{
    /* TODO: реализуйте list_remove. */
    (void)head;
    (void)value;
    assert(!"TODO: list_remove");
    return NULL;
}

void list_free(Node* head)
{
    /* TODO: реализуйте list_free. */
    (void)head;
    assert(!"TODO: list_free");
}

int main(void)
{
    Node* list = NULL;

    for (int value = 1; value <= 5; value++) {
        Node* head = list_push_front(list, value);

        if (head == NULL) {
            list_free(list);
            return 1;
        }
        list = head;
    }

    list = list_reverse(list);
    list = list_remove(list, 3);

    for (const Node* node = list; node != NULL; node = node->next) {
        printf("%d ", node->value);
    }
    printf("\nlength: %zu\n", list_length(list));

    list_free(list);
    return 0;
}
