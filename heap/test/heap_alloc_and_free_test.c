#include "heap.h"
#include <assert.h>

#include "test_heap.h"

int main(void) {
    test_heap_init();
    for (size_t n = 0; n < 2; ++n) {
        heap_pair *list = NULL;
        for (size_t i = 0; i < TEST_HEAP_SIZE; ++i) {
            heap_pair *new_pair = heap_alloc(&test_heap);
            assert(new_pair);
            new_pair->second = (intptr_t)list;
            list = new_pair;
        }
        assert(test_heap.free_list == NULL);
        while (list) {
            heap_pair *p = list;
            list = (heap_pair*)list->second;
            heap_free(&test_heap, p);
        }
    }
    
    return 0;
}
