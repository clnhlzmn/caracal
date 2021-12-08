#include "parser.h"
#include <assert.h>

int main(void) {
    lexer_token *tokens;
    lexer_lex(&tokens, "123");
    parser_return err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_SUCCESS);
    lexer_lex(&tokens, "abc");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_SUCCESS);
    lexer_lex(&tokens, "!");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_FAILURE);
    lexer_lex(&tokens, "!abc");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_SUCCESS);
    lexer_lex(&tokens, "foo()");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_SUCCESS);
    lexer_lex(&tokens, "foo(bar)");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_SUCCESS);
    lexer_lex(&tokens, "foo(bar, baz)");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_SUCCESS);
    lexer_lex(&tokens, "foo(bar,)");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_FAILURE);
    lexer_lex(&tokens, "foo(");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_FAILURE);
    lexer_lex(&tokens, "a+b");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_SUCCESS);
    lexer_lex(&tokens, "a+");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_FAILURE);
    return 0;
}
