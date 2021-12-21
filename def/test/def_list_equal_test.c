#include "def.h"
#include <assert.h>

#define DEFS {                                                      \
    NULL,                                                           \
    def_make_list(1, def_make_let("foo", word_make_name("bar"))),   \
    def_make_list(2, def_make_let("foo", word_make_name("bar")),    \
                     def_make_let("bar", word_make_number(123)))    \
}

int main() {
    def *defs_a[] = DEFS;
    def *defs_b[] = DEFS;
    for (size_t i = 0; i < sizeof(defs_a) / sizeof(def*); ++i) {
        for (size_t j = 0; j < sizeof(defs_b) / sizeof(def*); ++j) {
            if (i == j) {
                assert(def_list_equal(defs_a[i], defs_b[j]));
            } else {
                assert(!def_list_equal(defs_a[i], defs_b[j]));
            }
        }
    }
}
