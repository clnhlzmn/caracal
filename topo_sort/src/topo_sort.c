#include "topo_sort.h"
#include <stdbool.h>
#include <string.h>

static bool empty(int *todo, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (todo[i] >= 0) {
            return false;
        }
    }
    return true;
}

static bool has_dependency(int *todo, size_t count, size_t index, bool adjacency[][count]) {
    for (size_t i = 0; i < count; ++i) {
        if (todo[i] < 0) continue;
        if (adjacency[index][i]) return true;
    }
    return false;
}

topo_sort_return topo_sort(const char **nodes, size_t node_count, topo_sort_edge *edges, size_t edge_count) {
    if (!nodes || !edges) {
        return (topo_sort_return){ .error = TOPO_SORT_FAILURE_ARGS, .order = NULL };
    }
    /* Create adjacency list. */
    bool adjacency_list[node_count][node_count];
    memset(adjacency_list, 0, sizeof(adjacency_list));
    for (size_t i = 0; i < edge_count; ++i) {
        adjacency_list[edges[i].source][edges[i].target] = true;
    }
    /* Create result array. */
    const char **result = malloc(sizeof(char*) * node_count);
    const char **next = result;
    /* Create todo buffer. */
    int todo[node_count];
    for (size_t i = 0; i < node_count; ++i) {
        todo[i] = i;
    }
    /* Do sorting. */
    while (!empty(todo, node_count)) {
        for (size_t i = 0; i < node_count; ++i) {
            if (todo[i] < 0) continue;
            if (!has_dependency(todo, node_count, i, adjacency_list)) {
                todo[i] = -1;
                *next++ = nodes[i];
                goto outer_continue;
            }
        }
        free(result);
        return (topo_sort_return){ .error = TOPO_SORT_FAILURE_CIRCULAR_DEPENDENCY, .order = NULL };
        outer_continue:
        ;
    }
    return (topo_sort_return){ .error = TOPO_SORT_SUCCESS, .order = result };
}
