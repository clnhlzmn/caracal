#include "def.h"
#include <assert.h>
#include <string.h>

int main(void) {
    word *value = word_make_name("bar");
    def *def = def_make_let("foo", value);
    assert(def && "def should not be NULL");
    assert(strcmp(def->id, "foo") == 0 && "def->id should equal foo");
    assert(def->value == value && "def->value should equal value");
}
