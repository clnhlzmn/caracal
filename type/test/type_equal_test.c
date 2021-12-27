#include "type.h"
#include <assert.h>

int main(void) {
    type *type0 = type_make_var();
    assert(type_equal(type0, type0));
    
    type *type1 = type_make_var();
    assert(!type_equal(type0, type1));
    
    type0 = type_make_op("foo", NULL);
    type1 = type_make_op("foo", NULL);
    assert(type_equal(type0, type1));
    
    type0 = type_make_op("foo", type_make_op("bar", NULL));
    type1 = type_make_op("foo", type_make_op("bar", NULL));
    assert(type_equal(type0, type1));
    
    type0 = type_make_op("foo", type_make_op("bar", NULL));
    type1 = type_make_op("foo", type_make_op("baz", NULL));
    assert(!type_equal(type0, type1));
    
    type0 = type_make_op("foo", type_make_op("bar", NULL));
    type1 = type_make_op("baz", type_make_op("bar", NULL));
    assert(!type_equal(type0, type1));
    
    type0 = type_make_op("foo", type_make_op("bar", NULL));
    type1 = type_make_op_from_args("foo", 2, type_make_op("bar", NULL), type_make_op("bar", NULL));
    assert(!type_equal(type0, type1));
    return 0;
}
