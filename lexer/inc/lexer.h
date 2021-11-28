#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>

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
    LEXER_ID,
} lexer_token_type;

struct lexer_token;

typedef struct lexer_token lexer_token;

struct lexer_token {
    const char *text;
    lexer_token_type type;
    size_t line;
    size_t column;
    lexer_token *next;
};

/**
 * @brief Analyzes input and produces a list of tokens.
 * The output token list is dynamically allocated by @ref
 * lexer_lex and should be freed by the caller.
 * @param [out] output Pointer to the ouput token list.
 * @param [in] input Pointer to the input character string.
 * @return Returns LEXER_SUCCESS if successful.
 */
lexer_return lexer_lex(lexer_token **output, const char *input);

/**
 * @brief Frees a token list that was produced by @ref lexer_lex.
 * @param [in] tokens Pointer to the token list.
 * @return Returns LEXER_SUCCESS if successful.
 */
lexer_return lexer_free(lexer_token *tokens);

#endif /*LEXER_H*/
