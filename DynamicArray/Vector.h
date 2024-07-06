#include <stddef.h>
#include <stdlib.h>
typedef char ALIGN[16];

typedef union {
    struct {
        size_t size;
        size_t capacity;
        size_t element_size;
    } data;
    ALIGN stub;

} header_t;

void *vector_init(size_t initial_capacity, size_t element_size);
void vector_free(void *Block);
void *vector_copy(void *vec);
void *vector_get(void *vector, size_t index);
