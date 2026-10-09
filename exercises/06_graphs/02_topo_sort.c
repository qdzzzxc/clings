/*
# Task 2 — Depth-first search

Обход в глубину (DFS) идёт по графу «до упора»: из вершины переходит
к первому непосещённому соседу, из него — дальше, и возвращается назад,
только когда идти некуда. Проще всего его написать рекурсией.

Граф здесь ориентированный: дуга a -> b не означает, что есть дуга b -> a.
Так описывают зависимости: «a нужно сделать раньше, чем b».

Тип `Graph` и функции `graph_init` и `graph_add_arc` уже готовы.

## Нужно реализовать функции

has_cycle:
    Возвращает 1, если в графе есть цикл: путь по дугам, который
    возвращается в ту же вершину.

topo_sort:
    Топологическая сортировка: записывает в `order` все вершины в таком
    порядке, что для каждой дуги a -> b вершина `a` стоит раньше `b`.
    Если таких порядков несколько, подойдёт любой.
    Если в графе есть цикл, порядка не существует — вернуть 0.

## Requirements

- Обе функции построить на DFS с тремя состояниями вершины:
  не посещена, в обработке (мы сейчас внутри неё или её потомков),
  полностью обработана.
- Цикл найден, когда DFS встречает вершину в состоянии «в обработке».
- В топологическом порядке вершины идут в порядке, обратном тому,
  в котором DFS заканчивает их обработку.
- `order` — массив минимум из `vertex_count` элементов.

## Interfaces

int has_cycle(const Graph *graph);
int topo_sort(const Graph *graph, size_t *order);

Возвращаемое значение `topo_sort`:

1 — порядок построен
0 — в графе есть цикл
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAX_VERTICES 16

typedef struct {
    size_t vertex_count;
    int adjacent[MAX_VERTICES][MAX_VERTICES];
} Graph;

void graph_init(Graph* graph, size_t vertex_count)
{
    graph->vertex_count = vertex_count;
    memset(graph->adjacent, 0, sizeof(graph->adjacent));
}

/* Добавляет дугу from -> to. */
void graph_add_arc(Graph* graph, size_t from, size_t to)
{
    graph->adjacent[from][to] = 1;
}

int topo_sort(const Graph* graph, size_t* order)
{
    /* TODO: реализуйте topo_sort. */
    (void)graph;
    (void)order;
    assert(!"TODO: topo_sort");
    return 0;
}

int has_cycle(const Graph* graph)
{
    /* TODO: реализуйте has_cycle. */
    (void)graph;
    assert(!"TODO: has_cycle");
    return 0;
}

int main(void)
{
    const char* names[] = { "socks", "shoes", "trousers", "shirt", "jacket" };
    size_t order[5];
    Graph graph;

    graph_init(&graph, 5);
    graph_add_arc(&graph, 0, 1);
    graph_add_arc(&graph, 2, 1);
    graph_add_arc(&graph, 3, 4);
    graph_add_arc(&graph, 2, 4);

    if (!topo_sort(&graph, order)) {
        printf("cycle\n");
        return 1;
    }

    for (size_t i = 0; i < 5; i++) {
        printf("%s\n", names[order[i]]);
    }
    return 0;
}
