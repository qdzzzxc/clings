/*
# Task 1 — Breadth-first search

Обход в ширину (BFS) посещает вершины по мере удаления от стартовой:
сначала саму вершину, потом всех её соседей, потом соседей соседей.
Поэтому он находит кратчайший путь, если длина пути — число рёбер.

Тип `Graph` и функции `graph_init` и `graph_add_edge` уже готовы.
Граф неориентированный.

## Нужно реализовать функции

bfs_distance:
    Возвращает число рёбер в кратчайшем пути из `from` в `to`.
    Если пути нет — возвращает -1. Путь из вершины в неё саму равен 0.

count_components:
    Количество компонент связности: групп вершин, внутри которых
    из любой вершины можно дойти до любой другой.
    Вершина без рёбер — отдельная компонента.

## Requirements

- Очередь для BFS сделать на обычном массиве из `MAX_VERTICES` элементов
  с двумя индексами: откуда брать и куда класть.
- Каждую вершину класть в очередь не больше одного раза: помечать её
  посещённой в момент добавления в очередь.
- Гарантируется, что `from` и `to` — существующие вершины.

## Interfaces

int bfs_distance(const Graph *graph, size_t from, size_t to);
size_t count_components(const Graph *graph);
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

void graph_add_edge(Graph* graph, size_t a, size_t b)
{
    graph->adjacent[a][b] = 1;
    graph->adjacent[b][a] = 1;
}

int bfs_distance(const Graph* graph, size_t from, size_t to)
{
    /* TODO: реализуйте bfs_distance. */
    (void)graph;
    (void)from;
    (void)to;
    assert(!"TODO: bfs_distance");
    return 0;
}

size_t count_components(const Graph* graph)
{
    /* TODO: реализуйте count_components. */
    (void)graph;
    assert(!"TODO: count_components");
    return 0;
}

int main(void)
{
    Graph graph;

    /* Цепочка 0-1-2-3 и отдельное ребро 4-5. */
    graph_init(&graph, 6);
    graph_add_edge(&graph, 0, 1);
    graph_add_edge(&graph, 1, 2);
    graph_add_edge(&graph, 2, 3);
    graph_add_edge(&graph, 4, 5);

    printf("0 -> 3: %d\n", bfs_distance(&graph, 0, 3));
    printf("0 -> 5: %d\n", bfs_distance(&graph, 0, 5));
    printf("components: %zu\n", count_components(&graph));
    return 0;
}
