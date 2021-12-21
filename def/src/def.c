#include "def.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

def *def_make_let(const char *id, word *value) {
    def *ret = malloc(sizeof(def));
    ret->id = id;
    ret->value = value;
    ret->next = NULL;
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

bool def_list_equal(def *a, def *b) {
    bool either_is_null = !a || !b;
    return def_equal(a, b) 
        && (either_is_null || def_list_equal(a->next, b->next));
}

static def *def_make_list_impl(size_t n, va_list *ap) {
    if (n == 0) {
        return NULL;
    } else {
        def *first = va_arg(*ap, def*);
        def *rest = def_make_list_impl(n - 1, ap);
        first->next = rest;
        return first;
    }
}

def *def_make_list(size_t n, ...) {
    va_list ap;
    va_start(ap, n);
    def *ret = def_make_list_impl(n, &ap);
    va_end(ap);
    return ret;
}
