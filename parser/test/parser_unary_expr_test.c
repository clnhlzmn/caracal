#include "parser.h"
#include <assert.h>

int main(void) {
    lexer_token *tokens;
    lexer_lex(&tokens, "-abc");
    parser_return err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_SUCCESS && "'-abc' should parse successfully");
    lexer_lex(&tokens, "-");
    err = parser_parse_expr(NULL, tokens);
    assert(err == PARSER_FAILURE && "'-' should fail to parse");
    return 0;
}
