#include "source_file.h"
#include <stdlib.h>
#include <string.h>

source_file *source_file_make(const char *file_name, struct list defs_list) {
    source_file *ret = malloc(sizeof(source_file));
    ret->file_name = file_name;
    ret->defs_list = defs_list;
    return ret;
}
