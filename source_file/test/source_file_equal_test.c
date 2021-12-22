#include "source_file.h"
#include <assert.h>

#define FILES {                                                             \
    NULL,                                                                   \
    source_file_make("foo", NULL),                                          \
    source_file_make("foo", def_make_let("foo", NULL)),                     \
    source_file_make("bar", def_make_let("foo", NULL)),                     \
}

int main(void) {
    source_file *files_a[] = FILES;
    source_file *files_b[] = FILES;
    for (size_t i = 0; i < sizeof(files_a) / sizeof(source_file*); ++i) {
        for (size_t j = 0; j < sizeof(files_b) / sizeof(source_file*); ++j) {
            if (i == j) {
                assert(source_file_equal(files_a[i], files_b[j]));
            } else {
                assert(!source_file_equal(files_a[i], files_b[j]));
            }
        }
    }
    return 0;
}
