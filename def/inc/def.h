#ifndef DEF_H
#define DEF_H

#include "word.h"

typedef struct
{
    const char *id;
    word *value;
} def;

def *def_make_let(const char *id, word *value);

#endif /*DEF_H*/
