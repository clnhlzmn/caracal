#ifndef VM_H
#define VM_H

#include "heap.h"
#include <stdlib.h>
#include <stdint.h>

typedef struct vm vm;

typedef void (*vm_word)(vm *);

struct vm {
    heap *heap;
    intptr_t *stack;
    size_t stack_size;
    intptr_t *tos;
    vm_word *words;
    size_t word_count;
    heap_pair *program;
    heap_pair *return_;
};

#endif /* VM_H */
