#include "vm.h"
#include <assert.h>

#define TEST_VM_STACK_SIZE 100
#define TEST_HEAP_SIZE (2 * TEST_VM_STACK_SIZE)

#include "test_vm.h"

int main(void) {
    test_vm_init();
    for (int n = 0; n < 2; ++n) {
        heap_pair *two_pairs = heap_alloc_list(&test_heap, 2, HEAP_MARK_INT(42), HEAP_MARK_INT(43));
        vm_push(&test_vm, (intptr_t)two_pairs);
        for (int i = 1; i < TEST_VM_STACK_SIZE; ++i) {
            vm_dup(&test_vm);
        }
        assert(heap_is_empty(&test_heap));
        for (int i = 0; i < TEST_VM_STACK_SIZE; ++i) {
            vm_drop(&test_vm);
        }
    }
    return 0;
}
