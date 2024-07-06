#include "Vector.h"

void vector_free(void* Block) {
    return free((void*) Block - 1);
}
