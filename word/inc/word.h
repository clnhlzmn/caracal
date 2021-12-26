#ifndef WORD_H
#define WORD_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    WORD_NAME,
    WORD_NUMBER,
    WORD_COMPOSE,
    WORD_QUOTE
} word_variant;

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
    word_variant variant;
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

bool word_equal(word *a, word *b);

#endif /*WORD_H*/
