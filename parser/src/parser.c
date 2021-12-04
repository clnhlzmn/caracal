#include "parser.h"
#include <stdbool.h>
#include <stdio.h>

static bool token_type(const lexer_token *tokens, size_t index, lexer_token_type type) {
    while (index--) {
        if (!tokens) return false;
        tokens = tokens->next;
    }
    if (!tokens) return false;
    return tokens->type == type;
}

static void consume(const lexer_token **tokens, size_t num) {
    while (num--) {
        *tokens = (*tokens)->next;
    }
}

static bool expect(const lexer_token **tokens, lexer_token_type type) {
    if ((*tokens)->type != type)
        return false;
    *tokens = (*tokens)->next;
    return true;
}

static parser_return expr(const lexer_token **tokens);
static parser_return or_expr(const lexer_token **tokens);
static parser_return and_expr(const lexer_token **tokens);
static parser_return unary_rel_expr(const lexer_token **tokens);
static parser_return rel_expr(const lexer_token **tokens);
static parser_return sum_expr(const lexer_token **tokens);
static parser_return mul_expr(const lexer_token **tokens);
static parser_return unary_expr(const lexer_token **tokens);
static parser_return factor_expr(const lexer_token **tokens);
static parser_return call(const lexer_token **tokens);

static parser_return expr(const lexer_token **tokens) {
    if (token_type(*tokens, 0, LEXER_ID) && token_type(*tokens, 1, LEXER_ASSIGN)) {
        printf("%s = ", (*tokens)->text);
        consume(tokens, 2);
        return or_expr(tokens);
    }
    return or_expr(tokens);
}

static parser_return or_expr(const lexer_token **tokens) {
    parser_return err = and_expr(tokens);
    if (err) return err;
    while (token_type(*tokens, 0, LEXER_OR)) {
        
    }
    return PARSER_SUCCESS;
}

static parser_return and_expr(const lexer_token **tokens) {
    parser_return err = unary_rel_expr(tokens);
    if (err) return err;
    /*TODO check for AND operator and more unaryRelExpr*/
    return PARSER_SUCCESS;
}

static parser_return unary_rel_expr(const lexer_token **tokens) {
    /*TODO check for unary NOT here*/
    parser_return err = rel_expr(tokens);
    if (err) return err;
    return PARSER_SUCCESS;
}

static parser_return rel_expr(const lexer_token **tokens) {
    parser_return err = sum_expr(tokens);
    if (err) return err;
    /*TODO check for relop and more sumExpr*/
    return PARSER_SUCCESS;
}

static parser_return sum_expr(const lexer_token **tokens) {
    parser_return err = mul_expr(tokens);
    if (err) return err;
    /*TODO check for sum op and more mulExpr*/
    return PARSER_SUCCESS;
}

static parser_return mul_expr(const lexer_token **tokens) {
    parser_return err = unary_expr(tokens);
    if (err) return err;
    /*TODO check for sum op and more mulExpr*/
    return PARSER_SUCCESS;
}

static parser_return unary_expr(const lexer_token **tokens) {
    /*check for unary NEG here*/
    parser_return err = factor_expr(tokens);
    if (err) return err;
    /*TODO check for sum op and more mulExpr*/
    return PARSER_SUCCESS;
}

static parser_return factor_expr(const lexer_token **tokens) {
    if (token_type(*tokens, 0, LEXER_L_PAREN)) {
        consume(tokens, 1);
        parser_return err = expr(tokens);
        if (err) return err;
        if (!expect(tokens, LEXER_R_PAREN)) return PARSER_FAILURE;
        return call(tokens);
    } else if (token_type(*tokens, 0, LEXER_NATURAL)) {
        /*TODO use token to create NATURAL ast node*/
        return PARSER_SUCCESS;
    } else if (token_type(*tokens, 0, LEXER_ID)) {
        /*TODO use ID here*/
        consume(tokens, 1);
        return call(tokens);
    }
    return PARSER_FAILURE;
}

static parser_return call(const lexer_token **tokens) {
    if (token_type(*tokens, 0, LEXER_L_PAREN)) {
        consume(tokens, 1);
        /*TODO parse args*/
        if (!expect(tokens, LEXER_R_PAREN)) return PARSER_FAILURE;
        return call(tokens);
    } else {
        return PARSER_SUCCESS;
    }
}

parser_return parse_expr(void *output, const lexer_token *tokens) {
    (void)output;
    return expr(&tokens);
}
