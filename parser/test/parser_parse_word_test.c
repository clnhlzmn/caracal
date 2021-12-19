#include "parser.h"
#include "word.h"
#include <assert.h>
#include <string.h>

int main(void) {
    lexer_token *tokens;
    lexer_lex(&tokens, "foo");
    parser_return result = parser_parse_word(tokens);
    assert(result.error == PARSER_SUCCESS && "foo should parse successfully");
    assert(word_equal(result.value, word_make_name("foo")) && "result.value should equal word_make_name(foo)");
    
    lexer_lex(&tokens, "123");
    result = parser_parse_word(tokens);
    assert(result.error == PARSER_SUCCESS && "123 should parse successfully");
    assert(word_equal(result.value, word_make_number(123)) && "result.value should equal word_make_number(123)");
    
    lexer_lex(&tokens, "()");
    result = parser_parse_word(tokens);
    assert(result.error == PARSER_SUCCESS && "() should parse successfully");
    assert(word_equal(result.value, word_make_quote(NULL)) && "result.value should equal word_make_quote(NULL)");
    
    lexer_lex(&tokens, "(foo 123)");
    result = parser_parse_word(tokens);
    assert(result.error == PARSER_SUCCESS && "(foo 123) should parse successfully");
    assert(word_equal(result.value, word_make_quote(word_make_compose(word_make_name("foo"), word_make_number(123)))) && "result.value should equal (foo 123)");
    
    lexer_lex(&tokens, "((foo) bar)");
    result = parser_parse_word(tokens);
    assert(result.error == PARSER_SUCCESS && "((foo) bar) should parse successfully");
    assert(word_equal(result.value, word_make_quote(word_make_compose(word_make_quote(word_make_name("foo")), word_make_name("bar")))) && "result.value should equal ((foo) bar)");
    
    lexer_lex(&tokens, "(foo bar baz)");
    result = parser_parse_word(tokens);
    assert(result.error == PARSER_SUCCESS && "(foo bar baz) should parse successfully");
    assert(word_equal(result.value, word_make_quote(word_make_compose(word_make_name("foo"), word_make_compose(word_make_name("bar"), word_make_name("baz"))))) && "result.value should equal (foo bar baz)");
    
    lexer_lex(&tokens, "(");
    assert(parser_parse_word(tokens).error == PARSER_FAILURE && "( should fail to parse");
    
    lexer_lex(&tokens, "(foo");
    assert(parser_parse_word(tokens).error == PARSER_FAILURE && "(foo should fail to parse");
    
    lexer_lex(&tokens, "((foo)");
    assert(parser_parse_word(tokens).error == PARSER_FAILURE && "((foo) should fail to parse");
    return 0;
}
