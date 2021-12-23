#include "vm.h"
#include <assert.h>

#include "test_vm.h"

int main(void) {
    test_vm_init();
    for (size_t i = 0; i < TEST_VM_STACK_SIZE; ++i) {
        vm_push(&test_vm, i);
    }
    for (intptr_t i = TEST_VM_STACK_SIZE; i > 0; --i) {
        assert(vm_pop(&test_vm) == (i - 1));
    }
    return 0;
}
