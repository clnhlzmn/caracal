#include "parser.h"
#include "word.h"
#include "def.h"
#include "source_file.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>

/**
 * Compares the type of the token at @ref index in the @ref tokens list and returns 
 * true if it is equal to @ref type and false otherwise
 */
static bool token_type(const lexer_token *tokens, size_t index, lexer_token_variant type) {
    while (index--) {
        if (!tokens) return false;
        tokens = tokens->next;
    }
    if (!tokens) return false;
    return tokens->variant == type;
}

static void consume(const lexer_token **tokens, size_t num) {
    while (num--) {
        *tokens = (*tokens)->next;
    }
}

static bool expect(const lexer_token **tokens, lexer_token_variant type) {
    if (!*tokens) return false;
    if ((*tokens)->variant != type)
        return false;
    *tokens = (*tokens)->next;
    return true;
}

static parser_return parse_word_impl(const lexer_token **tokens);

/* Trys to parse a list of words.
 * If there were no words to parse then return value will be NULL,
 * if there was one word then return value will be that word, and
 * if there are two or more words then return value will be a compose
 * word containing those words. */
static word *parse_words_impl(const lexer_token **tokens) {
    parser_return first = parse_word_impl(tokens);
    if (first.error) {
        return NULL;
    }
    word *rest = parse_words_impl(tokens);
    if (rest == NULL) { /* No more words were found */
        return first.value;
    } else {
        return word_make_compose(first.value, rest);
    }
}

static parser_return parse_word_impl(const lexer_token **tokens) {
    if (token_type(*tokens, 0, LEXER_NATURAL)) {
        int64_t value = atoll((*tokens)->text);
        consume(tokens, 1);
        return (parser_return){ .error = PARSER_SUCCESS, .value = word_make_number(value) };
    } else if (token_type(*tokens, 0, LEXER_ID)) {
        const char *name = (*tokens)->text;
        consume(tokens, 1);
        return (parser_return){ .error = PARSER_SUCCESS, .value = word_make_name(name) };
    } else if (token_type(*tokens, 0, LEXER_L_PAREN)) {
        consume(tokens, 1);
        word *words = parse_words_impl(tokens);
        if (!expect(tokens, LEXER_R_PAREN)) {
            return (parser_return){ .error = PARSER_FAILURE, .value = NULL };
        }
        return (parser_return){ .error = PARSER_SUCCESS, .value = word_make_quote(words) };
    }
    return (parser_return){ .error = PARSER_FAILURE, .value = NULL };
}

static parser_return parse_def_impl(const lexer_token **tokens) {
    if (!expect(tokens, LEXER_LET)) {
        return (parser_return){ .error = PARSER_FAILURE, .value = NULL  };
    }
    if (!token_type(*tokens, 0, LEXER_ID)) {
        return (parser_return){ .error = PARSER_FAILURE, .value = NULL  };
    }
    const char *id = (*tokens)->text;
    consume(tokens, 1);
    if (!expect(tokens, LEXER_ASSIGN)) {
        return (parser_return){ .error = PARSER_FAILURE, .value = NULL  };
    }
    word *value = parse_words_impl(tokens);
    if (!expect(tokens, LEXER_DOT)) {
        return (parser_return){ .error = PARSER_FAILURE, .value = NULL };
    }
    return (parser_return){ .error = PARSER_SUCCESS, .value = def_make_let(id, word_make_quote(value)) };
}

/* Parses defs until there are no more defs to parse and
 * returns the successfully parsed defs in a list. */
static def *parse_defs_impl(const lexer_token **tokens) {
    parser_return result = parse_def_impl(tokens);
    if (result.error == PARSER_FAILURE) {
        return NULL;
    }
    def *first = result.value;
    result = parse_def_impl(tokens);
    first->next = result.value;
    return first;
}

static parser_return parse_file_impl(const lexer_token **tokens, const char *file_name) {
    def *defs = parse_defs_impl(tokens);
    if (*tokens != NULL) { /* Haven't reached the end of file. */
        return (parser_return){ .error = PARSER_FAILURE, .value = NULL };
    }
    return (parser_return){ .error = PARSER_SUCCESS, .value = source_file_make(file_name, defs) };
}

parser_return parser_parse_def(const lexer_token *tokens) {
    return parse_def_impl(&tokens);
}

parser_return parser_parse_word(const lexer_token *tokens) {
    return parse_word_impl(&tokens);
}

parser_return parser_parse_file(const lexer_token *tokens, const char *file_name) {
    return parse_file_impl(&tokens, file_name);
}
