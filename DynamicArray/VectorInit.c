#include "Vector.h"

void *VectorInit(size_t initial_capacity, size_t element_size) {
    if(!initial_capacity || !element_size)
        return NULL;

    header_t *header;
    size_t total_size;
    void *Block;

    total_size = sizeof(header_t) + (initial_capacity * element_size);
    Block = malloc(total_size);

    if(!Block)
        return NULL;

    header = Block;

    header->data.size = 0;
    header->data.capacity = initial_capacity;

    return (void*) header + 1;
}
