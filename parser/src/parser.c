#include "parser.h"
#include "word.h"
#include "def.h"
#include "source_file.h"
#include "type.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

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

parser_type_state *parser_type_state_make(const char *id, type *type, parser_type_state *next) {
    parser_type_state *ret = malloc(sizeof(parser_type_state));
    ret->id = id;
    ret->type = type;
    ret->next = next;
    return ret;
}

type *parser_type_state_find(parser_type_state *state, const char *id) {
    if (!state) return NULL;
    return strcmp(state->id, id) == 0 ? type_make_duplicate(state->type) : parser_type_state_find(state->next, id);
}

static parser_return parse_type_impl(const lexer_token **tokens, parser_type_state *state);

static type *parse_types_impl(const lexer_token **tokens, parser_type_state *state) {
    parser_return result = parse_type_impl(tokens, state);
    if (result.error != PARSER_SUCCESS) {
        return NULL;
    }
    type *ret = result.value;
    ret->next = parse_types_impl(tokens, state);
    return ret;
}

static parser_return try_parse_fun_type(const lexer_token **tokens, type *lhs, parser_type_state *state) {
    if (token_type(*tokens, 0, LEXER_R_ARROW)) {
        consume(tokens, 1);
        parser_return result = parse_type_impl(tokens, state);
        if (result.error) return result;
        return (parser_return) { .error = PARSER_SUCCESS, .value = type_make_op_from_args("Fun", 2, lhs, result.value), .state = state };
    } else {
        return (parser_return) { .error = PARSER_SUCCESS, .value = lhs, .state = state };
    }
}

static type *make_pair_type_from_word_param_list(type *list, type *base) {
    if (!list) return base;
    base = type_make_op_from_args("Pair", 2, type_make_duplicate(list), base);
    return make_pair_type_from_word_param_list(list->next, base);
}

static parser_return parse_type_impl(const lexer_token **tokens, parser_type_state *state) {
    if (token_type(*tokens, 0, LEXER_ID)) {
        const char *id = (*tokens)->text;
        type *type = parser_type_state_find(state, id);
        if (type == NULL) {
            type = type_make_var();
            state = parser_type_state_make(id, type, state);
        }
        consume(tokens, 1);
        return try_parse_fun_type(tokens, type, state);
    } else if (token_type(*tokens, 0, LEXER_TYPENAME)) {
        const char *operator = (*tokens)->text;
        consume(tokens, 1);
        type *params = NULL;
        if (token_type(*tokens, 1, LEXER_L_PAREN)) {
            consume(tokens, 1);
            params = parse_types_impl(tokens, state);
            expect(tokens, LEXER_R_PAREN);
        }
        return try_parse_fun_type(tokens, type_make_op(operator, params), state);
    } else if (token_type(*tokens, 0, LEXER_L_PAREN)) {
        /* Either a pair or a word type. */
        consume(tokens, 1);
        type *lhs = parse_types_impl(tokens, state);
        if (token_type(*tokens, 1, LEXER_DOT)) {
            /* Parsing a pair type. */
            consume(tokens, 1);
            type *rhs = parse_types_impl(tokens, state);
            if (!rhs) return (parser_return) { .error = PARSER_FAILURE, .value = NULL };
            expect(tokens, LEXER_R_PAREN);
            return try_parse_fun_type(tokens, type_make_op_from_args("Pair", 2, lhs, rhs), state);
        } else if (token_type(*tokens, 1, LEXER_R_PAREN)) {
            /* Parsing a word type. */
            consume(tokens, 1);
            expect(tokens, LEXER_R_ARROW);
            expect(tokens, LEXER_L_PAREN);
            type *rhs = parse_types_impl(tokens, state);
            if (!rhs) return (parser_return) { .error = PARSER_FAILURE, .value = NULL };
            expect(tokens, LEXER_R_PAREN);
            type *stack_base = type_make_var();
            lhs = make_pair_type_from_word_param_list(lhs, stack_base);
            rhs = make_pair_type_from_word_param_list(rhs, stack_base);
            return try_parse_fun_type(tokens, type_make_op_from_args("Fun", 2, lhs, rhs), state);
        }
    }
    return (parser_return) { .error = PARSER_FAILURE, .value = NULL };
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

parser_return parser_parse_type(const lexer_token *tokens, parser_type_state *state) {
    return parse_type_impl(&tokens, state);
}
