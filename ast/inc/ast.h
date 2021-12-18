#ifndef AST_H
#define AST_H

#include <stdint.h>

typedef enum {
    AST_NODE_WORD,
    AST_NODE_NUMBER,
    AST_NODE_COMPOSE,
    AST_NODE_QUOTE
} ast_node_type;

typedef struct ast_node ast_node;

typedef struct {
    const char *text;
} ast_node_word;

typedef struct {
    int64_t value;
} ast_node_number;

typedef struct {
    ast_node *first;
    ast_node *second;
} ast_node_compose;

typedef struct {
    ast_node *word;
} ast_node_quote;

struct ast_node {
    ast_node_type type;
    union {
        ast_node_word word;
        ast_node_number number;
        ast_node_compose compose;
        ast_node_quote quote;
    };
};

ast_node *ast_make_word(const char *text);

ast_node *ast_make_number(int64_t value);

ast_node *ast_make_compose(ast_node *first, ast_node *second);

ast_node *ast_make_quote(ast_node *word);

#endif /*AST_H*/
