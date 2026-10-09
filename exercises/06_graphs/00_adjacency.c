/*
# Task 0 — Adjacency matrix

Граф — это вершины и рёбра между ними. Вершины пронумерованы с нуля.
Самый простой способ хранить граф — матрица смежности:
`adjacent[a][b] == 1`, если между вершинами `a` и `b` есть ребро.

Граф здесь неориентированный: ребро a—b и ребро b—a — одно и то же.

## Нужно реализовать функции

graph_init:
    Делает граф с `vertex_count` вершинами и без рёбер.
    Если вершин больше `MAX_VERTICES` — возвращает 0.

graph_add_edge:
    Добавляет ребро между `a` и `b`. Возвращает 0, если номер вершины
    вне графа или `a == b` (петли запрещены). Повторное добавление
    того же ребра — успех, граф при этом не меняется.

graph_has_edge:
    Возвращает 1, если ребро есть. Для номеров вне графа возвращает 0.

graph_degree:
    Степень вершины — количество рёбер, которые из неё выходят.

graph_edge_count:
    Количество рёбер в графе. Ребро a—b считается один раз.

## Requirements

- Матрица должна оставаться симметричной.
- Не читать и не писать за пределами матрицы: номера вершин
  проверять до обращения к ней.

## Interfaces

#define MAX_VERTICES 16

typedef struct {
    size_t vertex_count;
    int adjacent[MAX_VERTICES][MAX_VERTICES];
} Graph;

int graph_init(Graph *graph, size_t vertex_count);
int graph_add_edge(Graph *graph, size_t a, size_t b);
int graph_has_edge(const Graph *graph, size_t a, size_t b);
size_t graph_degree(const Graph *graph, size_t vertex);
size_t graph_edge_count(const Graph *graph);

Возвращаемое значение `graph_init` и `graph_add_edge`:

1 — успех
0 — ошибка
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

int graph_init(Graph* graph, size_t vertex_count)
{
    /* TODO: реализуйте graph_init. */
    (void)graph;
    (void)vertex_count;
    assert(!"TODO: graph_init");
    return 0;
}

int graph_add_edge(Graph* graph, size_t a, size_t b)
{
    /* TODO: реализуйте graph_add_edge. */
    (void)graph;
    (void)a;
    (void)b;
    assert(!"TODO: graph_add_edge");
    return 0;
}

int graph_has_edge(const Graph* graph, size_t a, size_t b)
{
    /* TODO: реализуйте graph_has_edge. */
    (void)graph;
    (void)a;
    (void)b;
    assert(!"TODO: graph_has_edge");
    return 0;
}

size_t graph_degree(const Graph* graph, size_t vertex)
{
    /* TODO: реализуйте graph_degree. */
    (void)graph;
    (void)vertex;
    assert(!"TODO: graph_degree");
    return 0;
}

size_t graph_edge_count(const Graph* graph)
{
    /* TODO: реализуйте graph_edge_count. */
    (void)graph;
    assert(!"TODO: graph_edge_count");
    return 0;
}

int main(void)
{
    Graph graph;

    /* Треугольник 0-1-2 и вершина 3, соединённая только с вершиной 0. */
    graph_init(&graph, 4);
    graph_add_edge(&graph, 0, 1);
    graph_add_edge(&graph, 1, 2);
    graph_add_edge(&graph, 2, 0);
    graph_add_edge(&graph, 0, 3);

    printf("edges: %zu\n", graph_edge_count(&graph));
    for (size_t vertex = 0; vertex < 4; vertex++) {
        printf("degree of %zu: %zu\n", vertex, graph_degree(&graph, vertex));
    }
    return 0;
}
