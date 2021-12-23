#include "vm.h"
#include <assert.h>

#include "test_vm.h"

int main(void) {
    test_vm_init();
    heap_pair *program = heap_alloc_list(&test_heap, 2, HEAP_MARK_INT(0), HEAP_MARK_INT(1));
    vm_call(&test_vm, program);
    vm_next_word(&test_vm);
    assert(HEAP_INT_VALUE(test_vm.program->first) == 1);
    assert(test_vm.program->second == 0);
    return 0;
}
