#include "parser.h"
#include <assert.h>

int main(void) {
    lexer_token *tokens;
    lexer_lex(&tokens, "");
    parser_return result = parser_parse_file(tokens, "foo");
    assert(!result.error);
    assert(result.value);
    return 0;
}
