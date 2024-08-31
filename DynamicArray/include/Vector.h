#include <stddef.h>

typedef enum { UNINITIALIZED, INTEGER, FLOAT, DOUBLE, STRING } types;

typedef char ALIGN[16];

typedef union {
    types dataType;
    struct {
        size_t size;
        size_t capacity;
    } data;
    ALIGN stub;
} header_t;
