#include "ast.h"
#include "stdlib.h"

ast_node *ast_make_word(const char *text) {
    ast_node *ret = malloc(sizeof(ast_node));
    ret->type = AST_NODE_WORD;
    ret->word.text = text;
    return ret;
}

ast_node *ast_make_number(int64_t value) {
    ast_node *ret = malloc(sizeof(ast_node));
    ret->type = AST_NODE_NUMBER;
    ret->number.value = value;
    return ret;
}

ast_node *ast_make_compose(ast_node *first, ast_node *second) {
    ast_node *ret = malloc(sizeof(ast_node));
    ret->type = AST_NODE_COMPOSE;
    ret->compose.first = first;
    ret->compose.second = second;
    return ret;
}

ast_node *ast_make_quote(ast_node *word) {
    ast_node *ret = malloc(sizeof(ast_node));
    ret->type = AST_NODE_QUOTE;
    ret->quote.word = word;
    return ret;
}
