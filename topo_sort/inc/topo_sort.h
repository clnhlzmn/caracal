#ifndef TOPO_SORT_H
#define TOPO_SORT_H

/* This implementation is adapted from 
 * https://rosettacode.org/wiki/Topological_sort#Kotlin 
 * (of all places). 
 * */

#include <stdlib.h>

typedef struct {
    int source;
    int target;
} topo_sort_edge;

typedef enum {
    TOPO_SORT_SUCCESS,
    TOPO_SORT_FAILURE_ARGS,
    TOPO_SORT_FAILURE_CIRCULAR_DEPENDENCY
} topo_sort_error;

typedef struct {
    topo_sort_error error;
    const char **order;
} topo_sort_return;

/* Nodes is a list of strings that identify the vertices of the graph.
 * Edges is a list of pairs of index from node to node, where the first node depends on the second.
 * The return value is either a failure, or in the case of success contains a pointer to an array of strings
 * that is in topological order. I.e. things earlier in the list are guranteed not to depend on things later
 * in the list.
 */
topo_sort_return topo_sort(const char **nodes, size_t node_count, topo_sort_edge *edges, size_t edge_count);

#endif /* TOPO_SORT_H */
