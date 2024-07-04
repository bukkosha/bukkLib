#include <stddef.h>
#include "Allocator.h"

header_t *head, *tail;
pthread_mutex_t global_malloc_lock;

void *mymalloc(size_t size) {
    if(size < 1)
        return 0;
//    pthread_mutex_init(&global_malloc_lock, NULL);
    size_t total_size; // Total size is full size of block of memory = size of header + requested size
    void *block; // Pointer at allocated memory
    header_t *header;

    pthread_mutex_lock(&global_malloc_lock);
    header = get_free_block(size);
    if(header != NULL) {
        header->s.is_free = 0;
        pthread_mutex_unlock(&global_malloc_lock);
        return (void*)(header + 1);
    }
    total_size = sizeof(header_t) + size;
    block = sbrk(total_size);
    if(block == (void *) -1){
        pthread_mutex_unlock(&global_malloc_lock);
        return NULL;
    }

    header = block;
    header->s.size = size;
    header->s.is_free = 0;
    header->s.next = NULL;
    if(!head)
        head = header;
    if(tail)
        tail->s.next = header;
    tail = header;

    pthread_mutex_unlock(&global_malloc_lock);
//    pthread_mutex_destroy(&global_malloc_lock);
    return (void*)(header + 1);
}
