#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>

/**
 * Compares the type of the token at @ref index in the @ref tokens list and returns 
 * true if it is equal to @ref type and false otherwise
 */
static bool token_type(const lexer_token *tokens, size_t index, lexer_token_type type) {
    while (index--) {
        if (!tokens) return false;
        tokens = tokens->next;
    }
    if (!tokens) return false;
    return tokens->type == type;
}

/** 
 * Takes @ref count @ref lexer_token_type as varargs and compares 
 * them to the type of the token at @ref index in the @ref tokens list.
 * If the token at @ref index in the @ref tokens list has the same type
 * as any of the varargs then @ref token_types returns true otherwise
 * it returns false.
 */
static bool token_types(const lexer_token *tokens, size_t index, size_t count, ...) {
    va_list ap;
    va_start(ap, count);
    bool ret = false;
    for (size_t i = 0; i < count; ++i) {
        lexer_token_type type = va_arg(ap, lexer_token_type);
        if (token_type(tokens, index, type)) {
            ret = true;
            break;
        }
    }
    va_end(ap);
    return ret;
}

static void consume(const lexer_token **tokens, size_t num) {
    while (num--) {
        *tokens = (*tokens)->next;
    }
}

static bool expect(const lexer_token **tokens, lexer_token_type type) {
    if (!*tokens) return false;
    if ((*tokens)->type != type)
        return false;
    *tokens = (*tokens)->next;
    return true;
}

static parser_return word(const lexer_token **tokens) {
    if (token_type(*tokens, 0, LEXER_NATURAL)) {
        consume(tokens, 1);
        return (parser_return){ PARSER_SUCCESS };
    } else if (token_type(*tokens, 0, LEXER_ID)) {
        consume(tokens, 1);
        return (parser_return){ PARSER_SUCCESS };
    } else if (token_type(*tokens, 0, LEXER_L_PAREN)) {
        consume(tokens, 1);
        while (1) {
            if (token_type(*tokens, 0, LEXER_R_PAREN)) {
                consume(tokens, 1);
                return (parser_return){ PARSER_SUCCESS };
            }
            parser_return parsed_word = word(tokens);
            if (parsed_word.error) return parsed_word;
        }
    }
    return (parser_return){ PARSER_FAILURE };
}

static parser_return def(const lexer_token **tokens) {
    if (!expect(tokens, LEXER_LET)) {
        return (parser_return){ PARSER_FAILURE };
    }
    if (!token_type(*tokens, 0, LEXER_ID)) {
        return (parser_return){ PARSER_FAILURE };
    }
    consume(tokens, 1);
    if (!expect(tokens, LEXER_ASSIGN)) {
        return (parser_return){ PARSER_FAILURE };
    }
    while (1) {
        if (token_type(*tokens, 0, LEXER_DOT)) {
            consume(tokens, 1);
            return (parser_return){ PARSER_SUCCESS };
        }
        parser_return parsed_word = word(tokens);
        if (parsed_word.error) return parsed_word;
    }
}

parser_return parser_parse_def(const lexer_token *tokens) {
    return def(&tokens);
}

parser_return parser_parse_word(const lexer_token *tokens) {
    return word(&tokens);
}
