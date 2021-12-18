#include "parser.h"
#include <assert.h>

int main(void) {
    lexer_token *tokens;
    lexer_lex(&tokens, "foo");
    assert(parser_parse_word(tokens).error == PARSER_SUCCESS && "foo should parse successfully");
    lexer_lex(&tokens, "123");
    assert(parser_parse_word(tokens).error == PARSER_SUCCESS && "123 should parse successfully");
    lexer_lex(&tokens, "()");
    assert(parser_parse_word(tokens).error == PARSER_SUCCESS && "() should parse successfully");
    lexer_lex(&tokens, "(foo 123)");
    assert(parser_parse_word(tokens).error == PARSER_SUCCESS && "(foo 123) should parse successfully");
    lexer_lex(&tokens, "((foo) bar)");
    assert(parser_parse_word(tokens).error == PARSER_SUCCESS && "((foo) bar) should parse successfully");
    lexer_lex(&tokens, "(");
    assert(parser_parse_word(tokens).error == PARSER_FAILURE && "( should fail to parse");
    lexer_lex(&tokens, "(foo");
    assert(parser_parse_word(tokens).error == PARSER_FAILURE && "(foo should fail to parse");
    lexer_lex(&tokens, "((foo)");
    assert(parser_parse_word(tokens).error == PARSER_FAILURE && "((foo) should fail to parse");
    return 0;
}
