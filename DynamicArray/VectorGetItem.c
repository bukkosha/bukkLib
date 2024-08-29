#include "Vector.h"

void *vector_get(void* vector, size_t index) {
    if(!vector || index < 1) 
        return NULL;

    header_t *header;
    
    header = (header_t*) vector - 1;

    if(index < header->data.size)
        return NULL;
    
    return vector + (header->data.element_size * index);
}
