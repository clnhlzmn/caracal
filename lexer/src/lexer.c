#include <ctype.h>
#include <stdlib.h>
#include "lexer.h"

static lexer_token *make_token(const char *text, lexer_token_type type) {
    lexer_token *token = malloc(sizeof(lexer_token));
    token->text = text;
    token->type = type;
    return token;
}

static void append(lexer_token **head, lexer_token **tail, lexer_token *token) {
    token->next = NULL;
    if (*head == NULL) {
        *head = token;
    } else {
        (*tail)->next = token;
    }
    *tail = token;
}

lexer_return lexer_lex(lexer_token **output, const char *input) {
    if (!output || !input) return LEXER_FAILURE;
    *output = NULL;
    lexer_token *tail = NULL;
    for (char c = *input; c; c = *++input) {
        lexer_token *token = NULL;
        if (c == '{') {
            token = make_token(NULL, LEXER_L_BRACKET);
        } else if (c == '}') {
            token = make_token(NULL, LEXER_R_BRACKET);
        } else if (c == '(') {
            token = make_token(NULL, LEXER_L_PAREN);
        } else if (c == ')') {
            token = make_token(NULL, LEXER_R_PAREN);
        } else if (c == ';') {
            token = make_token(NULL, LEXER_SEMI);
        } else if (c == ',') {
            token = make_token(NULL, LEXER_COMMA);
        } else if (isdigit(c)) {
            for (; isdigit(c); c = *++input) {
                if (!isdigit(*(input + 1)))
                    break;
            }
            token = make_token(NULL, LEXER_NATURAL);
        } else if (isalpha(c) || c == '_') {
            for (; isalpha(c) || isdigit(c) || c == '_'; c = *++input) {
                char next = *(input + 1);
                if (!isalpha(next) || !isdigit(next) || next != '_')
                    break;
            }
            token = make_token(NULL, LEXER_ID);
        } else {
            return LEXER_FAILURE;
        }
        append(output, &tail, token);
    }
    return LEXER_SUCCESS;
}
