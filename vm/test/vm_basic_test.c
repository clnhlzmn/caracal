#include "vm.h"
#include <stdio.h>
#include <inttypes.h>

void word_push_42(vm *vm) {
    vm_push(vm, HEAP_MARK_INT(42)); 
}

void word_println(vm *vm) {
    printf("%"PRIdPTR"\n", *(vm->tos - 1));
    vm_drop(vm);
}

#define SIZE 1000

int main(void) {
    heap the_heap;
    heap_pair heap_mem[SIZE];
    heap_init(&the_heap, heap_mem, SIZE);
    
    vm the_vm;
    intptr_t stack[SIZE];
    vm_word words[] = {};
    vm_init(&the_vm, &the_heap, stack, SIZE, words, sizeof(words) / sizeof(vm_word));
    
    return 0;
}
