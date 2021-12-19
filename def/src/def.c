#include "def.h"
#include <stdlib.h>
#include <string.h>

def *def_make_let(const char *id, word *value) {
    def *ret = malloc(sizeof(def));
    ret->id = id;
    ret->value = value;
    return ret;
}

bool def_equal(const def *a, const def *b) {
    if (!a && !b) {
        return true;
    } else if ((!a && b) || (a && !b)) {
        return false;
    } else {
        return strcmp(a->id, b->id) == 0
            && word_equal(a->value, b->value);
    }
}
