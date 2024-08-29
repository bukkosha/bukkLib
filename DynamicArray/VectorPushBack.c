#include "Vector.h"

int vector_push_back(void *vector, size_t element) {
    if(!vector)
        return -1;

    header_t *header;

    header = (header_t*) vector - 1;

    
}
