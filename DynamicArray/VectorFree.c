#include "Vector.h"

void VectorFree(void* Block) {
    return free((void*) Block - 1);
}
