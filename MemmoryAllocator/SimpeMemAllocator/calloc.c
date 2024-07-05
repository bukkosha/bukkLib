#pragma once

#include "Allocator.h"

void *mycalloc(size_t nmemb, size_t size) {
    if(size < 1 || nmemb < 1)
        return NULL;

    size_t total_size = size * nmemb;
    if(size != total_size / nmemb)
        return NULL;

    void *block = mymalloc(total_size);
    if(!block)
        return NULL;

    memset(block, 0, size);
    return block;
}
