#include "parser.h"
#include <assert.h>

int main(void) {
    lexer_token *tokens;
    lexer_lex(&tokens, "!123");
    parser_return err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_SUCCESS && "'!123' should parse successfully");
    lexer_lex(&tokens, "!!123");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_SUCCESS && "'!!123' should parse successfully");
    lexer_lex(&tokens, "!");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_FAILURE && "'!' should fail to parse");
    return 0;
}
