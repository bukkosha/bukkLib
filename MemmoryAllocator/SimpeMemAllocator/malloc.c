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
    size_t total_size; // Total size is full size of block of memory = size of header + requested size
    void *block; // Pointer at allocated memory
    header_t *header;

    header = get_free_block(size);
    if(header != NULL) {
        header->s.is_free = 0;
        return (void*)(header + 1);
    }
    total_size = sizeof(header_t) + size;
    block = sbrk(total_size);
    if(block == (void *) -1)
        return NULL;

    header = block;
    header->s.size = size;
    header->s.is_free = 0;
    header->s.next = NULL;
    if(!head)
        head = header;
    if(tail)
        tail->s.next = header;
    tail = header;

    return (void*)(header + 1);
}
