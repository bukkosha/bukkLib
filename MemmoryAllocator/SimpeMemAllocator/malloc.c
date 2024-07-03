#include <pthread.h>
#include <stddef.h>
#include <unistd.h>

// Allocated block if memory looks like {[header][requested memory]}.
// We can't free block of memory whitchone wasn't allocated last, becouse of that we well mark 'freed' block of memory like a free
// in header part of allocated memory and use it again if it will do for next allocate operation.

typedef char ALIGN[16]; // 16 bites for align header in allocated memory block

typedef union header { // Header of allocated memory block, need for keep size of allocated memory(without header), is free block and next block of allocated memory.
    struct {
        size_t size; // Size of allocated memory(without header)
        unsigned is_free; // Is block free for use
        union header *next; // Next allocated block of memory
    } s;
    ALIGN stub; // Align header of memory block for easy access to request memory block
} header_t;

header_t *head, *tail; // Pointers to head and tail of single linked list of allocated memory blocks.

// pthread_mutex_t mutex;

header_t *get_free_block(size_t size) { // Func for get fist free block of memory in out single linked list of already allocated blocks
    header_t *current = head;
    while(current) {
        if(current->s.is_free && current->s.size >= size)
            return current;
        current = current->s.next;
    }
    return NULL;
}

void *malloc(size_t size) {
    if(size < 1)
        return 0;
    size_t total_size;
    void *block;
    header_t header;
    
}
