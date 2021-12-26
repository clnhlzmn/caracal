#include "type.h"
#include <assert.h>

int main(void) {
    type *var = type_make_var();
    assert(var);
    assert(var->variant == TYPE_VAR);
    assert(var->next == NULL);
    assert(var->var.id == 0);
    var = type_make_var();
    assert(var->var.id == 1);
}
