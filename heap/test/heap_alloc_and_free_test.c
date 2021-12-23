#include "heap.h"
#include <assert.h>

#define HEAP_SIZE 1000

int main(void) {
    heap the_heap;
    heap_pair heap_mem[HEAP_SIZE];
    heap_init(&the_heap, heap_mem, HEAP_SIZE);
    for (size_t n = 0; n < 2; ++n) {
        heap_pair *list = NULL;
        for (size_t i = 0; i < HEAP_SIZE; ++i) {
            heap_pair *new_pair = heap_alloc(&the_heap);
            assert(new_pair);
            new_pair->second = (intptr_t)list;
            list = new_pair;
        }
        while (list) {
            heap_pair *p = list;
            list = (heap_pair*)list->second;
            heap_free(&the_heap, p);
        }
    }
    
    return 0;
}
