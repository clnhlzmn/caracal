#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    PARSER_SUCCESS,
    PARSER_FAILURE
} parser_error;

typedef struct {
    parser_error error;
} parser_return;

parser_return parser_parse_word(const lexer_token *tokens);

#endif /*PARSER_H*/
