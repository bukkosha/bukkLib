#pragma once

#include <unistd.h>
#include <string.h>
#include <pthread.h>

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

extern header_t *head, *tail; // Pointers to head and tail of single linked list of allocated memory blocks.
extern pthread_mutex_t global_malloc_lock;


header_t *get_free_block(size_t size);
void *mymalloc(size_t size);
void myfree(void* block);
void *mycalloc(size_t nmemb, size_t size);
void *myrealloc(void *block, size_t size);
