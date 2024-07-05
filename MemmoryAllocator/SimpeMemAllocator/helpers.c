#include "Allocator.h"

header_t *get_free_block(size_t size) { // Func for get fist free block of memory in out single linked list of already allocated blocks
    header_t *current = head;
    while(current) {
        if(current->s.is_free && current->s.size >= size)
            return current;
        current = current->s.next;
    }
    return NULL;
}

