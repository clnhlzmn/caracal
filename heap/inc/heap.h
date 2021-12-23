#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include <stdlib.h>

#define HEAP_IS_INT(v) (v & 1)
#define HEAP_MARK_INT(v) ((v << 1) | 1)
#define HEAP_INT_VALUE(v) (v >> 1)

typedef struct {
    intptr_t first;
    intptr_t second;
} heap_pair;

typedef struct {
    heap_pair *memory;
    size_t heap_size;
    heap_pair *free_list;
} heap;

void heap_init(heap *self, heap_pair *memory, size_t count);

heap_pair *heap_alloc(heap *self);

/* Returns the given heap_pair to the free list. */
void heap_free(heap *self, heap_pair *p);

/* Creates a clone of the given heap_pair */
heap_pair *heap_dup(heap *self, heap_pair *p);

/* Returns the given heap_pair and its children to the free list. */
void heap_drop(heap *self, heap_pair *p);

#endif /* HEAP_H */
