#ifndef SOURCE_FILE_H
#define SOURCE_FILE_H

#include "def.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    const char *file_name;
    def *defs;
} source_file;

source_file *source_file_make(const char *file_name, def *defs);

bool source_file_equals(const source_file *a, const source_file *b);

#endif /*SOURCE_FILE_H*/
