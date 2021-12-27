#include "type.h"
#include <assert.h>

int main(void) {
    type *type0 = type_make_var();
    type *type1 = type_make_duplicate(type0);
    assert(type_equal(type0, type1));
    
    type0 = type_make_op("foo", type_make_op("bar", NULL));
    type1 = type_make_duplicate(type0);
    assert(type_equal(type1, type1));
    return 0;
}
