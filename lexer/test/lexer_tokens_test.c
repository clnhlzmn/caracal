#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

int main(void) {
    const char *input = "{}();,1a";
    lexer_token *output = NULL;
    assert(lexer_lex(&output, input) == LEXER_SUCCESS);
    for (size_t i = 0; i < strlen(input); ++i) {
        assert(output);
        assert((size_t)output->type == i);
        char text[2] = {0};
        memcpy(text, &input[i], 1);
        assert(strcmp(text, output->text) == 0);
        output = output->next;
    }
    assert(output == NULL);
    return 0;
}
