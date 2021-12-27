#ifndef TYPES_H
#define TYPES_H

#include "word.h"
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    TYPE_VAR,
    TYPE_OP
} type_variant;

typedef struct type type;

typedef struct {
    int id;
    type *instance;
} type_var;

typedef struct {
    const char *operator;
    type *params;
} type_op;

struct type {
    type_variant variant;
    type *next;
    union {
        type_var var;
        type_op op;
    };
};

typedef enum {
    TYPE_INFERENCE_SUCCESS,
    TYPE_INFERENCE_FAILURE_ARGS,
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

type *type_make_var(void);

type *type_make_op(const char *operator, type *params);

type *type_make_op_from_args(const char *operator, size_t count, ...);

type *type_make_duplicate(type *type);

bool type_equal(type *a, type *b);

type_inference_return type_infer_type_of_word(word *word, type_env *env);

#endif /* TYPES_H */
