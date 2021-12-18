#include "word.h"
#include "stdlib.h"

word *word_make_name(const char *text) {
    word *ret = malloc(sizeof(word));
    ret->type = WORD_NAME;
    ret->name.text = text;
    return ret;
}

word *word_make_number(int64_t value) {
    word *ret = malloc(sizeof(word));
    ret->type = WORD_NUMBER;
    ret->number.value = value;
    return ret;
}

word *word_make_compose(word *first, word *second) {
    word *ret = malloc(sizeof(word));
    ret->type = WORD_COMPOSE;
    ret->compose.first = first;
    ret->compose.second = second;
    return ret;
}

word *word_make_quote(word *quoted_word) {
    word *ret = malloc(sizeof(word));
    ret->type = WORD_QUOTE;
    ret->quote.word = quoted_word;
    return ret;
}
