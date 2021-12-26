#ifndef TYPES_H
#define TYPES_H

#include "word.h"
#include <stdlib.h>

typedef enum {
    TYPE_VAR,
    TYPE_OP
} type_class;

typedef enum {
    TYPE_OP_UNIT,
    TYPE_OP_BOOL,
    TYPE_OP_INT,
    TYPE_OP_FUN
} type_op_class;

typedef struct type type;

typedef struct {
    int id;
    type *instance;
} type_var;

typedef struct {
    type_op_class class_;
    type *params;
    size_t param_count;
} type_op;

struct type {
    type_class class_;
    union {
        type_var var;
        type_op op;
    };
};

typedef enum {
    TYPE_INFERENCE_SUCCESS,
    TYPE_INFERENCE_FAILURE
} type_error;

typedef struct {
    type_error error;
    type *result;
} type_inference_return;

typedef struct type_env type_env;

struct type_env {
    const char *id;
    type *type;
    type_env *next;
};

type_inference_return type_infer_type_of_word(word *word, type_env *env);

#endif /* TYPES_H */
