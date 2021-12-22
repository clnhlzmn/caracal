#include "topo_sort.h"
#include <assert.h>
#include <string.h>

int main(void) {
    assert(topo_sort(NULL, 0, NULL, 0).error == TOPO_SORT_FAILURE_ARGS);
    const char *nodes[] = {
        "foo", "bar", "baz", "qux"
    };
    {
        topo_sort_edge edges[] = {
            {0, 1}, /* foo->bar */
            {1, 2}, /* bar->baz */
            {1, 3}, /* bar->qux */
            {0, 3}, /* foo->qux */
            {3, 2}, /* qux->baz */
        };
        /* Order should be baz, qux, bar, foo */
        int expected_order[] = {2, 3, 1, 0};
        topo_sort_return result = topo_sort(nodes, 4, edges, 5);
        assert(result.error == TOPO_SORT_SUCCESS);
        for (size_t i = 0; i < 4; ++i) {
            assert(strcmp(result.order[i], nodes[expected_order[i]]) == 0);
        }
    }
    {
        topo_sort_edge edges[] = {
            {0, 1}, /* foo->bar */
            {1, 2}, /* bar->baz */
            {2, 3}, /* baz->qux */
            {3, 0}, /* qux->foo */
        };
        topo_sort_return result = topo_sort(nodes, 4, edges, 4);
        assert(result.error == TOPO_SORT_FAILURE_CIRCULAR_DEPENDENCY);
    }
    return 0;
}
