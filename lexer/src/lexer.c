#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

static lexer_token *make_token(const char *text, lexer_token_type type, size_t line, size_t column) {
    lexer_token *token = malloc(sizeof(lexer_token));
    token->text = text;
    token->type = type;
    token->line = line;
    token->column = column;
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
    size_t line = 1;
    const char *line_start = input;
    while (1) {
        char c = *input;
        if (!c) break;
        lexer_token *token = NULL;
        if (c == '{') {
            token = make_token("{", LEXER_L_BRACKET, line, input - line_start + 1);
            input++;
        } else if (c == '}') {
            token = make_token("}", LEXER_R_BRACKET, line, input - line_start + 1);
            input++;
        } else if (c == '(') {
            token = make_token("(", LEXER_L_PAREN, line, input - line_start + 1);
            input++;
        } else if (c == ')') {
            token = make_token(")", LEXER_R_PAREN, line, input - line_start + 1);
            input++;
        } else if (c == ';') {
            token = make_token(";", LEXER_SEMI, line, input - line_start + 1);
            input++;
        } else if (c == ',') {
            token = make_token(",", LEXER_COMMA, line, input - line_start + 1);
            input++;
        } else if (isdigit(c)) {
            const char *start = input;
            for (; isdigit(c); c = *++input) {}
            size_t len = input - start;
            token = make_token(copy_text(start, len), LEXER_NATURAL, line, start - line_start + 1);
        } else if (isalpha(c) || c == '_') {
            const char *start = input;
            for (; isalpha(c) || isdigit(c) || c == '_'; c = *++input) {}
            size_t len = input - start;
            token = make_token(copy_text(start, len), LEXER_ID, line, start - line_start + 1);
        } else if (isspace(c)) {
            for (; isspace(c); c = *++input) {
                if (c == '\n') {
                    line++;
                    line_start = input + 1;
                }
            }
            continue;
        } else {
            return LEXER_FAILURE;
        }
        append(output, &tail, token);
    }
    return LEXER_SUCCESS;
}

lexer_return lexer_free(lexer_token *tokens) {
    while (tokens) {
        lexer_token *current = tokens;
        tokens = tokens->next;
        if (current->type == LEXER_NATURAL || current->type == LEXER_ID) {
            free((void*)current->text);
        }
        free(current);
    }
    return LEXER_SUCCESS;
}
