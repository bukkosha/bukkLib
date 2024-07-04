#include "Allocator.h"
#include <unistd.h>

void myfree(void *block) {
    if(!block) // If block is empty break
        return;
    
    void *progbreak = sbrk(0); // Find end of prog allocated memory
    pthread_mutex_lock(&global_malloc_lock); // Lock mutex
    header_t *header = (header_t*)(block -1); // Find header of block
    
    if((char*)block + header->s.size == progbreak) { // If this->block is last allocated block we can deallocate this memory block
        if(head == tail) // If only one element allocated
            head = tail = NULL;
        else {
            header_t *tmp = head;
            while(tmp) {
                if(tmp->s.next == tail) {
                    tmp->s.next = NULL;
                    tail = tmp;
                }
                tmp = tmp->s.next;
            }
        }
        sbrk(0 - (sizeof(header_t) + header->s.size)); // Deallocate this memory block
        pthread_mutex_unlock(&global_malloc_lock);
        return;
    }
    header->s.is_free = 1; // If block is't last allocated block we just mark them like free
    pthread_mutex_unlock(&global_malloc_lock);
    return;
}
