#include "word.h"
#include <assert.h>
#include <stdlib.h>

#define WORDS {                                                             \
        NULL,                                                               \
        word_make_name("foo"),                                              \
        word_make_number(123),                                              \
        word_make_quote(word_make_name("foo")),                             \
        word_make_compose(word_make_name("foo"), word_make_name("foo")),    \
        word_make_compose(NULL, word_make_number(123)),                     \
    }

int main(void) {
    /* Make distinct sets of otherwise equal words to ensure word_equal isn't just comparing addresses. */
    word *words_a[] = WORDS;
    word *words_b[] = WORDS;
    for (size_t i = 0; i < sizeof(words_a) / sizeof(word*); ++i) {
        for (size_t j = 0; j < sizeof(words_b) / sizeof(word*); ++j) {
            word *a = words_a[i];
            word *b = words_b[j];
            if (i == j) {
                assert(word_equal(a, b) && "word_equal should return true for equal words");
            } else {
                assert(!word_equal(a, b) && "word_equal should return false for unequal words");
            }
        }
    }
}
