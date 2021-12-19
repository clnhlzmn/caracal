#include "parser.h"
#include "def.h"
#include <assert.h>

int main(void) {
    lexer_token *tokens;
    lexer_lex(&tokens, "let foo = .");
    parser_return result = parser_parse_def(tokens);
    assert(result.error == PARSER_SUCCESS && "let foo = . should parse successfully");
    assert(result.value && "result.value should not be NULL");
    assert(def_equal(def_make_let("foo", word_make_quote(NULL)), result.value));
    
    lexer_lex(&tokens, "let foo = 123 .");
    result = parser_parse_def(tokens);
    assert(result.error == PARSER_SUCCESS && "let foo = 123 . should parse successfully");
    assert(result.value && "result.value should not be NULL");
    assert(def_equal(def_make_let("foo", word_make_quote(word_make_number(123))), result.value));
    
    lexer_lex(&tokens, "let foo = bar 123 .");
    result = parser_parse_def(tokens);
    assert(result.error == PARSER_SUCCESS && "let foo = bar 123 . should parse successfully");
    assert(result.value && "result.value should not be NULL");
    assert(def_equal(def_make_let("foo", word_make_quote(word_make_compose(word_make_name("bar"), word_make_number(123)))), result.value));
    
    lexer_lex(&tokens, "let = 123 .");
    result = parser_parse_def(tokens);
    assert(result.error == PARSER_FAILURE && "let = 123 . should fail to parse");
    
    lexer_lex(&tokens, "foo = 123 .");
    result = parser_parse_def(tokens);
    assert(result.error == PARSER_FAILURE && "foo = 123 . should fail to parse");
    
    lexer_lex(&tokens, "let foo 123 .");
    result = parser_parse_def(tokens);
    assert(result.error == PARSER_FAILURE && "let foo 123 . should fail to parse");
    
    lexer_lex(&tokens, "let foo = 123");
    result = parser_parse_def(tokens);
    assert(result.error == PARSER_FAILURE && "let foo = 123 should fail to parse");
    return 0;
}
