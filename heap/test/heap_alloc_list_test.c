#include "heap.h"
#include <assert.h>

#define TEST_HEAP_SIZE 5

#include "test_heap.h"

int main(void) {
    test_heap_init();
    for (int n = 0; n < 2; ++n) {
        heap_pair *list = heap_alloc_list(&test_heap, 5, HEAP_MARK_INT(0), HEAP_MARK_INT(1), HEAP_MARK_INT(2), HEAP_MARK_INT(3), HEAP_MARK_INT(4));
        assert(test_heap.free_list == NULL);
        for (intptr_t i = 0; i < 5; ++i) {
            assert(list);
            assert(HEAP_INT_VALUE(list->first) == i);
            heap_pair *next = (heap_pair*)list->second;
            heap_free(&test_heap, list);
            list = next;
        }
    }
}