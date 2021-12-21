#include "def.h"
#include <assert.h>
#include <string.h>

int main(void) {
    assert(def_make_list(0) == NULL);
    def *list = def_make_list(1, def_make_let("foo", word_make_name("bar")));
    assert(list);
    assert(strcmp(list->id, "foo") == 0);
    assert(list->next == NULL);
    
    list = def_make_list(2, 
                def_make_let("foo", word_make_name("bar")),
                def_make_let("bar", word_make_number(123))
            );
    assert(list);
    assert(strcmp(list->id, "foo") == 0);
    assert(word_equal(list->value, word_make_name("bar")));
    assert(list->next);
    assert(strcmp(list->next->id, "bar") == 0);
    assert(word_equal(list->next->value, word_make_number(123)));
    assert(list->next->next == NULL);
    return 0;
}
