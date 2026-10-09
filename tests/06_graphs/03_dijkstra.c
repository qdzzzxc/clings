/* Тесты к exercises/06_graphs/03_dijkstra.c. Запуск: make test 6 3 */

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/06_graphs/03_dijkstra.c"
#undef main

static void test_single_edge(void)
{
    WeightedGraph graph;

    wgraph_init(&graph, 2);
    wgraph_add_edge(&graph, 0, 1, 7);

    assert(shortest_path(&graph, 0, 1) == 7);
    assert(shortest_path(&graph, 1, 0) == 7);
}

static void test_path_to_itself(void)
{
    WeightedGraph graph;

    wgraph_init(&graph, 3);
    wgraph_add_edge(&graph, 0, 1, 7);

    assert(shortest_path(&graph, 0, 0) == 0);
    assert(shortest_path(&graph, 2, 2) == 0);
}

static void test_unreachable(void)
{
    WeightedGraph graph;

    wgraph_init(&graph, 4);
    wgraph_add_edge(&graph, 0, 1, 1);
    wgraph_add_edge(&graph, 2, 3, 1);

    assert(shortest_path(&graph, 0, 3) == -1);
    assert(shortest_path(&graph, 2, 1) == -1);
}

static void test_more_edges_but_shorter(void)
{
    WeightedGraph graph;

    /* Прямая дорога 0-3 длиной 10 и объезд 0-1-2-3 длиной 2 + 3 + 1. */
    wgraph_init(&graph, 4);
    wgraph_add_edge(&graph, 0, 3, 10);
    wgraph_add_edge(&graph, 0, 1, 2);
    wgraph_add_edge(&graph, 1, 2, 3);
    wgraph_add_edge(&graph, 2, 3, 1);

    assert(shortest_path(&graph, 0, 3) == 6);
    assert(shortest_path(&graph, 3, 0) == 6);
    assert(shortest_path(&graph, 0, 2) == 5);
}

static void test_cheapest_first_step_is_a_trap(void)
{
    WeightedGraph graph;

    /* Из 0 самое дешёвое ребро ведёт в 1, но дальше оттуда дорого. */
    wgraph_init(&graph, 4);
    wgraph_add_edge(&graph, 0, 1, 1);
    wgraph_add_edge(&graph, 1, 3, 100);
    wgraph_add_edge(&graph, 0, 2, 5);
    wgraph_add_edge(&graph, 2, 3, 5);

    assert(shortest_path(&graph, 0, 3) == 10);
}

static void test_distance_is_improved_later(void)
{
    WeightedGraph graph;

    /* Расстояние до 2 сначала 9 (ребро 0-2), потом улучшается до 3 через 1. */
    wgraph_init(&graph, 5);
    wgraph_add_edge(&graph, 0, 2, 9);
    wgraph_add_edge(&graph, 0, 1, 1);
    wgraph_add_edge(&graph, 1, 2, 2);
    wgraph_add_edge(&graph, 2, 3, 4);
    wgraph_add_edge(&graph, 0, 4, 20);
    wgraph_add_edge(&graph, 3, 4, 1);

    assert(shortest_path(&graph, 0, 2) == 3);
    assert(shortest_path(&graph, 0, 3) == 7);
    assert(shortest_path(&graph, 0, 4) == 8);
    assert(shortest_path(&graph, 4, 1) == 7);
}

static void test_classic_graph(void)
{
    WeightedGraph graph;

    wgraph_init(&graph, 6);
    wgraph_add_edge(&graph, 0, 1, 7);
    wgraph_add_edge(&graph, 0, 2, 9);
    wgraph_add_edge(&graph, 0, 5, 14);
    wgraph_add_edge(&graph, 1, 2, 10);
    wgraph_add_edge(&graph, 1, 3, 15);
    wgraph_add_edge(&graph, 2, 3, 11);
    wgraph_add_edge(&graph, 2, 5, 2);
    wgraph_add_edge(&graph, 3, 4, 6);
    wgraph_add_edge(&graph, 4, 5, 9);

    assert(shortest_path(&graph, 0, 1) == 7);
    assert(shortest_path(&graph, 0, 2) == 9);
    assert(shortest_path(&graph, 0, 3) == 20);
    assert(shortest_path(&graph, 0, 4) == 20);
    assert(shortest_path(&graph, 0, 5) == 11);
}

static void test_huge_weights(void)
{
    WeightedGraph graph;

    /* Сумма весов не помещается в int, а часть вершин недостижима. */
    wgraph_init(&graph, 5);
    wgraph_add_edge(&graph, 0, 1, INT_MAX);
    wgraph_add_edge(&graph, 1, 2, INT_MAX);
    wgraph_add_edge(&graph, 3, 4, INT_MAX);

    assert(shortest_path(&graph, 0, 2) == 2L * INT_MAX);
    assert(shortest_path(&graph, 0, 4) == -1);
}

static void test_long_chain(void)
{
    WeightedGraph graph;

    wgraph_init(&graph, MAX_VERTICES);
    for (size_t vertex = 0; vertex + 1 < MAX_VERTICES; vertex++) {
        wgraph_add_edge(&graph, vertex, vertex + 1, (int)vertex + 1);
    }

    /* 1 + 2 + ... + 15 */
    assert(shortest_path(&graph, 0, MAX_VERTICES - 1) == 120);
    assert(shortest_path(&graph, MAX_VERTICES - 1, 0) == 120);
}

int main(void)
{
    test_single_edge();
    test_path_to_itself();
    test_unreachable();
    test_more_edges_but_shorter();
    test_cheapest_first_step_is_a_trap();
    test_distance_is_improved_later();
    test_classic_graph();
    test_huge_weights();
    test_long_chain();

    puts("All tests passed");
    return 0;
}
