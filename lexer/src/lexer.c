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

static const char *copy_text(const char *input, size_t len) {
    char *ret = malloc(len + 1);
    ret[len] = 0;
    memcpy(ret, input, len);
    return ret;
}

lexer_return lexer_lex(lexer_token **output, const char *input) {
    if (!output || !input) return LEXER_FAILURE;
    *output = NULL;
    lexer_token *tail = NULL;
    for (char c = *input; c; c = *++input) {
        lexer_token *token = NULL;
        if (c == '{') {
            token = make_token(NULL, LEXER_L_BRACKET);
            token->text = "{";
        } else if (c == '}') {
            token = make_token(NULL, LEXER_R_BRACKET);
            token->text = "}";
        } else if (c == '(') {
            token = make_token(NULL, LEXER_L_PAREN);
            token->text = "(";
        } else if (c == ')') {
            token = make_token(NULL, LEXER_R_PAREN);
            token->text = ")";
        } else if (c == ';') {
            token = make_token(NULL, LEXER_SEMI);
            token->text = ";";
        } else if (c == ',') {
            token = make_token(NULL, LEXER_COMMA);
            token->text = ",";
        } else if (isdigit(c)) {
            const char *start = input;
            for (; isdigit(c); c = *++input) {
                if (!isdigit(*(input + 1)))
                    break;
            }
            size_t len = input - start + 1;
            token = make_token(NULL, LEXER_NATURAL);
            token->text = copy_text(start, len);
        } else if (isalpha(c) || c == '_') {
            const char *start = input;
            for (; isalpha(c) || isdigit(c) || c == '_'; c = *++input) {
                char next = *(input + 1);
                if (!isalpha(next) || !isdigit(next) || next != '_')
                    break;
            }
            size_t len = input - start + 1;
            token = make_token(NULL, LEXER_ID);
            token->text = copy_text(start, len);
        } else {
            return LEXER_FAILURE;
        }
        append(output, &tail, token);
    }
    return LEXER_SUCCESS;
}
