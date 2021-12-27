#include "parser.h"
#include "type.h"
#include <assert.h>

int main(void) {
    lexer_token *tokens;
    lexer_lex(&tokens, "a");
    parser_return result = parser_parse_type(tokens, NULL);
    assert(result.error == PARSER_SUCCESS);
    type *parsed_type = result.value;
    assert(parsed_type->variant == TYPE_VAR);
    
    lexer_lex(&tokens, "a -> a");
    result = parser_parse_type(tokens, NULL);
    assert(result.error == PARSER_SUCCESS);
    parsed_type = result.value;
    parser_type_state *state = result.state;
    type *var_type = parser_type_state_find(state, "a");
    assert(var_type);
    type *expected = type_make_op_from_args("Fun", 2, var_type, type_make_duplicate(var_type));
    assert(type_equal(expected, parsed_type));
    
    /* TODO: more cases */
    return 0;
}
