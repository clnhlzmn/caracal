#ifndef LEXER_H
#define LEXER_H

typedef enum {
    LEXER_SUCCESS,
    LEXER_FAILURE
} lexer_return;

typedef enum {
    LEXER_L_BRACKET,
    LEXER_R_BRACKET,
    LEXER_L_PAREN,
    LEXER_R_PAREN,
    LEXER_SEMI,
    LEXER_COMMA,
    LEXER_NATURAL,
    LEXER_ID
} lexer_token_type;

struct lexer_token;

typedef struct lexer_token lexer_token;

struct {
    const char *text;
    lexer_token_type type;
    lexer_token *next;
};

lexer_return lexer_lex(lexer_token **output, const char *input);

#endif /*LEXER_H*/
