#ifndef DEF_H
#define DEF_H

#include "word.h"
#include <stdbool.h>
#include <stdlib.h> 

typedef struct def def;

struct def
{
    def *next;
    const char *id;
    word *value;
};

def *def_make_let(const char *id, word *value);

bool def_equal(const def *a, const def *b);

bool def_list_equal(def *a, def *b);

/* Takes n def* and returns a struct list that contains those defs. */
def *def_make_list(size_t n, ...);

#endif /*DEF_H*/
