#include "source_file.h"
#include <string.h>
#include <assert.h>

int main(void) {
    def *defs = def_make_let("foo", word_make_number(123));
    source_file *file = source_file_make("foo", defs);
    assert(file);
    assert(strcmp(file->file_name, "foo") == 0);
    assert(def_list_equal(file->defs, defs));
}
