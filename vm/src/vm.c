#include "vm.h"
#include <assert.h>

void vm_init(vm *self, heap *heap, intptr_t *stack, size_t stack_size, vm_word *words, size_t word_count) {
    assert(self && heap && stack && words);
    self->heap = heap;
    self->stack = stack;
    self->stack_size = stack_size;
    self->tos = stack;
    self->words = words;
    self->word_count = word_count;
}

/* Adds an item to the top of the stack */
void vm_push(vm *self, intptr_t v) {
    assert(self);
    assert(self->tos - self->stack < (intptr_t)self->stack_size);
    *self->tos++ = v;
}

/* Removes an item from the stack, but doesn't free that item */
intptr_t vm_pop(vm *self) {
    assert(self);
    assert(self->tos - self->stack > 0);
    return *--self->tos;
}

/* Duplicates the top of the stack */
void vm_dup(vm *self) {
    intptr_t top = vm_pop(self);
    intptr_t dup = top;
    if (!HEAP_IS_INT(top)) dup = (intptr_t)heap_dup(self->heap, (heap_pair*)top);
    vm_push(self, top);
    vm_push(self, dup);
}

void vm_drop(vm *self) {
    intptr_t top = vm_pop(self);
    if (!HEAP_IS_INT(top)) heap_drop(self->heap, (heap_pair*)top);
}

void vm_run(vm *self, heap_pair *program) {
    assert(self);
    while (program) {
        if (HEAP_IS_INT(program->first)) {
            intptr_t word_index = HEAP_INT_VALUE(program->first);
            assert(word_index < (size_t)self->word_count);
            vm_word word = self->words[word_index];
            
        } else {
            
        }
        program = (heap_pair*)program->second;
    }
}
