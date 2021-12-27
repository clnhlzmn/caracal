#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "type.h"

typedef enum {
    PARSER_SUCCESS,
    PARSER_FAILURE
} parser_error;

typedef struct parser_type_state parser_type_state;

typedef struct {
    parser_error error;
    void *value;
    parser_type_state *state;
} parser_return;

struct parser_type_state {
    const char *id;
    type *type;
    parser_type_state *next;
};

parser_return parser_parse_def(const lexer_token *tokens);

parser_return parser_parse_word(const lexer_token *tokens);

parser_return parser_parse_file(const lexer_token *tokens, const char *file_name);

parser_type_state *parser_type_state_make(const char *id, type *type, parser_type_state *next);

type *parser_type_state_find(parser_type_state *state, const char *id);

parser_return parser_parse_type(const lexer_token *tokens, parser_type_state *state);

#endif /*PARSER_H*/
