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
    self->program = NULL;
    self->return_ = NULL;
}

void vm_push(vm *self, intptr_t v) {
    assert(self);
    assert(self->tos - self->stack < (intptr_t)self->stack_size);
    *self->tos++ = v;
}

intptr_t vm_pop(vm *self) {
    assert(self);
    assert(self->tos - self->stack > 0);
    return *--self->tos;
}

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

void vm_push_to(vm *self, heap_pair **stack, intptr_t value) {
    assert(self && stack);
    heap_pair *new_pair = heap_alloc(self->heap);
    new_pair->first = value;
    new_pair->second = (intptr_t)*stack;
    *stack = new_pair;
}

intptr_t vm_pop_from(vm *self, heap_pair **stack) {
    assert(self && stack && *stack);
    intptr_t value = (*stack)->first;
    heap_pair *top = *stack;
    *stack = (heap_pair*)(*stack)->second;
    heap_free(self->heap, top);
    return value;
}

void vm_run(vm *self, heap_pair *program) {
    assert(self);
    while (program) {
        if (HEAP_IS_INT(program->first)) {
            intptr_t word_index = HEAP_INT_VALUE(program->first);
            assert(word_index < (intptr_t)self->word_count);
            vm_word word = self->words[word_index];
            
        } else {
            
        }
        program = (heap_pair*)program->second;
    }
}
