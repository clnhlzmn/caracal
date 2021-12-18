#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

int main(void) {
    const char *input[] = {
        "(", ")", "=", ".", "let",
        "0123456789", "abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789"
    };
    for (size_t i = 0; i < sizeof(input)/sizeof(const char *); ++i) {
        lexer_token *output = NULL;
        assert(lexer_lex(&output, input[i]) == LEXER_SUCCESS);
        assert(output);
        assert((size_t)output->type == i);
        assert(strcmp(input[i], output->text) == 0);
        assert(output->next == NULL);
    }
    return 0;
}
