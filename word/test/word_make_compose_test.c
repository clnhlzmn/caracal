#include "word.h"
#include <assert.h>
#include <string.h>

int main(void) {
    word *first = word_make_name("foo");
    word *second = word_make_number(42);
    word *node = word_make_compose(first, second);
    assert(node && "node should not be null");
    assert(node->type == WORD_COMPOSE && "node->type should be WORD_COMPOSE");
    assert(node->compose.first == first && "node->compose.first should equal first");
    assert(node->compose.second == second && "node->compose.second should equal second");
    return 0;
}
