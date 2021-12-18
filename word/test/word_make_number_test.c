#include "word.h"
#include <assert.h>
#include <string.h>

int main(void) {
    int64_t value = 69;
    word *node = word_make_number(value);
    assert(node && "node should not be null");
    assert(node->type == WORD_NUMBER && "node type should be WORD_NUMBER");
    assert(node->number.value == value && "node->number.value should equal value");
    return 0;
}
