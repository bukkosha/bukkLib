#include "Vector.h"

size_t vector_get_size(void* vector) {
    if(!vector)
        return 0;

    header_t *header = (header_t*) vector - 1;

    return header->data.size;
}