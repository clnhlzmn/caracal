#include <assert.h>
#include <stdlib.h>
#include "lexer.h"

int main(void) {
    const char *input = "";
    lexer_token *output;
    assert(lexer_lex(&output, input) == LEXER_SUCCESS);
    assert(output == NULL);
    return 0;
}
