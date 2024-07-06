#include <stddef.h>
#include <stdlib.h>
typedef char ALIGN[16];

typedef union {
    struct {
        size_t size;
        size_t capacity;
    } data;
    ALIGN stub;

} header_t;
