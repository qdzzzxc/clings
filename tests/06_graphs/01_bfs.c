/* Тесты к exercises/06_graphs/01_bfs.c. Запуск: make test 6 1 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/06_graphs/01_bfs.c"
#undef main

static void test_chain(void)
{
    Graph graph;

    graph_init(&graph, 5);
    graph_add_edge(&graph, 0, 1);
    graph_add_edge(&graph, 1, 2);
    graph_add_edge(&graph, 2, 3);
    graph_add_edge(&graph, 3, 4);

    assert(bfs_distance(&graph, 0, 1) == 1);
    assert(bfs_distance(&graph, 0, 4) == 4);
    assert(bfs_distance(&graph, 4, 0) == 4);
    assert(bfs_distance(&graph, 1, 3) == 2);
}

static void test_distance_to_itself(void)
{
    Graph graph;

    graph_init(&graph, 3);
    graph_add_edge(&graph, 0, 1);

    assert(bfs_distance(&graph, 0, 0) == 0);
    assert(bfs_distance(&graph, 2, 2) == 0);
}

static void test_unreachable(void)
{
    Graph graph;

    graph_init(&graph, 4);
    graph_add_edge(&graph, 0, 1);
    graph_add_edge(&graph, 2, 3);

    assert(bfs_distance(&graph, 0, 2) == -1);
    assert(bfs_distance(&graph, 3, 1) == -1);
    assert(bfs_distance(&graph, 2, 3) == 1);
}

static void test_shortest_of_two_paths(void)
{
    Graph graph;

    /* Из 0 в 5 есть длинный путь 0-1-2-3-4-5 и короткий 0-6-5. */
    graph_init(&graph, 7);
    graph_add_edge(&graph, 0, 1);
    graph_add_edge(&graph, 1, 2);
    graph_add_edge(&graph, 2, 3);
    graph_add_edge(&graph, 3, 4);
    graph_add_edge(&graph, 4, 5);
    graph_add_edge(&graph, 0, 6);
    graph_add_edge(&graph, 6, 5);

    assert(bfs_distance(&graph, 0, 5) == 2);
    assert(bfs_distance(&graph, 0, 3) == 3);
    assert(bfs_distance(&graph, 6, 2) == 3);
}

static void test_cycle(void)
{
    Graph graph;

    /* Кольцо из шести вершин. */
    graph_init(&graph, 6);
    for (size_t vertex = 0; vertex < 6; vertex++) {
        graph_add_edge(&graph, vertex, (vertex + 1) % 6);
    }

    assert(bfs_distance(&graph, 0, 3) == 3);
    assert(bfs_distance(&graph, 0, 4) == 2);
    assert(bfs_distance(&graph, 0, 5) == 1);
}

static void test_full_graph_fits_in_the_queue(void)
{
    Graph graph;

    /* Каждая вершина — сосед каждой: в очередь нельзя класть вершину дважды. */
    graph_init(&graph, MAX_VERTICES);
    for (size_t a = 0; a < MAX_VERTICES; a++) {
        for (size_t b = a + 1; b < MAX_VERTICES; b++) {
            graph_add_edge(&graph, a, b);
        }
    }

    assert(bfs_distance(&graph, 0, MAX_VERTICES - 1) == 1);
    assert(bfs_distance(&graph, 5, 5) == 0);
    assert(count_components(&graph) == 1);
}

static void test_components(void)
{
    Graph graph;

    /* Цепочка 0-1-2, ребро 3-4 и одинокая вершина 5. */
    graph_init(&graph, 6);
    graph_add_edge(&graph, 0, 1);
    graph_add_edge(&graph, 1, 2);
    graph_add_edge(&graph, 3, 4);

    assert(count_components(&graph) == 3);

    graph_add_edge(&graph, 2, 3);
    assert(count_components(&graph) == 2);

    graph_add_edge(&graph, 5, 0);
    assert(count_components(&graph) == 1);
}

static void test_components_without_edges(void)
{
    Graph graph;

    graph_init(&graph, 7);
    assert(count_components(&graph) == 7);

    graph_init(&graph, 1);
    assert(count_components(&graph) == 1);

    graph_init(&graph, 0);
    assert(count_components(&graph) == 0);
}

static void test_components_numbered_out_of_order(void)
{
    Graph graph;

    /* Компоненты {0, 4, 2} и {1, 3}: соседи идут не подряд. */
    graph_init(&graph, 5);
    graph_add_edge(&graph, 0, 4);
    graph_add_edge(&graph, 4, 2);
    graph_add_edge(&graph, 3, 1);

    assert(count_components(&graph) == 2);
}

int main(void)
{
    test_chain();
    test_distance_to_itself();
    test_unreachable();
    test_shortest_of_two_paths();
    test_cycle();
    test_full_graph_fits_in_the_queue();
    test_components();
    test_components_without_edges();
    test_components_numbered_out_of_order();

    puts("All tests passed");
    return 0;
}
