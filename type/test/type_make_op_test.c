#include "type.h"
#include <assert.h>
#include <string.h>

int main(void) {
    type *op = type_make_op("foo", NULL);
    assert(op);
    assert(op->variant == TYPE_OP);
    assert(op->next == NULL);
    assert(strcmp(op->op.operator, "foo") == 0);
    assert(op->op.params == NULL);
    type *param0 = type_make_var();
    type *param1 = type_make_var();
    param0->next = param1;
    op = type_make_op("foo", param0);
    assert(op->next == NULL);
    assert(op->op.params == param0);
    assert(op->op.params->next == param1);
    assert(op->op.params->next->next == NULL);
}
