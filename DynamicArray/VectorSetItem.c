#include "Vector.h"
#include <string.h>

void vector_set(void *vector, size_t index, void* element) {
    if(!vector || index < 1 || !element)
        return;

    header_t *header = (header_t*) vector - 1;

    if(header->data.size < index)
        return;

    memcpy(vector + index * header->data.element_size, element, header->data.element_size);
}
