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
    heap_pair *return_stack;
};

void vm_init(vm *self, heap *heap, intptr_t *stack, size_t stack_size, vm_word *words, size_t word_count);

/* Adds an item to the top of the stack */
void vm_push(vm *self, intptr_t v);

/* Removes an item from the stack, but doesn't free that item */
intptr_t vm_pop(vm *self);

/* Duplicates the top of the stack */
void vm_dup(vm *self);

void vm_drop(vm *self);

void vm_push_to(vm *self, heap_pair **stack, intptr_t value);

intptr_t vm_pop_from(vm *self, heap_pair **stack);

/* Drops front of the current program list and puts
 * the rest on the return_stack. Then sets the current program
 * to the second argument. */
void vm_call(vm *self, heap_pair *program);

/* Used in the implementation of a vm_word to move to the next
 * word in the program list. This is an alternative to a vm_word
 * using vm_call, but one or the other must be called by each
 * vm_word implementation. */
void vm_next_word(vm *self);

#endif /* VM_H */
