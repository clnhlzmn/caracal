#ifndef TEST_HEAP_H
#define TEST_HEAP_H

#ifndef TEST_HEAP_SIZE
#define TEST_HEAP_SIZE 1000
#endif

heap test_heap;
heap_pair heap_mem[TEST_HEAP_SIZE];

void test_heap_init(void) {
    heap_init(&test_heap, heap_mem, TEST_HEAP_SIZE);
}

#endif /* TEST_HEAP_H */
