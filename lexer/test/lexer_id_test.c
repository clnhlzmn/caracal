#include <assert.h>
#include <string.h>
#include "lexer.h"

int main(void) {
    lexer_token *output;
    const char *input = "foo bar";
    lexer_return err = lexer_lex(&output, input);
    assert(err == LEXER_SUCCESS);
    assert(output);
    assert(output->type = LEXER_ID);
    assert(strcmp(output->text, "foo") == 0);
    output = output->next;
    assert(output);
    assert(output->type = LEXER_ID);
    assert(strcmp(output->text, "bar") == 0);
    return 0;
}
