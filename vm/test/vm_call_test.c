#include "vm.h"
#include <assert.h>

#include "test_vm.h"

int main(void) {
    test_vm_init();
    heap_pair *program1 = heap_alloc_list(&test_heap, 2, HEAP_MARK_INT(0), HEAP_MARK_INT(1));
    /* This should set vm.program to [0 1]. */
    vm_call(&test_vm, program1);
    assert(test_vm.return_stack == NULL);
    assert(test_vm.program == program1);
    heap_pair *program2 = heap_alloc_list(&test_heap, 1, HEAP_MARK_INT(2));
    /* This should set vm.program to [2] and set vm.return_stack to [1]. */
    vm_call(&test_vm, program2);
    assert(test_vm.return_stack);
    assert(HEAP_INT_VALUE(((heap_pair*)test_vm.return_stack->first)->first) == 1);
    assert(test_vm.return_stack->second == 0);
    assert(HEAP_INT_VALUE(test_vm.program->first) == 2);
    assert(test_vm.program->second == 0);
    return 0;
}
