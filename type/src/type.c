#include "type.h"
#include <stdarg.h>

static int id = 0;

type *type_make_var(void) {
    type *ret = malloc(sizeof(type));
    ret->variant = TYPE_VAR;
    ret->var.id = id++;
    ret->var.instance = NULL;
    return ret;
}

type *type_make_op(const char *operator, type *params) {
    type *ret = malloc(sizeof(type));
    ret->variant = TYPE_OP;
    ret->op.operator = operator;
    ret->op.params = params;
    return ret;
}

static type *type_make_op_params_from_args(va_list ap, size_t count) {
    if (count) {
        type *param = va_arg(ap, type*);
        param->next = type_make_op_params_from_args(ap, count - 1);
        return param;
    } else {
        return NULL;
    }
}

type *type_make_op_from_args(const char *operator, size_t count, ...) {
    va_list ap;
    va_start(ap, count);
    type *ret = type_make_op(operator, type_make_op_params_from_args(ap, count));
    va_end(ap);
    return ret;
}

type_inference_return type_infer_type_of_word(word *word, type_env *env) {
    return (type_inference_return) {.error = TYPE_INFERENCE_FAILURE, .result = NULL };
}
