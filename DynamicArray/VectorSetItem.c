#include "Vector.h"
#include <string.h>

int vector_set(void *vector, size_t index, void* element) {
    if(!vector || index < 1 || !element)
        return -1;

    header_t *header = (header_t*) vector - 1;

    if(header->data.size < index)
        return -1;

    if(!memcpy(vector + index * header->data.element_size, element, header->data.element_size))
        return -1;
    return 0;
}
