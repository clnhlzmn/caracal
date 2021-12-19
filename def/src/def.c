#include "def.h"
#include <stdlib.h>

def *def_make_let(const char *id, word *value) {
    def *ret = malloc(sizeof(def));
    ret->id = id;
    ret->value = value;
    return ret;
}
