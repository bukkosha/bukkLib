#include "Vector.h"
#include <string.h>

void *VectorCopy(void *vec) {
    if(!vec)
        return NULL;

    header_t *tHeader, *nHeader;
    void *tBlock, *nBlock;

    tBlock = (void*) vec - 1;

    tHeader = tBlock;

    if(!tHeader->data.size || !tHeader->data.capacity)
        return NULL;

    nBlock = VectorInit(tHeader->data.capacity, tHeader->data.element_size);
    
    if(!nBlock)
        return NULL;

    nHeader = nBlock;

    if(!memcpy(nBlock, tBlock, sizeof(header_t) + tHeader->data.size * tHeader->data.element_size)) {
        VectorFree(nBlock);
        return NULL;
    }
    
    return (void*) nBlock + 1;
}
