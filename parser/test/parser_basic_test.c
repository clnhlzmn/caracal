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
    return 0;
}
