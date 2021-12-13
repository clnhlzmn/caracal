#include "parser.h"
#include <assert.h>

int main(void) {
    lexer_token *tokens;
    lexer_lex(&tokens, "abc = 123");
    parser_return err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_SUCCESS && "'abc = 123' should parse successfully");
    lexer_lex(&tokens, "= 123");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_FAILURE && "'= 123' should fail to parse");
    lexer_lex(&tokens, "abc =");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_FAILURE && "'abc =' should fail to parse");
    return 0;
}
