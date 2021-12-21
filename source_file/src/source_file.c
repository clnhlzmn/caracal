#include "source_file.h"
#include <stdlib.h>
#include <string.h>

source_file *source_file_make(const char *file_name, def *defs) {
    source_file *ret = malloc(sizeof(source_file));
    ret->file_name = file_name;
    ret->defs = defs;
    return ret;
}

bool source_file_equals(const source_file *a, const source_file *b) {
    if (!a && !b) {
        return true;
    } else if((!a && b) || (a && !b)) {
        return false;
    } else {
        return strcmp(a->file_name, b->file_name) == 0
            && def_list_equal(a->defs, b->defs);
    }
}
