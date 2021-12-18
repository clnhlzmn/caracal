#include "ast.h"
#include <assert.h>
#include <string.h>

int main(void) {
    ast_node *word = ast_make_word("foo");
    ast_node *node = ast_make_quote(word);
    assert(node && "node should not be null");
    assert(node->type == AST_NODE_QUOTE && "node->type should equal AST_NODE_WORD");
    assert(node->quote.word == word && "node->quote.word should equal word");
    return 0;
}
