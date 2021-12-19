#ifndef DEF_H
#define DEF_H

#include "word.h"
#include <stdbool.h>

typedef struct
{
    const char *id;
    word *value;
} def;

def *def_make_let(const char *id, word *value);

bool def_equal(const def *a, const def *b);

#endif /*DEF_H*/