#include "Vector.h"

void VectorFree(void* block) {
    return free((void*) block - 1);
}
