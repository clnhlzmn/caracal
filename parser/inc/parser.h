#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    PARSER_SUCCESS,
    PARSER_FAILURE
} parser_return;

parser_return parse_expr(void *output, const lexer_token *tokens);

#endif /*PARSER_H*/
