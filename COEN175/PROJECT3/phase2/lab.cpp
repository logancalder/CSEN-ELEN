#include "Type.h"
#include <cassert>

Declarator::Declarator(int kind, unsigned length, Parameters *parameters):_kind(kind), _length(length), _parameters(parameters){
    assert(kind == POINTER || kind == ARRAY || kind == FUNCTION);
}