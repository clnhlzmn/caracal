#include "word.h"
#include "stdlib.h"
#include <string.h>

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

bool word_equal(word *a, word *b) {
    if (!a && !b) { 
        return true;
    } else if ((!a && b) || (a && !b)) {
        return false;
    } else if (a->type != b->type) {
        return false;
    } else {
        switch (a->type) {
        case WORD_NAME:
            return strcmp(a->name.text, b->name.text) == 0;
        case WORD_NUMBER:
            return a->number.value == b->number.value;
        case WORD_QUOTE:
            return word_equal(a->quote.word, b->quote.word);
        case WORD_COMPOSE:
            return word_equal(a->compose.first, b->compose.first)
                && word_equal(a->compose.second, b->compose.second);
        }
    }
}
