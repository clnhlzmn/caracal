#include "ast.h"
#include <assert.h>
#include <string.h>

int main(void) {
    int64_t value = 69;
    ast_node *node = ast_make_number(value);
    assert(node && "node should not be null");
    assert(node->type == AST_NODE_NUMBER && "node type should be AST_NODE_NUMBER");
    assert(node->number.value == value && "node->number.value should equal value");
    return 0;
}
