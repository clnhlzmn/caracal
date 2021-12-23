#include "heap.h"
#include <assert.h>

void heap_init(heap *self, heap_pair *memory, size_t count) {
    assert(self && memory);
    self->memory = memory;
    self->heap_size = count;
    self->free_list = memory;
    for (size_t i = 0; i < count; ++i) {
        memory[i].second = (intptr_t)self->free_list;
        self->free_list = &memory[i];
    }
}

heap_pair *heap_alloc(heap *self) {
    assert(self);
    assert(self->free_list);
    heap_pair *ret = self->free_list;
    self->free_list = (heap_pair*)self->free_list->second;
    return ret;
}

void heap_free(heap *self, heap_pair *p) {
    if (!p) return;
    p->second = (intptr_t)self->free_list;
    self->free_list = p;
}

heap_pair *heap_dup(heap *self, heap_pair *p) {
    assert(self);
    if (!p) return p;
    heap_pair *new_pair = heap_alloc(self);
    if (HEAP_IS_INT(p->first)) new_pair->first = p->first;
    else new_pair->first = (intptr_t)heap_dup(self, (heap_pair*)p->first);
    if (HEAP_IS_INT(p->second)) new_pair->second = p->second;
    else new_pair->second = (intptr_t)heap_dup(self, (heap_pair*)p->second);
    return new_pair;
}

void heap_drop(heap *self, heap_pair *p) {
    assert(self);
    if (!p) return;
    if (!HEAP_IS_INT(p->first)) heap_drop(self, (heap_pair*)p->first);
    if (!HEAP_IS_INT(p->second)) heap_drop(self, (heap_pair*)p->second);
    heap_free(self, p);
}
