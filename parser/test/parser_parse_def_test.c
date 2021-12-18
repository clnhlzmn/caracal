#include "parser.h"
#include <assert.h>

int main(void) {
    lexer_token *tokens;
    lexer_lex(&tokens, "let foo = .");
    assert(parser_parse_def(tokens).error == PARSER_SUCCESS && "let foo = . should parse successfully");
    lexer_lex(&tokens, "let foo = 123 .");
    assert(parser_parse_def(tokens).error == PARSER_SUCCESS && "let foo = 123 . should parse successfully");
    lexer_lex(&tokens, "let foo = bar 123 .");
    assert(parser_parse_def(tokens).error == PARSER_SUCCESS && "let foo = bar 123 . should parse successfully");
    lexer_lex(&tokens, "let = 123 .");
    assert(parser_parse_def(tokens).error == PARSER_FAILURE && "let = 123 . should fail to parse");
    lexer_lex(&tokens, "foo = 123 .");
    assert(parser_parse_def(tokens).error == PARSER_FAILURE && "foo = 123 . should fail to parse");
    lexer_lex(&tokens, "let foo 123 .");
    assert(parser_parse_def(tokens).error == PARSER_FAILURE && "let foo 123 . should fail to parse");
    lexer_lex(&tokens, "let foo = 123");
    assert(parser_parse_def(tokens).error == PARSER_FAILURE && "let foo = 123 should fail to parse");
    return 0;
}
