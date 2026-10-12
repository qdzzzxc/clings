/*
# Task 4 — Loop in a list

Дан односвязный список: узел хранит значение и указатель на следующий
узел, у последнего узла next == NULL. Но список может быть испорчен:
next какого-то узла указывает на один из предыдущих узлов (или на себя),
и тогда список зацикливается и конца у него нет.

Вернуть true, если в списке есть цикл, и false, если список
заканчивается NULL. Пустой список (head == NULL) — без цикла.

## Example

1 -> 2 -> 3 -> NULL             ->  false
1 -> 2 -> 3 -> (снова 2)        ->  true
1 -> (снова 1)                  ->  true

## Requirements

- Массивы и динамическая память запрещены: запоминать пройденные узлы
  нельзя, нужна O(1) дополнительной памяти. Подсказка: два указателя,
  один шагает по одному узлу, другой — через узел. Если цикл есть,
  быстрый догонит медленного.
- Список менять нельзя — поэтому head указывает на const.
- Структура Node и getNext уже даны, их не менять.
- Лимит времени — 1 секунда на список из миллиона узлов.

## Interface

bool hasLoop(const Node* head);
*/

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

const Node* getNext(const Node* node)
{
    return node == NULL ? NULL : node->next;
}

bool hasLoop(const Node* head)
{
    /* TODO: реализуйте hasLoop. */
    (void)head;
    assert(!"TODO: hasLoop");
    return false;
}

int main(void)
{
    Node third = { 3, NULL };
    Node second = { 2, &third };
    Node first = { 1, &second };

    printf("1 -> 2 -> 3: %s\n", hasLoop(&first) ? "loop" : "no loop");
    third.next = &second;
    printf("1 -> 2 -> 3 -> 2: %s\n", hasLoop(&first) ? "loop" : "no loop");
    return 0;
}
