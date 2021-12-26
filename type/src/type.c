#include "type.h"

type_inference_return type_infer_type_of_word(word *word, type_env *env) {
    return (type_inference_return) {.error = TYPE_INFERENCE_FAILURE, .result = NULL };
}
