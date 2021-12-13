#include "parser.h"
#include <assert.h>

int main(void) {
    lexer_token *tokens;
    lexer_lex(&tokens, "123 || abc");
    parser_return err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_SUCCESS && "'123 || abc' should parse successfully");
    lexer_lex(&tokens, "|| abc");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_FAILURE && "'|| abc' should fail to parse");
    lexer_lex(&tokens, "123 ||");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_FAILURE && "'123 ||' should fail to parse");
    return 0;
}
