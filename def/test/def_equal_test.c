#include "def.h"
#include <assert.h>
#include <stdlib.h>

#define DEFS {                                  \
    NULL,                                       \
    def_make_let("foo", word_make_name("bar")), \
    def_make_let("foo", word_make_number(42))   \
    }

int main(void) {
    def *defs_a[] = DEFS;
    def *defs_b[] = DEFS;
    for (size_t i = 0; i < sizeof(defs_a) / sizeof(def*); ++i) {
        for (size_t j = 0; j < sizeof(defs_a) / sizeof(def*); ++j) {
            def *a = defs_a[i];
            def *b = defs_b[j];
            if (i == j) {
                assert(def_equal(a, b));
            } else {
                assert(!def_equal(a, b));
            }
        }
    }
    return 0;
}
