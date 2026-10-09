/* Тесты к exercises/06_graphs/00_adjacency.c. Запуск: make test 6 0 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/06_graphs/00_adjacency.c"
#undef main

static void test_init(void)
{
    Graph graph;

    /* Мусор в памяти: graph_init обязан всё обнулить. */
    memset(&graph, 0x55, sizeof(graph));

    assert(graph_init(&graph, 5));
    assert(graph.vertex_count == 5);
    assert(graph_edge_count(&graph) == 0);

    for (size_t a = 0; a < 5; a++) {
        assert(graph_degree(&graph, a) == 0);
        for (size_t b = 0; b < 5; b++) {
            assert(!graph_has_edge(&graph, a, b));
        }
    }
}

static void test_init_size_limits(void)
{
    Graph graph;

    assert(graph_init(&graph, 0));
    assert(graph_edge_count(&graph) == 0);

    assert(graph_init(&graph, MAX_VERTICES));
    assert(!graph_init(&graph, MAX_VERTICES + 1));
}

static void test_edges_are_symmetric(void)
{
    Graph graph;

    assert(graph_init(&graph, 4));
    assert(graph_add_edge(&graph, 0, 3));

    assert(graph_has_edge(&graph, 0, 3));
    assert(graph_has_edge(&graph, 3, 0));
    assert(!graph_has_edge(&graph, 0, 1));
    assert(!graph_has_edge(&graph, 0, 0));
}

static void test_bad_edges(void)
{
    Graph graph;

    assert(graph_init(&graph, 4));

    assert(!graph_add_edge(&graph, 0, 4));
    assert(!graph_add_edge(&graph, 4, 0));
    assert(!graph_add_edge(&graph, 100, 200));
    assert(!graph_add_edge(&graph, 2, 2));

    assert(graph_edge_count(&graph) == 0);
    assert(!graph_has_edge(&graph, 0, 4));
    assert(!graph_has_edge(&graph, 4, 0));
    assert(!graph_has_edge(&graph, 2, 2));
}

static void test_vertices_outside_a_small_graph(void)
{
    Graph graph;

    /* Вершина 3 помещается в матрицу, но в графе из трёх вершин её нет. */
    assert(graph_init(&graph, 3));
    assert(!graph_add_edge(&graph, 0, 3));
    assert(!graph_has_edge(&graph, 0, 3));
}

static void test_degree_and_edge_count(void)
{
    Graph graph;

    /* Треугольник 0-1-2 и вершина 3, соединённая только с вершиной 0. */
    assert(graph_init(&graph, 5));
    assert(graph_add_edge(&graph, 0, 1));
    assert(graph_add_edge(&graph, 1, 2));
    assert(graph_add_edge(&graph, 2, 0));
    assert(graph_add_edge(&graph, 0, 3));

    assert(graph_edge_count(&graph) == 4);
    assert(graph_degree(&graph, 0) == 3);
    assert(graph_degree(&graph, 1) == 2);
    assert(graph_degree(&graph, 2) == 2);
    assert(graph_degree(&graph, 3) == 1);
    assert(graph_degree(&graph, 4) == 0);
}

static void test_repeated_edge(void)
{
    Graph graph;

    assert(graph_init(&graph, 3));
    assert(graph_add_edge(&graph, 0, 1));
    assert(graph_add_edge(&graph, 0, 1));
    assert(graph_add_edge(&graph, 1, 0));

    assert(graph_edge_count(&graph) == 1);
    assert(graph_degree(&graph, 0) == 1);
    assert(graph_degree(&graph, 1) == 1);
}

static void test_full_graph(void)
{
    Graph graph;

    assert(graph_init(&graph, MAX_VERTICES));
    for (size_t a = 0; a < MAX_VERTICES; a++) {
        for (size_t b = a + 1; b < MAX_VERTICES; b++) {
            assert(graph_add_edge(&graph, a, b));
        }
    }

    assert(graph_edge_count(&graph) == MAX_VERTICES * (MAX_VERTICES - 1) / 2);
    assert(graph_degree(&graph, 0) == MAX_VERTICES - 1);
    assert(graph_degree(&graph, MAX_VERTICES - 1) == MAX_VERTICES - 1);
}

static void test_init_clears_old_edges(void)
{
    Graph graph;

    assert(graph_init(&graph, 3));
    assert(graph_add_edge(&graph, 0, 1));

    assert(graph_init(&graph, 3));
    assert(!graph_has_edge(&graph, 0, 1));
    assert(graph_edge_count(&graph) == 0);
}

int main(void)
{
    test_init();
    test_init_size_limits();
    test_edges_are_symmetric();
    test_bad_edges();
    test_vertices_outside_a_small_graph();
    test_degree_and_edge_count();
    test_repeated_edge();
    test_full_graph();
    test_init_clears_old_edges();

    puts("All tests passed");
    return 0;
}
