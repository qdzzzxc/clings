/* Тесты к exercises/06_graphs/02_topo_sort.c. Запуск: make test 6 2 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

/* Подключаем решение. Его main переименован, чтобы не мешать тестовому. */
#define main demo_main
#include "../../exercises/06_graphs/02_topo_sort.c"
#undef main

/* Проверяет, что order — перестановка всех вершин и что каждая дуга идёт слева направо. */
static int is_valid_order(const Graph* graph, const size_t* order)
{
    size_t position[MAX_VERTICES];
    int seen[MAX_VERTICES] = { 0 };

    for (size_t i = 0; i < graph->vertex_count; i++) {
        if (order[i] >= graph->vertex_count || seen[order[i]]) {
            return 0;
        }
        seen[order[i]] = 1;
        position[order[i]] = i;
    }

    for (size_t from = 0; from < graph->vertex_count; from++) {
        for (size_t to = 0; to < graph->vertex_count; to++) {
            if (graph->adjacent[from][to] && position[from] >= position[to]) {
                return 0;
            }
        }
    }
    return 1;
}

static int sorts_correctly(const Graph* graph)
{
    size_t order[MAX_VERTICES];

    for (size_t i = 0; i < MAX_VERTICES; i++) {
        order[i] = 777;
    }
    return topo_sort(graph, order) && is_valid_order(graph, order);
}

static int rejects(const Graph* graph)
{
    size_t order[MAX_VERTICES];

    return !topo_sort(graph, order);
}

static void test_chain(void)
{
    Graph graph;
    size_t order[4];

    /* Единственный возможный порядок: 3, 2, 1, 0. */
    graph_init(&graph, 4);
    graph_add_arc(&graph, 3, 2);
    graph_add_arc(&graph, 2, 1);
    graph_add_arc(&graph, 1, 0);

    assert(!has_cycle(&graph));
    assert(topo_sort(&graph, order));
    assert(order[0] == 3 && order[1] == 2 && order[2] == 1 && order[3] == 0);
}

static void test_no_arcs(void)
{
    Graph graph;

    graph_init(&graph, 5);
    assert(!has_cycle(&graph));
    assert(sorts_correctly(&graph));

    graph_init(&graph, 1);
    assert(!has_cycle(&graph));
    assert(sorts_correctly(&graph));
}

static void test_diamond(void)
{
    Graph graph;

    /* 0 -> 1 -> 3 и 0 -> 2 -> 3: два пути в одну вершину — это не цикл. */
    graph_init(&graph, 4);
    graph_add_arc(&graph, 0, 1);
    graph_add_arc(&graph, 0, 2);
    graph_add_arc(&graph, 1, 3);
    graph_add_arc(&graph, 2, 3);

    assert(!has_cycle(&graph));
    assert(sorts_correctly(&graph));
}

static void test_dependencies(void)
{
    Graph graph;

    graph_init(&graph, 8);
    graph_add_arc(&graph, 7, 0);
    graph_add_arc(&graph, 7, 5);
    graph_add_arc(&graph, 5, 1);
    graph_add_arc(&graph, 0, 1);
    graph_add_arc(&graph, 4, 0);
    graph_add_arc(&graph, 6, 4);
    graph_add_arc(&graph, 6, 2);
    graph_add_arc(&graph, 2, 1);
    graph_add_arc(&graph, 1, 3);

    assert(!has_cycle(&graph));
    assert(sorts_correctly(&graph));
}

static void test_every_arc_forward_and_backward(void)
{
    Graph forward;
    Graph backward;

    /* Все дуги из меньшего номера в больший и наоборот. */
    graph_init(&forward, MAX_VERTICES);
    graph_init(&backward, MAX_VERTICES);
    for (size_t a = 0; a < MAX_VERTICES; a++) {
        for (size_t b = a + 1; b < MAX_VERTICES; b++) {
            graph_add_arc(&forward, a, b);
            graph_add_arc(&backward, b, a);
        }
    }

    assert(!has_cycle(&forward));
    assert(!has_cycle(&backward));
    assert(sorts_correctly(&forward));
    assert(sorts_correctly(&backward));
}

static void test_simple_cycles(void)
{
    Graph graph;

    graph_init(&graph, 3);
    graph_add_arc(&graph, 0, 1);
    graph_add_arc(&graph, 1, 2);
    graph_add_arc(&graph, 2, 0);
    assert(has_cycle(&graph));
    assert(rejects(&graph));

    graph_init(&graph, 2);
    graph_add_arc(&graph, 0, 1);
    graph_add_arc(&graph, 1, 0);
    assert(has_cycle(&graph));
    assert(rejects(&graph));

    graph_init(&graph, 2);
    graph_add_arc(&graph, 1, 1);
    assert(has_cycle(&graph));
    assert(rejects(&graph));
}

static void test_cycle_far_from_vertex_zero(void)
{
    Graph graph;

    /* Из вершины 0 цикл 3 -> 4 -> 5 -> 3 недостижим. */
    graph_init(&graph, 6);
    graph_add_arc(&graph, 0, 1);
    graph_add_arc(&graph, 1, 2);
    graph_add_arc(&graph, 3, 4);
    graph_add_arc(&graph, 4, 5);
    graph_add_arc(&graph, 5, 3);

    assert(has_cycle(&graph));
    assert(rejects(&graph));
}

static void test_cycle_behind_a_tail(void)
{
    Graph graph;

    /* 0 -> 1 -> 2 -> 3 -> 1: цикл начинается не с первой вершины пути. */
    graph_init(&graph, 4);
    graph_add_arc(&graph, 0, 1);
    graph_add_arc(&graph, 1, 2);
    graph_add_arc(&graph, 2, 3);
    graph_add_arc(&graph, 3, 1);

    assert(has_cycle(&graph));
    assert(rejects(&graph));
}

int main(void)
{
    test_chain();
    test_no_arcs();
    test_diamond();
    test_dependencies();
    test_every_arc_forward_and_backward();
    test_simple_cycles();
    test_cycle_far_from_vertex_zero();
    test_cycle_behind_a_tail();

    puts("All tests passed");
    return 0;
}
