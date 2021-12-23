#ifndef TEST_VM_H
#define TEST_VM_H

#include "vm.h"
#include <inttypes.h>
#include <stdio.h>

#include "test_heap.h"

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

vm test_vm;
intptr_t stack[TEST_VM_STACK_SIZE];

vm_word words[] = {
    [0] = word_push_42, 
    [1] = word_println
};

void test_vm_init(void) {
    test_heap_init();
    vm_init(&test_vm, &test_heap, stack, TEST_VM_STACK_SIZE, words, sizeof(words) / sizeof(vm_word));
}

#endif /* TEST_VM_H */
