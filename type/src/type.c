#include "type.h"
#include <stdarg.h>
#include <string.h>

static int id = 0;

static type *type_make_var_impl(int id) {
    type *ret = malloc(sizeof(type));
    ret->variant = TYPE_VAR;
    ret->var.id = id;
    ret->var.instance = NULL;
    ret->next = NULL;
    return ret;
}

type *type_make_var(void) {
    return type_make_var_impl(id++);
}

type *type_make_op(const char *operator, type *params) {
    type *ret = malloc(sizeof(type));
    ret->variant = TYPE_OP;
    ret->op.operator = operator;
    ret->op.params = params;
    ret->next = NULL;
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

type *type_make_duplicate(type *type) {
    if (!type) return NULL;
    switch (type->variant) {
    case TYPE_VAR:
        return type_make_var_impl(type->var.id);
    case TYPE_OP:
        return type_make_op(type->op.operator, type->op.params);
    }
    return NULL;
}

static bool type_params_equal(type *a, type *b) {
    if (!a && !b) {
        return true;
    } else if (!a || !b) {
        return false;
    } else {
        return type_equal(a, b) && type_params_equal(a->next, b->next);
    }
}

bool type_equal(type *a, type *b) {
    if (!a && !b) {
        return true;
    } else if (!a || !b) {
        return false;
    } else if (a->variant != b->variant) {
        return false;
    } else {
        switch (a->variant) {
        case TYPE_VAR:
            return type_equal(a->var.instance, b->var.instance) 
                && a->var.id == b->var.id;
        case TYPE_OP:
            return strcmp(a->op.operator, b->op.operator) == 0
                && type_params_equal(a->op.params, b->op.params);
        }
        return false;
    }
}

type_inference_return type_infer_type_of_word(word *word, type_env *env) {
    return (type_inference_return) {.error = TYPE_INFERENCE_FAILURE, .result = NULL };
}
