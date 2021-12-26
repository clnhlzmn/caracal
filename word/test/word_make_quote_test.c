#include "word.h"
#include <assert.h>
#include <string.h>

int main(void) {
    word *quoted_word = word_make_name("foo");
    word *node = word_make_quote(quoted_word);
    assert(node && "node should not be null");
    assert(node->variant == WORD_QUOTE && "node->variant should equal WORD_QUOTE");
    assert(node->quote.word == quoted_word && "node->quote.word should equal quoted_word");
    return 0;
}
