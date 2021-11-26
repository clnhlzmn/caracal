#include <assert.h>
#include <string.h>
#include "lexer.h"

int main(void) {
    lexer_token *output;
    const char *input = "123bar123";
    lexer_return err = lexer_lex(&output, input);
    assert(err == LEXER_SUCCESS);
    assert(output);
    assert(output->type = LEXER_NATURAL);
    assert(strcmp(output->text, "123") == 0);
    output = output->next;
    assert(output);
    assert(output->type = LEXER_ID);
    assert(strcmp(output->text, "bar123") == 0);
    return 0;
}
