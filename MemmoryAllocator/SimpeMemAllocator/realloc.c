#pragma once

#include "Allocator.h"

void *myrealloc(void *block, size_t size) {
    if(!block || !size)
        return mymalloc(size);
    
    header_t *header = (header_t*)(block - 1);
    void *ret_block;

    if(header->s.size <= size)
        return block;

    ret_block = mymalloc(size);

    if(ret_block) {
        memcpy(ret_block, block, header->s.size);
        myfree(block);
    }

    return ret_block;
}
