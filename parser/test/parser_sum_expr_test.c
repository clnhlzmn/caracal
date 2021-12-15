#include "parser.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    lexer_token *tokens;
    lexer_token_type rel_op_token_types[] = {
        LEXER_ADD, LEXER_SUB
    };
    const char *rel_op_token_texts[] = {
        "+", "-"
    };
    for (size_t i = 0; i < sizeof(rel_op_token_types) / sizeof(lexer_token_type); ++i) {
        char buf[100];
        snprintf(buf, 100, "123 %s abc", rel_op_token_texts[i]);
        lexer_lex(&tokens, buf);
        parser_return err = parser_parse_expr(NULL, tokens);
        assert(err == PARSER_SUCCESS && "'123 <sum_op> abc' should parse successfully");
    }
    for (size_t i = 0; i < sizeof(rel_op_token_types) / sizeof(lexer_token_type); ++i) {
        if (rel_op_token_types[i] == LEXER_SUB) continue;
        char buf[100];
        snprintf(buf, 100, "%s abc", rel_op_token_texts[i]);
        lexer_lex(&tokens, buf);
        parser_return err = parser_parse_expr(NULL, tokens);
        assert(err == PARSER_FAILURE && "'<sum_op> abc' should fail to parse");
    }
    for (size_t i = 0; i < sizeof(rel_op_token_types) / sizeof(lexer_token_type); ++i) {
        char buf[100];
        snprintf(buf, 100, "123 %s", rel_op_token_texts[i]);
        lexer_lex(&tokens, buf);
        parser_return err = parser_parse_expr(NULL, tokens);
        assert(err == PARSER_FAILURE && "'123 <sum_op>' should fail to parse");
    }
    return 0;
}
