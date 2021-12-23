#ifndef VM_H
#define VM_H

#define IS_INT(v) (v & 1)
#define MARK_INT(v) ((v << 1) | 1)
#define INT_VALUE(v) (v >> 1)

typedef struct {
    intptr_t first;
    intptr_t second;
} pair;

typedef struct {
    pair *memory;
    size_t heap_size;
    pair *free_list;
} heap;

#endif /* VM_H */
