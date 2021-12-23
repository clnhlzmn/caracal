#include "vm.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>

#define HEAP_SIZE 1000

typedef struct vm vm;

typedef void (*vm_word)(vm *);

struct vm {
    heap *heap;
    intptr_t *stack;
    size_t stack_size;
    intptr_t *tos;
    vm_word *words;
    size_t word_count;
    pair *program;
    pair *return_;
};

static void vm_init(vm *self, heap *heap, intptr_t *stack, size_t stack_size, vm_word *words, size_t word_count) {
    assert(self && heap && stack && words);
    self->heap = heap;
    self->stack = stack;
    self->stack_size = stack_size;
    self->tos = stack;
    self->words = words;
    self->word_count = word_count;
}

/* Adds an item to the top of the stack */
static void vm_push(vm *self, intptr_t v) {
    assert(self);
    assert(self->tos - self->stack < (intptr_t)self->stack_size);
    *self->tos++ = v;
}

/* Removes an item from the stack, but doesn't free that item */
static intptr_t vm_pop(vm *self) {
    assert(self);
    assert(self->tos - self->stack > 0);
    return *--self->tos;
}

/* Duplicates the top of the stack */
static void vm_dup(vm *self) {
    intptr_t top = vm_pop(self);
    intptr_t dup = top;
    if (!IS_INT(top)) dup = (intptr_t)heap_dup(self->heap, (pair*)top);
    vm_push(self, top);
    vm_push(self, dup);
}

static void vm_drop(vm *self) {
    intptr_t top = vm_pop(self);
    if (!IS_INT(top)) heap_drop(self->heap, (pair*)top);
}

static void vm_run(vm *self, pair *program) {
    assert(self);
    while (program) {
        if (IS_INT(program->first)) {
            intptr_t word_index = INT_VALUE(program->first);
            assert(index < self->word_count);
            vm_word word = self->words[index];
            
        } else {
            
        }
        program = (pair*)program->second;
    }
}

static void word_push_42(vm *vm) {
    vm_push(vm, MARK_INT(42)); 
}

static void word_println(vm *vm) {
    printf("%"PRIdPTR"\n", *(vm->tos - 1));
    vm_drop(vm);
}

int main(void) {
    heap the_heap;
    pair heap_mem[HEAP_SIZE];
    heap_init(&the_heap, heap_mem, HEAP_SIZE);
    for (size_t n = 0; n < 2; ++n) {
        pair *list = NULL;
        for (size_t i = 0; i < HEAP_SIZE; ++i) {
            pair *new_pair = heap_alloc(&the_heap);
            assert(new_pair);
            new_pair->second = (intptr_t)list;
            list = new_pair;
        }
        while (list) {
            pair *p = list;
            list = (pair*)list->second;
            heap_free(&the_heap, p);
        }
    }
    
    vm the_vm;
    intptr_t stack[1000];
    vm_word words[] = {};
    vm_init(&the_vm, &the_heap, stack, 1000, words, sizeof(words) / sizeof(vm_word));
    
    return 0;
}
