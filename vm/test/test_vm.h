#ifndef TEST_VM_H
#define TEST_VM_H

#include "vm.h"
#include <inttypes.h>
#include <stdio.h>

#ifndef TEST_VM_HEAP_SIZE
#define TEST_VM_HEAP_SIZE 1000
#endif

#ifndef TEST_VM_STACK_SIZE
#define TEST_VM_STACK_SIZE 1000
#endif

void word_push_42(vm *vm) {
    vm_push(vm, HEAP_MARK_INT(42)); 
}

void word_println(vm *vm) {
    printf("%"PRIdPTR"\n", *(vm->tos - 1));
    vm_drop(vm);
}

heap test_heap;
heap_pair heap_mem[TEST_VM_HEAP_SIZE];

vm test_vm;
intptr_t stack[TEST_VM_STACK_SIZE];

vm_word words[] = {word_push_42, word_println};

void test_vm_init(void) {
    heap_init(&test_heap, heap_mem, TEST_VM_HEAP_SIZE);
    vm_init(&test_vm, &test_heap, stack, TEST_VM_STACK_SIZE, words, sizeof(words) / sizeof(vm_word));
}

#endif /* TEST_VM_H */
