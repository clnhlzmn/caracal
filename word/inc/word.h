#ifndef WORD_H
#define WORD_H

#include <stdint.h>

typedef enum {
    WORD_NAME,
    WORD_NUMBER,
    WORD_COMPOSE,
    WORD_QUOTE
} word_type;

typedef struct word word;

typedef struct {
    const char *text;
} word_name;

typedef struct {
    int64_t value;
} word_number;

typedef struct {
    word *first;
    word *second;
} word_compose;

typedef struct {
    word *word;
} word_quote;

struct word {
    word_type type;
    union {
        word_name name;
        word_number number;
        word_compose compose;
        word_quote quote;
    };
};

word *word_make_name(const char *text);

word *word_make_number(int64_t value);

word *word_make_compose(word *first, word *second);

word *word_make_quote(word *word);

#endif /*WORD_H*/
