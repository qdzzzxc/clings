/*
# Task 3 — Dijkstra

У рёбер появляется вес: длина дороги, время, цена. Кратчайший путь —
теперь путь с наименьшей суммой весов, и рёбер в нём может быть больше,
чем в другом пути. BFS здесь уже не годится.

Алгоритм Дейкстры хранит для каждой вершины лучшее известное расстояние
от старта. На каждом шаге он берёт ещё не обработанную вершину
с наименьшим расстоянием — оно уже окончательное — и пробует улучшить
расстояния до её соседей.

Тип `WeightedGraph` и функции `wgraph_init` и `wgraph_add_edge` уже
готовы. Граф неориентированный, `weight[a][b] == 0` означает,
что ребра нет. Все веса положительные.

## Нужно реализовать функцию

shortest_path:
    Возвращает длину кратчайшего пути из `from` в `to`.
    Если пути нет — возвращает -1. Путь из вершины в неё саму равен 0.

## Requirements

- Ближайшую необработанную вершину искать простым проходом по массиву:
  для графа из 16 вершин этого достаточно.
- «Бесконечное» расстояние должно быть таким, чтобы прибавление
  веса ребра его не переполняло (или не прибавлять к нему вовсе).
- Гарантируется, что `from` и `to` — существующие вершины.

## Interface

long shortest_path(const WeightedGraph *graph, size_t from, size_t to);
*/

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAX_VERTICES 16

typedef struct {
    size_t vertex_count;
    int weight[MAX_VERTICES][MAX_VERTICES];
} WeightedGraph;

void wgraph_init(WeightedGraph* graph, size_t vertex_count)
{
    graph->vertex_count = vertex_count;
    memset(graph->weight, 0, sizeof(graph->weight));
}

void wgraph_add_edge(WeightedGraph* graph, size_t a, size_t b, int weight)
{
    graph->weight[a][b] = weight;
    graph->weight[b][a] = weight;
}

long shortest_path(const WeightedGraph* graph, size_t from, size_t to)
{
    /* TODO: реализуйте shortest_path. */
    (void)graph;
    (void)from;
    (void)to;
    assert(!"TODO: shortest_path");
    return 0;
}

int main(void)
{
    WeightedGraph graph;

    /* Прямая дорога 0-3 длиной 10 и объезд 0-1-2-3 длиной 2 + 3 + 1. */
    wgraph_init(&graph, 4);
    wgraph_add_edge(&graph, 0, 3, 10);
    wgraph_add_edge(&graph, 0, 1, 2);
    wgraph_add_edge(&graph, 1, 2, 3);
    wgraph_add_edge(&graph, 2, 3, 1);

    printf("0 -> 3: %ld\n", shortest_path(&graph, 0, 3));
    return 0;
}
