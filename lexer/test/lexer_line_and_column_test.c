#include <assert.h>
#include <string.h>
#include "lexer.h"

int main(void) {
    lexer_token *output;
    const char *input = "foo\nbar\r\n baz";
    lexer_return err = lexer_lex(&output, input);
    assert(err == LEXER_SUCCESS);
    assert(output->line == 1 && output->column == 1);
    output = output->next;
    assert(output->line == 2 && output->column == 1);
    output = output->next;
    assert(output->line == 3 && output->column == 2);
    return 0;
}
