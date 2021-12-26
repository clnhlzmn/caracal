#include "word.h"
#include <assert.h>
#include <string.h>

int main(void) {
    word *node = word_make_name("foo");
    assert(node && "node should not be null");
    assert(node->variant == WORD_NAME && "node->variant should equal WORD_NAME");
    assert(strcmp(node->name.text, "foo") == 0 && "node->name.text should equal foo");
    return 0;
}
