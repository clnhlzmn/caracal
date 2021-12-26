#include "type.h"
#include <assert.h>
#include <string.h>

int main(void) {
    type *param0 = type_make_var();
    type *param1 = type_make_var();
    param0->next = param1;
    type *op = type_make_op_from_args("foo", 2, param0, param1);
    assert(op->variant == TYPE_OP);
    assert(op->next == NULL);
    assert(op->op.params == param0);
    assert(op->op.params->next == param1);
    assert(op->op.params->next->next == NULL);
}
