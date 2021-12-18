#include "ast.h"
#include <assert.h>
#include <string.h>

int main(void) {
    ast_node *first = ast_make_word("foo");
    ast_node *second = ast_make_number(42);
    ast_node *node = ast_make_compose(first, second);
    assert(node && "node should not be null");
    assert(node->type == AST_NODE_COMPOSE && "node->type should be AST_NODE_COMPOSE");
    assert(node->compose.first == first && "node->compose.first should equal first");
    assert(node->compose.second == second && "node->compose.second should equal second");
    return 0;
}
