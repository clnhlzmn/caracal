#include "vm.h"
#include <assert.h>

#define TEST_HEAP_SIZE 5
#include "test_vm.h"

int main(void) {
    test_vm_init();
    for (int n = 0; n < 2; ++n) {
        for (int i = 0; i < TEST_HEAP_SIZE; ++i) {
            vm_push_to(&test_vm, &test_vm.program, HEAP_MARK_INT(i));
        }
        assert(heap_is_empty(&test_heap));
        for (int i = TEST_HEAP_SIZE; i > 0; --i) {
            intptr_t value = vm_pop_from(&test_vm, &test_vm.program);
            assert(HEAP_INT_VALUE(value) == i - 1);
        }
    }
    return 0;
}
