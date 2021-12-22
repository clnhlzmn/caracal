#include "parser.h"
#include "source_file.h"
#include <assert.h>

int main(void) {
    lexer_token *tokens;
    lexer_lex(&tokens, "");
    parser_return result = parser_parse_file(tokens, "foo");
    assert(!result.error);
    assert(result.value);
    assert(source_file_equal(result.value, source_file_make("foo", NULL)));
    
    lexer_lex(&tokens, "let foo = 123 .\nlet bar = 456 .");
    result = parser_parse_file(tokens, "foo");
    assert(!result.error);
    assert(result.value);
    assert(
        source_file_equal(
            result.value, 
            source_file_make("foo", 
                def_make_list(2, 
                    def_make_let("foo", word_make_quote(word_make_number(123))), 
                    def_make_let("bar", word_make_quote(word_make_number(456)))
                )
            )
        )
    );
    return 0;
}
