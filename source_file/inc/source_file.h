#ifndef SOURCE_FILE_H
#define SOURCE_FILE_H

#include "def.h"
#include "list.h"
#include <stdlib.h>

typedef struct
{
    const char *file_name;
    struct list defs_list;
} source_file;

source_file *source_file_make(const char *file_name, struct list defs_list);

#endif /*SOURCE_FILE_H*/
