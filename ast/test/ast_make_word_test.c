#include "ast.h"
#include <assert.h>
#include <string.h>

int main(void) {
    ast_node *node = ast_make_word("foo");
    assert(node && "node should not be null");
    assert(node->type == AST_NODE_WORD && "node->type should equal AST_NODE_WORD");
    assert(strcmp(node->word.text, "foo") == 0 && "node->word.text should equal foo");
    return 0;
}
